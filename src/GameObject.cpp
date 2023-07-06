#include "GameObject.hpp"

GameObject::GameObject(){
    name = "Default";
    position = glm::vec3(0, 0, 0);
    rotation = glm::vec3(0, 0, 0);
    scale = glm::vec3(1, 1, 1);
}

GameObject::~GameObject(){
    
}

void GameObject::Update(){
    if (InputSystem::getInstance().getKeyPress(GLFW_KEY_W, GLFW_PRESS)){
        // std::string msg = name + ": (" + position.x + "," + position.y + "," + position.z + ")";
        DEBUG_LOG(name);
    }
        
}