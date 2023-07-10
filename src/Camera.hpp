#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "GlobalIncludes.hpp"

class Camera
{

protected:
    glm::mat4 M = glm::mat4(10.0f);
    glm::mat4 V = glm::lookAt(eye, glm::vec3(0), up);
    glm::mat4 P = glm::perspective(glm::radians(90.0f), 1.0f / 1.0f, 0.001f, 1000.0f);
    glm::vec3 camera_dir = glm::vec3(0);
public:
    glm::vec3 eye = glm::vec3(1.0);
    glm::vec3 up = glm::vec3(0, 1.0, 0);
    glm::mat4 GetM() { return M; }
    glm::mat4 GetV() { return V; }
    glm::mat4 GetP() { return P; }
    glm::vec3 GetCameraDir() { return camera_dir; }
    Camera();
    ~Camera();
    glm::mat4 GetMVP() { return GetP() * GetV() * GetM(); }
    virtual void Update();
};

#endif