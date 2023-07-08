#include "GlobalIncludes.hpp"

class DebugObject : public GameObject {
    public:
    DebugObject(
        std::string name = "Default", 
        glm::vec3 position = glm::vec3(0, 0, 0), 
        glm::vec3 rotation = glm::vec3(0, 0, 0),
        glm::vec3 scale = glm::vec3(0, 0, 0));
    ~DebugObject();
    std::string ToString();
    void Update();
    void Draw();
};