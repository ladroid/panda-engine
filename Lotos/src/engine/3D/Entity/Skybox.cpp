#include "Skybox.h"

Skybox::Skybox(std::vector<std::string> path)
{
	skies.push_back(path[0]);
	skies.push_back(path[1]);
	skies.push_back(path[2]);
	skies.push_back(path[3]);
	skies.push_back(path[4]);
	skies.push_back(path[5]);

	this->textureID = 0;
	float textSize = 50.0f;

    this->skyVerticies = {
		// positions
        -textSize,  textSize, -textSize,
        -textSize, -textSize, -textSize,
        textSize, -textSize, -textSize,
        textSize, -textSize, -textSize,
        textSize,  textSize, -textSize,
        -textSize,  textSize, -textSize,

        -textSize, -textSize,  textSize,
        -textSize, -textSize, -textSize,
        -textSize,  textSize, -textSize,
        -textSize,  textSize, -textSize,
        -textSize,  textSize,  textSize,
        -textSize, -textSize,  textSize,

        textSize, -textSize, -textSize,
        textSize, -textSize,  textSize,
        textSize,  textSize,  textSize,
        textSize,  textSize,  textSize,
        textSize,  textSize, -textSize,
        textSize, -textSize, -textSize,

        -textSize, -textSize,  textSize,
        -textSize,  textSize,  textSize,
        textSize,  textSize,  textSize,
        textSize,  textSize,  textSize,
        textSize, -textSize,  textSize,
        -textSize, -textSize,  textSize,

        -textSize,  textSize, -textSize,
        textSize,  textSize, -textSize,
        textSize,  textSize,  textSize,
        textSize,  textSize,  textSize,
        -textSize,  textSize,  textSize,
        -textSize,  textSize, -textSize,

        -textSize, -textSize, -textSize,
        -textSize, -textSize,  textSize,
        textSize, -textSize, -textSize,
        textSize, -textSize, -textSize,
        -textSize, -textSize,  textSize,
        textSize, -textSize,  textSize
    };
}

Skybox::Skybox(std::vector<std::string> path, float size)
{
    std::cout << "Skybox " << path[0] << std::endl;
    skies.push_back(path[0]);
    skies.push_back(path[1]);
    skies.push_back(path[2]);
    skies.push_back(path[3]);
    skies.push_back(path[4]);
    skies.push_back(path[5]);

    this->textureID = 0;

    this->skyVerticies = {
        // positions
        -size,  size, -size,
        -size, -size, -size,
        size, -size, -size,
        size, -size, -size,
        size,  size, -size,
        -size,  size, -size,

        -size, -size,  size,
        -size, -size, -size,
        -size,  size, -size,
        -size,  size, -size,
        -size,  size,  size,
        -size, -size,  size,

        size, -size, -size,
        size, -size,  size,
        size,  size,  size,
        size,  size,  size,
        size,  size, -size,
        size, -size, -size,

        -size, -size,  size,
        -size,  size,  size,
        size,  size,  size,
        size,  size,  size,
        size, -size,  size,
        -size, -size,  size,

        -size,  size, -size,
        size,  size, -size,
        size,  size,  size,
        size,  size,  size,
        -size,  size,  size,
        -size,  size, -size,

        -size, -size, -size,
        -size, -size,  size,
        size, -size, -size,
        size, -size, -size,
        -size, -size,  size,
        size, -size,  size
    };
}

bool Skybox::loadCube()
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    int width, height, nrComponents;
    for (unsigned int i = 0; i < skies.size(); i++)
    {
        unsigned char* data = stbi_load(skies[i].c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cerr << "Could not load texture " << std::endl;
            stbi_image_free(data);
            return false;
        }
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}

void Skybox::buildSkybox()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(getVerticies()) * 108, getVerticies(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);  
}

void Skybox::renderSkybox()
{
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureID);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}

unsigned int Skybox::getTextureID()
{
    return this->textureID;
}

float* Skybox::getVerticies()
{
    return skyVerticies.data();
}

Skybox::~Skybox()
{
    glDeleteTextures(1, &textureID);
    textureID = 0;
}