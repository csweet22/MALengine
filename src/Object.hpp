#include "GlobalIncludes.hpp"

class Object : public GameObject {
    public:
    glm::vec3 velocity;
    glm::vec3 acceleration;
    Object(
        std::string name = "Default", 
        glm::vec3 position = glm::vec3(0, 0, 0), 
        glm::vec3 rotation = glm::vec3(0, 0, 0),
        glm::vec3 scale = glm::vec3(1, 1, 1));
    ~Object();
    virtual std::string ToString() {    return std::string("(") + std::to_string(this->guid) + " / " + (this->name) +"): " +  glm::to_string(this->position); }
    virtual void Update() { if (!CheckEnabled()) {return;} }
    virtual void Draw(){
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
};