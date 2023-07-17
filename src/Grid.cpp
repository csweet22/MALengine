#include "Grid.hpp"


Grid::Grid(
    std::string _name,
    glm::vec3 _position, 
    glm::vec3 _rotation,
    glm::vec3 _scale){
        DEBUG_INFO("Created Grid");
        this->name = _name;
        this->position = _position;
        this->rotation = _rotation;
        this->scale = _scale;
}

Grid::~Grid(){
    DEBUG_INFO("Destroyed Grid");
}

void Grid::Update(){
    if (!CheckEnabled()) {return;}
    // DEBUG_INFO(this->ToString());
}


void Grid::Draw() {
    if (!CheckEnabled()) {return;}
    int segments = 5;
    float scale = 1.0;
    glBegin(GL_LINES);
    
        glColor4f(0.0, 0.0, 0.0, 0.2);
        for(int x = -1 * (segments -1); x < segments; x++){
            for(int z = -1 * (segments -1); z < segments; z++){
                
                for(int y = -1 * (segments -1); y < segments; y++){
                    glVertex3f(x, y, -1 * z);
                    glVertex3f(x, y, z);
                    
                    glVertex3f(-1 * x, y, z);
                    glVertex3f(x, y, z);

                    
                    glVertex3f(x, -y, z);
                    glVertex3f(x, y, z);
                }
                // glVertex3f(x, 0, -1 * z);
                // glVertex3f(x, 0, z);
                
                // glVertex3f(-1 * x, 0, z);
                // glVertex3f(x, 0, z);
            }
        }

    
    glEnd();
}

std::string Grid::ToString(){
    return std::string("(") + std::to_string(this->guid) + " / " + (this->name) +"): " +  glm::to_string(this->position); 
}