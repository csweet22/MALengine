#include "GlobalIncludes.hpp"

#include "Scene.hpp"
#include "Player.hpp"
#include "DebugObject.hpp"
#include "PlaneMesh.hpp"
#include "SphereMesh.hpp"
#include "OrbitalCamera.hpp"
#include "OrthoCamera.hpp"
#include "FreeCamera.hpp"
#include "Axes.hpp"
#include "Grid.hpp"
#include "FakeBoid.hpp"
#include "Framebuffer.hpp"
#include "Object.hpp"



class Application {
public:
    GLFWwindow* window;
    Camera* camera;
    std::vector<Camera*> cameraList;
    int camIndex = 0;
    Scene mainScene;
    int screenH = 900;
    int screenW = screenH * 1.3;
    
    PlaneMesh* mesh;

    float* appFramerate;

    bool show_demo_window = true;
    bool show_another_window = false;    
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    Application(){ DEBUG_INIT("Application"); }
    ~Application(){}
    void InitGLEW();
    void InitGLFW();
    void InitGL();
    void InitCamera(GLFWwindow* _window, Framebuffer* _framebuffer);
    void InitInput(GLFWwindow* _window);
    void InitImGui(GLFWwindow* _window);
    void SceneSetup();
    int Run();
};
