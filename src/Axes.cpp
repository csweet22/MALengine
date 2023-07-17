#include "Axes.hpp"


Axes::Axes(
    std::string _name,
    glm::vec3 _position, 
    glm::vec3 _rotation,
    glm::vec3 _scale){
        DEBUG_INFO("Created Axes");
        this->name = _name;
        this->position = _position;
        this->rotation = _rotation;
        this->scale = _scale;
}

Axes::~Axes(){
    DEBUG_INFO("Destroyed Axes");
}

void Axes::Update(){
    if (!CheckEnabled()) {return;}
    // DEBUG_INFO(this->ToString());
}


void Axes::Draw() {
    if (!CheckEnabled()) {return;}
    glBegin(GL_LINES);
    
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(position.x, position.y, position.z);
        glVertex3f(position.x + scale.x, position.y, position.z);
    
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(position.x, position.y, position.z);
        glVertex3f(position.x, position.y + scale.y, position.z);
    
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(position.x, position.y, position.z);
        glVertex3f(position.x, position.y, position.z  + scale.z);

    
    glEnd();
}

std::string Axes::ToString(){
    return std::string("(") + std::to_string(this->guid) + " / " + (this->name) +"): " +  glm::to_string(this->position); 
}