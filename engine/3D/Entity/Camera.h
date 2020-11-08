//
// Created by Lado on 8/11/20.
//

#ifndef UNTITLED_CAMERA_H
#define UNTITLED_CAMERA_H

#include "glad/include/glad.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

enum camera_movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSETIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
private:
    void updateCameraVector() {
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(direction);
        right = glm::normalize(glm::cross(front, world_up));
        up = glm::normalize(glm::cross(right, front));
    }

public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;
    float yaw;
    float pitch;
    float movement_speed;
    float mouse_sensetivity;
    float zoom;

    Camera() {}
    Camera(glm::vec3 pos, glm::vec3 world_up, float yaw = YAW, float pitch = PITCH) {
        position = pos;
        this->world_up = world_up;
        this->yaw = yaw;
        this->pitch = pitch;

        front = glm::vec3(0.0f, 0.0f, -1.0f);
        movement_speed = SPEED;
        mouse_sensetivity = SENSETIVITY;
        zoom = ZOOM;

        updateCameraVector();
    }

    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pith) {
        position = glm::vec3(posX, posY, posZ);
        world_up = glm::vec3(upX, upY, upZ);
        this->yaw = yaw;
        this->pitch = pitch;

        front = glm::vec3(0.0f, 0.0f, -1.0f);
        movement_speed = SPEED;
        mouse_sensetivity = SENSETIVITY;
        zoom = ZOOM;

        updateCameraVector();
    }

    glm::mat4 GetViewMatrix() {
        return glm::lookAt(position, position + front, up);
    }

    void InputHandlerKeyboard(camera_movement direction, float deltaTime) {
        float velocity = movement_speed * deltaTime;
        if(direction == FORWARD) {
            position += front * velocity;
        }
        else if(direction == BACKWARD) {
            position -= front * velocity;
        }
        else if(direction == LEFT) {
            position -= right * velocity;
        }
        else {
            position += right * velocity;
        }
    }

    void InputHandlerMouse(float xoffset, float yoffset, GLboolean constrainPitch = true) {
        xoffset *= mouse_sensetivity;
        yoffset *= mouse_sensetivity;

        yaw += xoffset;
        pitch += yoffset;

        if(constrainPitch) {
            if(pitch > 89.0f) {
                pitch = 89.0f;
            }
            if(pitch < -89.0f) {
                pitch = -89.0f;
            }
        }
        updateCameraVector();
    }

    void InputHandlerMouseZoom(float yoffset) {
        if(zoom > 1.0f && zoom <= 45.0f) {
            zoom -= yoffset;
        }
        else if(zoom <= 1.0f) {
            zoom = 1.0f;
        }
        else if(zoom >= 45.0f) {
            zoom = 45.0f;
        }
    }

    ~Camera() {  }
};

#endif //UNTITLED_CAMERA_H
