#include "Scene.hpp"

Scene::Scene(){
}

Scene::~Scene(){
}


std::vector<GameObject>* Scene::getGameObjects(){
    return &(this->gameObjects);
}


void Scene::addGameObject(GameObject obj){
    this->gameObjects.emplace_back(obj);
}

void Scene::Update(){
    
    for (auto & gameObject : gameObjects) 
    {
        gameObject.Update();
    }
}