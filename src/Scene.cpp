#include "Scene.hpp"

Scene::Scene(){
    DEBUG_INFO("Created Scene");
}

Scene::~Scene(){
    DEBUG_INFO("Destroyed Scene");
    for (auto & gameObject : gameObjects) 
    {
        delete gameObject;
    }
}


std::vector<GameObject*>* Scene::getGameObjects(){
    return &(this->gameObjects);
}


void Scene::addGameObject(GameObject* obj){
    this->gameObjects.emplace_back(obj);
}

void Scene::Update(){   
    for (auto & gameObject : gameObjects) 
    {
        gameObject->Update();
    }
}