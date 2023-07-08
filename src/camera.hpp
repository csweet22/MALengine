
#ifndef CAMERA_HPP
#define CAMERA_HPP


#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

// This takes in a view matrix and moves it along spherical coordinates based on
// user inputs. It also uses delta time.
void globeCameraControls(glm::mat4& V) {
    double currentTime = glfwGetTime();
    static double lastTime = glfwGetTime();
    float deltaTime = (currentTime - lastTime);
    lastTime = currentTime;

	static float r = 5.0;
	static float theta = 3.1415 / 4;
	static float phi = 5*sqrt(2) - 2*3.1415;
	
	static float prev_xpos = 0.0f;
	static float prev_ypos = 0.0f;
	static double curr_xpos = 0.0f;
	static double curr_ypos = 0.0f;

	float zoomSpeed = 10.0f;
	float moveSpeed = 0.2f;

	// ===================================================================
	// Update camera r value
	// ===================================================================
	// if ( glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS ){
	// 	r -= zoomSpeed * deltaTime;
	// }
	// if ( glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS ){
	// 	r += zoomSpeed * deltaTime;
	// }

	if (r < 0.0) { r = 0.0; }

	// ===================================================================
	// Update camera theta and phi values
	// ===================================================================
	if ( glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS ){
		// Get the current mouse position
		glfwGetCursorPos(window, &curr_xpos, &curr_ypos);
		// If the previous position was (NULL,NULL), the mouse was not being held
		if (prev_xpos == NULL) {prev_xpos = curr_xpos;}
		if (prev_ypos == NULL) {prev_ypos = curr_ypos;}
		// Get the change in position between the previous frame
		double delta_xpos = curr_xpos - prev_xpos;
		double delta_ypos = curr_ypos - prev_ypos;
		// Set the previous position
		prev_xpos = curr_xpos;
		prev_ypos = curr_ypos;
		// Change theta and phi by change in mouse position
		theta += delta_xpos * moveSpeed * deltaTime;
		phi += delta_ypos * moveSpeed * deltaTime;

	} else {
		prev_xpos = NULL;
		prev_ypos = NULL;
	}
	
	// Clamp phi
	if (phi < -3.1415/2) { phi = -3.1415/2; }
	if (phi > 3.1415/2) { phi = 3.1415/2; }

	// ===================================================================
	// Update camera position based on Azimuth, Inclination, and Zoom
	// ===================================================================
	// Azimuth is phi
	// Inclination is theta
	// Convert spherical coordinate to cartesian coordinate
	float newX = r * cos(phi) * cos(theta);
	float newY = r * sin(phi);
	float newZ = r * cos(phi) * sin(theta);
	
	V = glm::lookAt(glm::vec3(newX, newY, newZ), glm::vec3(0,0,0), glm::vec3(0,1,0)); 
}

#endif