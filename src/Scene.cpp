#include "Scene.hpp"

Scene::Scene(){
    // Logger::GetInstance("CreationLog")->Log("Scene Created!");
}

Scene::~Scene(){
    // Logger::GetInstance("CreationLog")->Log("Scene Destroyed!");
    
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