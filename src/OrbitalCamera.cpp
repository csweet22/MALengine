#include "OrbitalCamera.hpp"

OrbitalCamera::OrbitalCamera(){
    DEBUG_INFO("Created OrbitalCamera");
}

OrbitalCamera::~OrbitalCamera(){
    DEBUG_INFO("Destroyed OrbitalCamera");
}

void OrbitalCamera::Update(){

    glm::vec3 right = glm::cross( glm::normalize(camera_dir), glm::normalize(up));
    glm::vec3 updown = glm::cross(glm::normalize(camera_dir), glm::normalize(right));

    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_W, GLFW_PRESS)){
        eye = eye - updown * speed;
    }
    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_S, GLFW_PRESS)){
        eye = eye + updown * speed;
    }
    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_A, GLFW_PRESS)){
        eye = eye - right * speed;
    }
    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_D, GLFW_PRESS)){
        eye = eye + right * speed;
    }
    

    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_Q, GLFW_PRESS)){
        eye = eye + camera_dir * zoom_speed;
    }
    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_E, GLFW_PRESS)){
        eye = eye - camera_dir * zoom_speed;
    }

    
    V = glm::lookAt(eye, glm::vec3(0), up); 
    camera_dir = glm::vec3(0) - eye; 
}