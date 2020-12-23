//
// Created by Lado on 23/12/20.
//

#ifndef UNTITLED_MESH_H
#define UNTITLED_MESH_H

#include <iostream>
#include <string>
#include <vector>
#include "Shader.h"
#include "glad/include/glad.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

struct vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 texCoord;
};

struct texture {
    int id;
    std::string type;
};

class Mesh {
private:
    unsigned int VAO, VBO, EBO;
    void setupMesh();
public:
    std::vector<vertex> verticies;
    std::vector<texture> textures;
    std::vector<unsigned int> indicies;

    Mesh(std::vector<vertex> verticies, std::vector<texture> textures, std::vector<unsigned int> indicies);
    void Draw(Shader& shader);
};

Mesh::Mesh(std::vector<vertex> verticies, std::vector<texture> textures, std::vector<unsigned int> indicies)
{
    this->verticies = verticies;
    this->textures = textures;
    this->indicies = indicies;

    setupMesh();
}

void Mesh::setupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(vertex), &verticies[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned int),
                 &indicies[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, texCoord));

    glBindVertexArray(0);
}

void Mesh::Draw(Shader& shader)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);

        shader.setFloat(("material." + name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

#endif //UNTITLED_MESH_H
