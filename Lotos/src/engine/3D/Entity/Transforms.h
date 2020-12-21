//
//// Created by Lado on 6/11/20.
//

//
// Created by Lado on 6/11/20.
//

#ifndef UNTITLED_TRANSFORMS_H
#define UNTITLED_TRANSFORMS_H

#include "glm.hpp"
#include "gtx/transform.hpp"

class Transforms {
private:
    glm::vec3 pos;
    glm::vec3 rot;
    glm::vec3 scale;
public:
    Transforms();
    Transforms(glm::vec3& pos, glm::vec3& rot, glm::vec3& scale);
    void setPos(glm::vec3& pos);
    void setRot(glm::vec3& rot);
    void setScale(glm::vec3& scale);
    glm::mat4 getModel();
    glm::vec3* getPos();
    glm::vec3* getRot();
    glm::vec3* getScale();
    ~Transforms();

};

#endif //UNTITLED_TRANSFORMS_H
