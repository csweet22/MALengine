#include "OrbitalCamera.hpp"

OrbitalCamera::OrbitalCamera(){
    DEBUG_INFO("Created OrbitalCamera");
}

OrbitalCamera::~OrbitalCamera(){
    DEBUG_INFO("Destroyed OrbitalCamera");
}

void OrbitalCamera::Update(){

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
    
    V = glm::lookAt(eye, glm::vec3(0), up); 
    camera_dir = glm::vec3(0) - eye; 
}