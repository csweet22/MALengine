#include "FreeCamera.hpp"

FreeCamera::FreeCamera(){
    DEBUG_INFO("Created FreeCamera");
    eye = glm::vec3(5.0);
    up = glm::vec3(0, 1.0, 0);
    camera_dir = glm::vec3(0) - eye;
}

FreeCamera::~FreeCamera(){
    DEBUG_INFO("Destroyed FreeCamera");
}

void FreeCamera::Update(){

    float speed = 0.005f;
    glm::vec3 right = glm::cross(camera_dir, up);

    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_W, GLFW_PRESS)){
        eye = eye + camera_dir * speed;
    }
    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_S, GLFW_PRESS)){
        eye = eye - camera_dir * speed;
    }
    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_A, GLFW_PRESS)){
        eye = eye - right * speed;
    }
    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_D, GLFW_PRESS)){
        eye = eye + right * speed;
    }

    
    if (InputSystem::getInstance().getMousePress(GLFW_MOUSE_BUTTON_RIGHT, GLFW_PRESS)){
        currX = InputSystem::getInstance().GetMousePosX();
        currY = InputSystem::getInstance().GetMousePosY();

        if (prevX != 0 && prevY != 0) {
            float deltaX = currX - prevX;
            float deltaY = currY - prevY;
            
            

            glm::mat4 rot_mat = glm::rotate( glm::mat4(1.0f), (float)(deltaX) * 1 * rot_speed, glm::vec3(0.0, 1.0, 0.0) );
            rot_mat = rot_mat * glm::rotate(glm::mat4(1.0f), (float)(deltaY) * 1 * rot_speed,  glm::cross(camera_dir, glm::vec3(0.0, 1.0, 0.0)) );

            camera_dir = glm::vec3(glm::vec4(camera_dir, 1.0f) * rot_mat);
        }

        prevX = currX;
        prevY = currY;
    } else {
        prevX = 0.0;
        prevY = 0.0;
    }

    
    int vpSize[2];
    glfwGetFramebufferSize(window, &vpSize[0], &vpSize[1]);

	float newaspect = (float)vpSize[0] / (float)vpSize[1];

    P = glm::perspective(defaultFov, newaspect, 0.001f, 1000.0f);
	V = glm::lookAt(eye, eye + camera_dir, glm::vec3(0,1,0)); 

}