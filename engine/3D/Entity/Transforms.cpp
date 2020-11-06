//
// Created by Lado on 6/11/20.
//

#include "Transforms.h"

Transforms::Transforms() { }

Transforms::Transforms(glm::vec3 &pos, glm::vec3 &rot, glm::vec3 &scale) {
    this->pos = pos;
    this->rot = rot;
    this->scale = scale;
}

void Transforms::setPos(glm::vec3 &pos) {
    this->pos = pos;
}

void Transforms::setRot(glm::vec3 &rot) {
    this->rot = rot;
}

void Transforms::setScale(glm::vec3 &scale) {
    this->scale = scale;
}

glm::mat4 Transforms::getModel() {
    glm::mat4 translate = glm::translate(pos);
    glm::mat4 scaling = glm::scale(scale);

    glm::mat4 rotX = glm::rotate(rot.x, glm::vec3(1.0, 0.0, 0.0));
    glm::mat4 rotY = glm::rotate(rot.y, glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 rotZ = glm::rotate(rot.z, glm::vec3(0.0, 0.0, 1.0));

    glm::mat4 rotModel = rotX * rotY * rotZ;

    return translate * rotModel *scaling;
}

glm::vec3 * Transforms::getPos() {
    return &pos;
}

glm::vec3 * Transforms::getRot() {
    return &rot;
}

glm::vec3 * Transforms::getScale() {
    return &scale;
}

Transforms::~Transforms() {

}