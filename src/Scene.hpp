#ifndef SCENE_HPP
#define SCENE_HPP
#include "GlobalIncludes.hpp"

class Scene{
    public:
        std::vector<GameObject*> gameObjects;
        Scene();
        ~Scene();
        std::vector<GameObject*>* getGameObjects();
        void addGameObject(GameObject* obj);
        void Update();
        void Draw();
};

#endif