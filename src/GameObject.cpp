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

    Draw();
        
}