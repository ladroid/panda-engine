//
// Created by Lado on 16/7/20.
//

#ifndef LOTOS_SHADER_H
#define LOTOS_SHADER_H

#include <fstream>
#include <sstream>
#include <iostream>
#include "glad/include/glad.h"
#include "EntityComponent3D.h"

class Shader : public Component {
public:
    unsigned int id;

    Shader(const char *vertexPath, const char *fragmentPath) {
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            vShaderFile.close();
            fShaderFile.close();
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        } catch (std::fstream::failure &e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const char *vShaderCode = vertexCode.c_str();
        const char *fShaderCode = fragmentCode.c_str();

        unsigned int vertex, fragment;
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);

        id = glCreateProgram();
        glAttachShader(id, vertex);
        glAttachShader(id, fragment);
        glLinkProgram(id);

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
    void use() {
        glUseProgram(id);
    }
    void setBool(const std::string &name, bool value) {
        glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
    }
    void setInt(const std::string &name, int value) {
        glUniform1f(glGetUniformLocation(id, name.c_str()), value);
    }
    ~Shader() {

    }
};

#endif //LOTOS_SHADER_H
