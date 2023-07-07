#include <string>
#include "GlobalIncludes.hpp"
#include "GameObject.hpp"

GameObject::GameObject(){
    name = "Default";
    position = glm::vec3(0, 0, 0);
    rotation = glm::vec3(0, 0, 0);
    scale = glm::vec3(1, 1, 1);
}

GameObject::~GameObject(){
    
}

void GameObject::Draw() {
    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_LINES);
        glVertex2f(position.x - scale.x, position.y - scale.y);
        glVertex2f(position.x + scale.x, position.y - scale.y);

        glVertex2f(position.x - scale.x, position.y + scale.y);
        glVertex2f(position.x + scale.x, position.y + scale.y);

        glVertex2f(position.x - scale.x, position.y + scale.y);
        glVertex2f(position.x - scale.x, position.y - scale.y);

        glVertex2f(position.x + scale.x, position.y + scale.y);
        glVertex2f(position.x + scale.x, position.y - scale.y);
        

        glVertex2f(position.x + scale.x, position.y + scale.y);
        glVertex2f(position.x - scale.x, position.y - scale.y);
    
    glEnd();
}

void GameObject::Update() {

    float speed = 0.001;

    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_W, GLFW_PRESS)){
        position = glm::vec3(position.x, position.y + speed, position.z);
    }
    
    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_A, GLFW_PRESS)){
        position = glm::vec3(position.x - speed, position.y, position.z);
    }
    
    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_S, GLFW_PRESS)){
        position = glm::vec3(position.x, position.y - speed, position.z);
    }
    
    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_D, GLFW_PRESS)){
        position = glm::vec3(position.x + speed, position.y, position.z);
    }

    
    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_UP, GLFW_PRESS)){
        scale = glm::vec3(scale.x + speed, scale.y + speed, scale.z);
    }
    
    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_DOWN, GLFW_PRESS)){
        scale = glm::vec3(scale.x - speed, scale.y - speed, scale.z);
    }

    Draw();
        
}