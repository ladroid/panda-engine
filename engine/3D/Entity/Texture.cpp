//
// Created by Lado on 9/8/20.
//

#include "Texture.h"

Texture::Texture() : id(0) {}

bool Texture::loading(const char *path) {
    int width, height, components;
    if(path == NULL) {
        std::cout << "Failed :(" << std::endl;
        return false;
    }
    bool is_loaded = false;
    unsigned char *data = stbi_load(path, &width, &height, &components, 0);
    if(data != nullptr) {
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glTexStorage2D(GL_TEXTURE_2D, 2, GL_RGB8, width, height);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {
        std::cout << "Failed to load texture :(" << std::endl;
    }
    stbi_image_free(data);
    return is_loaded;
}

Texture::~Texture() noexcept {
    if(id != 0) {
        glDeleteTextures(1, &id);
        id = 0;
    }
}