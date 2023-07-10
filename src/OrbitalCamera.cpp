#include "OrbitalCamera.hpp"

OrbitalCamera::OrbitalCamera(){
    DEBUG_INFO("Created OrbitalCamera");
}

OrbitalCamera::~OrbitalCamera(){
    DEBUG_INFO("Destroyed OrbitalCamera");
}

float DistanceToOrigin(glm::vec3 point){
    return sqrt( point.x*point.x + point.y*point.y + point.z*point.z);
}

void OrbitalCamera::Update(){

    glm::vec3 right = glm::cross( glm::normalize(camera_dir), glm::normalize(up));
    right = glm::normalize(right);
    glm::vec3 updown = glm::cross(glm::normalize(camera_dir), glm::normalize(right));
    updown = glm::normalize(updown);

    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_W, GLFW_PRESS)){
        eye = eye - updown * speed * DistanceToOrigin(eye);
    }
    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_S, GLFW_PRESS)){
        eye = eye + updown * speed * DistanceToOrigin(eye);
    }
    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_A, GLFW_PRESS)){
        eye = eye - right * speed * DistanceToOrigin(eye);
    }
    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_D, GLFW_PRESS)){
        eye = eye + right * speed * DistanceToOrigin(eye);
    }
    

    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_Q, GLFW_PRESS)){
        eye = eye + camera_dir * zoom_speed;
    }
    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_E, GLFW_PRESS)){
        eye = eye - camera_dir * zoom_speed;
    }

    // spherical coord calculations
    // x = r * sin(theta) * cos(phi)
    // y = r * sin(theta) * sin(phi)
    // z = r * cos(theta)

    V = glm::lookAt(eye, glm::vec3(0), up); 
    camera_dir = glm::normalize(glm::vec3(0) - eye); 
}