#include "Camera.hpp"

Camera::Camera(){
    DEBUG_INFO("Created Camera");
}

Camera::~Camera(){
    DEBUG_INFO("Destroyed Camera");
}

void Camera::Update(){

    float speed = 0.005f;
    glm::vec3 right = glm::cross(GetCameraDir(), up);

    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_UP, GLFW_PRESS)){
        eye = eye + (GetCameraDir()) * speed;
    }
    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_DOWN, GLFW_PRESS)){
        eye = eye - GetCameraDir() * speed;
    }
    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_LEFT, GLFW_PRESS)){
        eye = eye - right * speed;
    }
    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_RIGHT, GLFW_PRESS)){
        eye = eye + right * speed;
    }
}