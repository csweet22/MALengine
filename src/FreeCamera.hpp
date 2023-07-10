#ifndef FREECAMERA_HPP
#define FREECAMERA_HPP

#include "GlobalIncludes.hpp"
#include "Camera.hpp"

class FreeCamera : public Camera
{
public:
    FreeCamera();
    ~FreeCamera();
    void Update();
};

#endif