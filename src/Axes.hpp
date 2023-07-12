#include "GlobalIncludes.hpp"

class Axes : public GameObject {
    public:
    Axes(
        std::string name = "Default", 
        glm::vec3 position = glm::vec3(0, 0, 0), 
        glm::vec3 rotation = glm::vec3(0, 0, 0),
        glm::vec3 scale = glm::vec3(0, 0, 0));
    ~Axes();
    std::string ToString();
    void Update() override;
    void Draw();
};