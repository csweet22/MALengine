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
};

#endif