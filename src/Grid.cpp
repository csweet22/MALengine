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
    int xsegments = 5;
    int ysegments = 1;
    int zsegments = 5;
    float scale = 1.0;
    glBegin(GL_LINES);
    
        glColor4f(0.0, 0.0, 0.0, 0.1);
        for(int x = -1 * (xsegments -1); x < xsegments; x++){
            for(int z = -1 * (zsegments -1); z < zsegments; z++){
                
                for(int y = -1 * (ysegments -1); y < ysegments; y++){
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