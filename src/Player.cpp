#include "Player.hpp"


Player::Player(
    std::string _name,
    glm::vec3 _position, 
    glm::vec3 _rotation,
    glm::vec3 _scale) {
        DEBUG_INFO("Created Player");
        this->name = _name;
        this->position = _position;
        this->rotation = _rotation;
        this->scale = _scale;
}

Player::~Player(){
    DEBUG_INFO("Destroyed Player");
}

void Player::Update(){
    if (!CheckEnabled()) {return;}

    // DEBUG_INFO(this->ToString());
    this->Draw();

float speed = 0.001;

    // if (InputSystem::getInstance().getKeyPress(GLFW_KEY_W, GLFW_PRESS)){
    //     position = glm::vec3(position.x, position.y + speed, position.z);
    // }
    
    // if (InputSystem::getInstance().getKeyPress(GLFW_KEY_A, GLFW_PRESS)){
    //     position = glm::vec3(position.x - speed, position.y, position.z);
    // }
    
    // if (InputSystem::getInstance().getKeyPress(GLFW_KEY_S, GLFW_PRESS)){
    //     position = glm::vec3(position.x, position.y - speed, position.z);
    // }
    
    // if (InputSystem::getInstance().getKeyPress(GLFW_KEY_D, GLFW_PRESS)){
    //     position = glm::vec3(position.x + speed, position.y, position.z);
    // }


    
    // if (InputSystem::getInstance().getKeyPress(GLFW_KEY_Q, GLFW_PRESS)){
    //     position = glm::vec3(position.x, position.y, position.z - speed);
    // }
    
    // if (InputSystem::getInstance().getKeyPress(GLFW_KEY_E, GLFW_PRESS)){
    //     position = glm::vec3(position.x, position.y, position.z + speed);
    // }
    
    // if (InputSystem::getInstance().getKeyPress(GLFW_KEY_UP, GLFW_PRESS)){
    //     scale = glm::vec3(scale.x + speed, scale.y + speed, scale.z);
    // }
    
    // if (InputSystem::getInstance().getKeyPress(GLFW_KEY_DOWN, GLFW_PRESS)){
    //     scale = glm::vec3(scale.x - speed, scale.y - speed, scale.z);
    // }

}

void Player::Draw() {

    glColor3f(0.0, 1.0, 0.0);

    glBegin(GL_LINES);
        glVertex3f(position.x - scale.x, position.y - scale.y, position.z);
        glVertex3f(position.x + scale.x, position.y - scale.y, position.z);

        glVertex3f(position.x - scale.x, position.y + scale.y, position.z);
        glVertex3f(position.x + scale.x, position.y + scale.y, position.z);

        glVertex3f(position.x - scale.x, position.y + scale.y, position.z);
        glVertex3f(position.x - scale.x, position.y - scale.y, position.z);

        glVertex3f(position.x + scale.x, position.y + scale.y, position.z);
        glVertex3f(position.x + scale.x, position.y - scale.y, position.z);
        

        glVertex3f(position.x + scale.x, position.y + scale.y, position.z);
        glVertex3f(position.x - scale.x, position.y - scale.y, position.z);
    
    glEnd();
}

std::string Player::ToString(){
    return std::string("(") + std::to_string(this->guid) + " / " + (this->name) +"): \n\t" +  
        glm::to_string(this->position) + "\n\t" +
        glm::to_string(this->rotation) + "\n\t" +
        glm::to_string(this->scale) + "\n\t"; 
}