#include "FakeBoid.hpp"


FakeBoid::FakeBoid(
    std::string _name,
    glm::vec3 _position, 
    glm::vec3 _rotation,
    glm::vec3 _scale){
        DEBUG_INFO("Created FakeBoid");
        this->name = _name;
        this->position =  glm::normalize(glm::vec3(rand() % 100 - 50, rand() % 100 - 50, rand() % 100 - 50)) * glm::vec3(rand() % 5);
        this->rotation = _rotation;
        this->scale = _scale;
        this->velocity = glm::vec3(rand() % 100 - 50, rand() % 100 - 50, rand() % 100 - 50);
        this->velocity = glm::normalize(this->velocity);
        
}

FakeBoid::~FakeBoid(){
    DEBUG_INFO("Destroyed FakeBoid");
}

void FakeBoid::Update(){
    
    // DEBUG_INFO( std::to_string(Time::getInstance().GetDeltaTime()) );

    position = position + velocity * glm::vec3(10) * glm::vec3(Time::getInstance().GetDeltaTime());
    // DEBUG_INFO(abs(glm::length(position)));
    if ( abs(glm::length(position)) > 5.0f ){
        velocity *= -1.0f;
    }

    this->Draw();
}


void FakeBoid::Draw() {
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_LINES);
        glVertex3f(position.x - scale.x, position.y - scale.y, position.z);
        glVertex3f(position.x + scale.x, position.y - scale.y, position.z);

        glVertex3f(position.x, position.y + scale.y, position.z);
        glVertex3f(position.x - scale.x, position.y - scale.y, position.z);

        glVertex3f(position.x, position.y + scale.y, position.z);
        glVertex3f(position.x + scale.x, position.y - scale.y, position.z);
    
    glEnd();
}

std::string FakeBoid::ToString(){
    return std::string("(") + std::to_string(this->guid) + " / " + (this->name) +"): " +  glm::to_string(this->position); 
}