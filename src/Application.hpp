#include "GlobalIncludes.hpp"

#include "Scene.hpp"
#include "Player.hpp"
#include "DebugObject.hpp"
#include "PlaneMesh.hpp"
#include "OrbitalCamera.hpp"
#include "FreeCamera.hpp"
#include "Axes.hpp"
#include "Grid.hpp"



class Application {
public:
    GLFWwindow* window;
    Camera* camera;
    Scene mainScene;
    int screenW = 800;
    int screenH = screenW * 1.0 / 1.0;
    Application(){ DEBUG_INIT("Application"); }
    ~Application(){}
    void InitGLEW();
    void InitGLFW();
    void InitGL();
    void InitCamera(GLFWwindow* _window);
    void InitInput(GLFWwindow* _window);
    void InitImGui(GLFWwindow* _window);
    void SceneSetup();
    int Run();
};
