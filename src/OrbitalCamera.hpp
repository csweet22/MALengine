#ifndef ORBITCAMERA_HPP
#define ORBITCAMERA_HPP

#include "GlobalIncludes.hpp"
#include "Camera.hpp"



class OrbitalCamera : public Camera
{
private:
	float r = 5.0;
	float theta = 3.1415 / 4;
	float phi = 5*sqrt(2) - 2*3.1415;
	
	float prev_xpos = 0.0f;
	float prev_ypos = 0.0f;
	double curr_xpos = 0.0f;
	double curr_ypos = 0.0f;

	float zoomSpeed = 10.0f;
	float moveSpeed = 0.6f;
public:
    OrbitalCamera();
    ~OrbitalCamera();
    void Update();
    float speed = 0.002f;
    float zoom_speed = 0.005f;
};

#endif