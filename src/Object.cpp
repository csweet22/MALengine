#include "Object.hpp"


Object::Object(
    std::string _name,
    glm::vec3 _position, 
    glm::vec3 _rotation,
    glm::vec3 _scale){
        DEBUG_INFO("Created Object");
        this->name = _name;
        this->position = _position;
        this->rotation = _rotation;
        this->scale = _scale;
}

Object::~Object(){
    DEBUG_INFO("Destroyed Object");
}

void Object::Update(){
    if (!CheckEnabled()) {return;}
}


void Object::Draw() {
    if (!CheckEnabled()) {return;}
    
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

std::string Object::ToString(){
    return std::string("(") + std::to_string(this->guid) + " / " + (this->name) +"): " +  glm::to_string(this->position); 
}