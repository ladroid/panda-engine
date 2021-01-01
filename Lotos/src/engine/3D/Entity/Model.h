#include "../../panda-engine-windows/Lotos/stb_image.h"
#include "glad/glad.h"
#include "glm.hpp"
#include "Mesh.h"
#include "Shader.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include <iostream>
#include <sstream>
#include <map>
#include <fstream>
#include <vector>
#include <string>

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);
/*
* //TODO:make animation
*/
class Model
{
private:
    Assimp::Importer import;
	std::vector<Mesh> mesh;
    std::string directory;
    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadTexture(aiMaterial* material, aiTextureType textureType, std::string typeName);
public:
    std::vector<Texture> textures_loaded;
    bool gammaCorrection;
    Model() { }
    Model(std::string path, bool gamma = false) : gammaCorrection(gamma)
    {
        loadModel(path);
    }
    void setModel(std::string path, bool gamma = false)
    {
        loadModel(path);
    }
    void draw(Shader& shader);
	~Model();
};

void Model::loadModel(std::string path)
{
    std::cout << path << std::endl;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "Error could not find a model ERROR::ASSIMP:: " << import.GetErrorString() << std::endl;
        return;
    }
    this->directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        this->mesh.push_back(processMesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> verticies;
    std::vector<unsigned int> indicies;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex _vertex;

        //verticies data
        glm::vec3 vector;

        //verticies
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;

        _vertex.Position = vector;

        //normal
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;

            _vertex.Normal = vector;
        }

        //texture coordinates
        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            _vertex.TexCoords = vec;

            // tangent
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            _vertex.Tangent = vector;

            // bitangent
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            _vertex.Bitangent = vector;
        } 
        else 
        {
            _vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }

        verticies.push_back(_vertex);
    }

    //mesh indicies
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indicies.push_back(face.mIndices[j]);
        }
    }

    //materials and diffuse
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    Material mater;
    aiColor3D color(0.f, 0.f, 0.f);

    //Read mtl file
    material->Get(AI_MATKEY_COLOR_AMBIENT, color);
    mater.Ka = glm::vec4(color.r, color.g, color.b, 1.0);
    material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
    mater.Kd = glm::vec4(color.r, color.g, color.b, 1.0);
    material->Get(AI_MATKEY_COLOR_SPECULAR, color);
    mater.Ks = glm::vec4(color.r, color.g, color.b, 1.0);

    std::vector<Texture> diffuseMap = loadTexture(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMap.begin(), diffuseMap.end());

    //specular
    std::vector<Texture> specular = loadTexture(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specular.begin(), specular.end());
        
    //normal
    std::vector<Texture> normalMaps = loadTexture(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        
    //height
    std::vector<Texture> heightMaps = loadTexture(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    //return Mesh(verticies, textures, indicies);
    return Mesh(verticies, textures, indicies, mater);
}

std::vector<Texture> Model::loadTexture(aiMaterial* material, aiTextureType textureType, std::string typeName)
{
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < material->GetTextureCount(textureType); i++)
    {
        aiString str;
        material->GetTexture(textureType, i, &str);
        bool skip = false;

        for (unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }

        if (!skip)
        {
            Texture tex;
            tex.id = TextureFromFile(str.C_Str(), this->directory);
            tex.type = typeName;
            tex.path = str.C_Str();
            textures.push_back(tex);
            textures_loaded.push_back(tex);
        }
    }

    return textures;
}

void Model::draw(Shader& shader) 
{
   for(int i = 0; i < mesh.size(); i++)
   {
       //mesh[i].Draw(shader);
       mesh[i].DrawMaterial(shader);
   }
}

Model::~Model()
{
}

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma)
{
    std::string filename = std::string(path);
    filename = directory + "/" + filename;
    unsigned int textureId;

    glGenTextures(1, &textureId);
    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
        {
            format = GL_RED;
        }
        else if (nrComponents == 3)
        {
            format = GL_RGB;
        }
        else if (nrComponents == 4)
        {
            format = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else 
    {
        std::cerr << "Texture faild to load " << path << std::endl;
        stbi_image_free(data);
    }

    return textureId;
}