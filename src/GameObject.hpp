#ifndef GAMEOBJ_HPP
#define GAMEOBJ_HPP

#include <string>
#include "GlobalIncludes.hpp"

class GameObject{
    public:
        GameObject();
        ~GameObject();
        std::string name;
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

        void Update();
};

#endif