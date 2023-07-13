#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "GlobalIncludes.hpp"

class GameObject {
    public:
    GameObject() { this->guid = nextGUID++; }
    virtual void Update() { }
    bool CheckEnabled() { 


        if (parent != nullptr){
            GameObject* currentParent = this->parent;

            while(currentParent->parent != nullptr){
                currentParent = currentParent->parent;
                if(currentParent->enabled == false){
                    return false;
                }
            }

            if(!(parent->enabled)){
                return false;
            }
        }
        if (!enabled){
            return false;
        }
        return true;
    }
    virtual std::string ToString() {}
    std::string name = "default";
    glm::vec3 position = glm::vec3(0, 0, 0);
    glm::vec3 rotation = glm::vec3(0, 0, 0);
    glm::vec3 scale = glm::vec3(0, 0, 0);
    int guid;
    bool enabled = true;
    GameObject* parent = nullptr;
    void SetParent(GameObject* newParent){
        this->parent = newParent;
        this->parent->children.emplace_back(this);
    }
    std::vector<GameObject*> children;

};

#endif