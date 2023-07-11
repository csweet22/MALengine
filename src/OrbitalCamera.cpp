#include "OrbitalCamera.hpp"

OrbitalCamera::OrbitalCamera(){
    DEBUG_INFO("Created OrbitalCamera");
}

OrbitalCamera::~OrbitalCamera(){
    DEBUG_INFO("Destroyed OrbitalCamera");
}

void OrbitalCamera::Update(){

    double deltaTime = Time::getInstance().GetDeltaTime();

    

	if ( InputSystem::getInstance().getKeyPress(GLFW_KEY_UP, GLFW_PRESS) ){
		r -= zoomSpeed * deltaTime;
	}
	if ( InputSystem::getInstance().getKeyPress(GLFW_KEY_DOWN, GLFW_PRESS) ){
		r += zoomSpeed * deltaTime;
	}

	if (r < 0.0) { r = 0.0; }


	if ( InputSystem::getInstance().getMousePress(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS) ){

        curr_xpos = InputSystem::getInstance().GetMousePosX();
        curr_ypos = InputSystem::getInstance().GetMousePosY();
        
		if (prev_xpos == NULL) {prev_xpos = curr_xpos;}
		if (prev_ypos == NULL) {prev_ypos = curr_ypos;}
        
		double delta_xpos = curr_xpos - prev_xpos;
		double delta_ypos = curr_ypos - prev_ypos;
        
		prev_xpos = curr_xpos;
		prev_ypos = curr_ypos;
        
		theta += delta_xpos * moveSpeed * deltaTime;
		phi += delta_ypos * moveSpeed * deltaTime;

	} else {
		prev_xpos = NULL;
		prev_ypos = NULL;
	}
	
	if (phi < -3.1415/2) { phi = -3.1415/2; }
	if (phi > 3.1415/2) { phi = 3.1415/2; }

	float newX = r * cos(phi) * cos(theta);
	float newY = r * sin(phi);
	float newZ = r * cos(phi) * sin(theta);
	
    int vpSize[2];
    glfwGetFramebufferSize(window, &vpSize[0], &vpSize[1]);

	float newaspect = (float)vpSize[0] / (float)vpSize[1];

    P = glm::perspective(defaultFov, newaspect, 0.001f, 1000.0f);
	V = glm::lookAt(glm::vec3(newX, newY, newZ), glm::vec3(0,0,0), glm::vec3(0,1,0)); 
}