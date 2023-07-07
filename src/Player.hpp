#include "GlobalIncludes.hpp"
#include "GameObject.hpp"

class Player : public GameObject {
    public:
        Player();
        ~Player();
        void Update();
        void Draw();
};