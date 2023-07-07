#ifndef GAMEOBJ_HPP
#define GAMEOBJ_HPP

#include <string>
#include "GlobalIncludes.hpp"

class GameObject {
    public:
        GameObject();
        ~GameObject();
        virtual void Update();
        virtual void Draw();
        
        std::string name = "Default";
        glm::vec3 position = glm::vec3(0, 0, 0);
        glm::vec3 rotation = glm::vec3(0, 0, 0);
        glm::vec3 scale = glm::vec3(1, 1, 1);
};

#endif