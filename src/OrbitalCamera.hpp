#ifndef ORBITCAMERA_HPP
#define ORBITCAMERA_HPP

#include "GlobalIncludes.hpp"
#include "Camera.hpp"

class OrbitalCamera : public Camera
{
public:
    OrbitalCamera();
    ~OrbitalCamera();
    void Update();
    float speed = 0.002f;
    float zoom_speed = 0.005f;
};

#endif