//
// Created by 54367 on 2018/12/31.
//

#ifndef OPENGL_CAMERA_H
#define OPENGL_CAMERA_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>


enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;


    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = YAW,
           float pitch = PITCH);

    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);


    glm::mat4 getViewMatrix();

    //反转俯仰角
    void invertPitch();

    void ProcessKeyboard(Camera_Movement direction, float deltaTime);

    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = GL_TRUE);

    void ProcessMouseScroll(float yoffset);

    glm::vec3 &getPosition();

    void setPosition(const glm::vec3 &Position);

private:
    void updateCameraVectors();
};

#endif //OPENGL_CAMERA_H
