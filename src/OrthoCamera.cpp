#include "OrthoCamera.hpp"

OrthoCamera::OrthoCamera(){
    DEBUG_INFO("Created OrthoCamera");
	eye = glm::vec3(0.0, 0.0, 1.0);
	camera_dir = glm::vec3(0, 0, -1.0);
}

OrthoCamera::~OrthoCamera(){
    DEBUG_INFO("Destroyed OrthoCamera");
}

void OrthoCamera::Update(){


    float speed = 0.05f;
    glm::vec3 right = glm::cross(camera_dir, up);

    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_W, GLFW_PRESS)){
        eye = eye +  glm::normalize(up) * speed;
    }
    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_S, GLFW_PRESS)){
        eye = eye - glm::normalize(up) * speed;
    }
    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_A, GLFW_PRESS)){
        eye = eye - glm::normalize(right) * speed;
    }
    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_D, GLFW_PRESS)){
        eye = eye + glm::normalize(right) * speed;
    }

    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_Q, GLFW_PRESS)){
        eye = eye - glm::vec3(0, 0, -1) * speed;
    }
    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_E, GLFW_PRESS)){
        eye = eye + glm::vec3(0, 0, -1) * speed;
    }

	if (eye.z < 0.1){
		eye.z = 0.1;
	}

	float newaspect = framebuffer->frameWidth / framebuffer->frameHeight;

    // P = glm::perspective(0.0001f, newaspect, 0.001f, 1000000000.0f);
	P = glm::ortho(
		-(50.0f) * newaspect * eye.z, 
		50.0f * newaspect * eye.z, 
        -50.0f  * eye.z,
		(50.0f)  * eye.z, 
      -10000.0f, 10000.0f);
	V = glm::lookAt(eye, eye + camera_dir, glm::vec3(0,1,0)); 
}