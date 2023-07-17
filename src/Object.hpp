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
    std::string ToString();
    void Update();
    void Draw();
};