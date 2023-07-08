#include "DebugObject.hpp"


DebugObject::DebugObject(
    std::string _name,
    glm::vec3 _position, 
    glm::vec3 _rotation,
    glm::vec3 _scale){
        DEBUG_INFO("Created DebugObject");
        this->name = _name;
        this->position = _position;
        this->rotation = _rotation;
        this->scale = _scale;
}

DebugObject::~DebugObject(){
    DEBUG_INFO("Destroyed DebugObject");
}

void DebugObject::Update(){
    // DEBUG_INFO(this->ToString());
    this->Draw();
}


void DebugObject::Draw() {
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

std::string DebugObject::ToString(){
    return std::string("(") + std::to_string(this->guid) + " / " + (this->name) +"): " +  glm::to_string(this->position); 
}