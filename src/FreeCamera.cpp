#include "FreeCamera.hpp"

FreeCamera::FreeCamera(){
    DEBUG_INFO("Created FreeCamera");
}

FreeCamera::~FreeCamera(){
    DEBUG_INFO("Destroyed FreeCamera");
}

void FreeCamera::Update(){

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