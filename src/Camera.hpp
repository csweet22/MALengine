#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "GlobalIncludes.hpp"
#include "Framebuffer.hpp"

class Camera
{

protected:
    glm::mat4 M = glm::mat4(1.0f);
    glm::mat4 V = glm::lookAt(eye, glm::vec3(0), up);
    glm::mat4 P = glm::perspective(defaultFov, aspect, 0.001f, 1000.0f);
    glm::vec3 camera_dir = glm::vec3(0);
public:
    float defaultFov = 90.0f;
    float aspect = 1.0f;
    GLFWwindow* window;
    Framebuffer* framebuffer = nullptr;
    glm::vec3 eye = glm::vec3(1.0);
    glm::vec3 up = glm::vec3(0, 1.0, 0);
    glm::mat4 GetM() { return M; }
    glm::mat4 GetV() { return V; }
    glm::mat4 GetP() { return P; }
    Camera();
    ~Camera();
    glm::mat4 GetMVP() { return P * V * M; }
    virtual void Update();
};

#endif