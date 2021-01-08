//
//// Created by Lado on 9/8/20.
//

#ifndef LOTOS_TEXTURE_H
#define LOTOS_TEXTURE_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
//#include "/usr/local/Cellar/glfw/3.3.2/include/GLFW/glfw3.h"
//#include "EntityComponent3D.h"
#include <iostream>
#include <string>
#include "../../panda-engine-windows/Lotos/stb_image.h"

class Texture {
private:
    GLuint id;
public:
    Texture();
    bool loading(const char *path);
    void bind(int index = 0) {
        if(id != 0) {
            glActiveTexture(GL_TEXTURE0 + index);
            glBindTexture(GL_TEXTURE_2D, id);
        }
    }
    ~Texture();
};


#endif //LOTOS_TEXTURE_H