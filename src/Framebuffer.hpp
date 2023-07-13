#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include "GlobalIncludes.hpp"

class Framebuffer
{
public:
    Framebuffer();
    ~Framebuffer();
    void CreateFramebuffer(float width, float height);
    void BindFramebuffer();
    void UnbindFramebuffer();
    void RescaleFramebuffer(float width, float height);
    GLuint FBO;
    GLuint RBO;
    GLuint textureID;
    float frameWidth;
    float frameHeight;
};

#endif