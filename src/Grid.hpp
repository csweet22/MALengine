#include "GlobalIncludes.hpp"

class Grid : public GameObject {
    public:
    Grid(
        std::string name = "Default", 
        glm::vec3 position = glm::vec3(0, 0, 0), 
        glm::vec3 rotation = glm::vec3(0, 0, 0),
        glm::vec3 scale = glm::vec3(0, 0, 0));
    ~Grid();
    std::string ToString();
    void Update();
    void Draw();
};