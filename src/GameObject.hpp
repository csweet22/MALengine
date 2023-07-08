#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "GlobalIncludes.hpp"

class GameObject {
    public:
    GameObject() { this->guid = nextGUID++; }
    virtual void Update() {}
    virtual std::string ToString() {}
    std::string name = "default";
    glm::vec3 position = glm::vec3(0, 0, 0);
    glm::vec3 rotation = glm::vec3(0, 0, 0);
    glm::vec3 scale = glm::vec3(0, 0, 0);
    int guid;

};

#endif