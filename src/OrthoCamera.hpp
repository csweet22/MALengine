#pragma once

#include "GlobalIncludes.hpp"
#include "Camera.hpp"



class OrthoCamera : public Camera
{
public:
    OrthoCamera();
    ~OrthoCamera();
    void Update();
};
