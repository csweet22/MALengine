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
    float deltaX = 0.0;
    float deltaY = 0.0;
    float prevX = 0.0;
    float prevY = 0.0;
    float currX = 0.0;
    float currY = 0.0;
};

#endif