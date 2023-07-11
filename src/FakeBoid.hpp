#include "GlobalIncludes.hpp"

class FakeBoid : public GameObject {
    public:
    glm::vec3 velocity;
    glm::vec3 startPos;
    glm::vec3 goal;
    glm::vec3 goal2;
    float amount = 0.0;
    FakeBoid(
        std::string name = "Default", 
        glm::vec3 position = glm::vec3(0, 0, 0), 
        glm::vec3 rotation = glm::vec3(0, 0, 0),
        glm::vec3 scale = glm::vec3(0, 0, 0));
    ~FakeBoid();
    std::string ToString();
    void Update();
    void Draw();
};