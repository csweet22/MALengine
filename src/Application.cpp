#include "GlobalIncludes.hpp"

#include "Scene.hpp"
#include "Player.hpp"
#include "DebugObject.hpp"
#include "PlaneMesh.hpp"
#include "Camera.hpp"
#include "Axes.hpp"
#include "Grid.hpp"



class Application {
public:
    GLFWwindow* window;
    Camera* camera;
    Scene mainScene;
    int screenW = 800;
    int screenH = screenW * 1.0 / 1.0;

    Application(){
        DEBUG_LOG("Created Application"); 
    }
    
    ~Application(){

    }

    void InitGLEW(){
        // Initialize GLEW
        glewExperimental = true; // Needed for core profile
        if (glewInit() != GLEW_OK) {
            fprintf(stderr, "Failed to initialize GLEW\n");
            getchar();
            glfwTerminate();
        }
        DEBUG_INIT("GLEW");
    }

    void InitGLFW(){
        if( !glfwInit() )
        {
            fprintf( stderr, "Failed to initialize GLFW\n" );
            getchar();
        }

        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);

        // Open a window and create its OpenGL context
        window = glfwCreateWindow( screenW, screenH, "Ash Engine", NULL, NULL);

        if( window == NULL ){
            fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
            getchar();
            glfwTerminate();
        }
        glfwMakeContextCurrent(window);

        // Ensure we can capture the escape key being pressed below
        glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

        DEBUG_INIT("GLFW");
    }

    void InitGL(){
        // Dark blue background
        glClearColor(0.3f, 0.3f, 0.4f, 0.0f);

        // Enable depth testing.
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        DEBUG_INIT("OpenGL");
    }

    void InitCamera(){
        camera = new Camera();
    }

    void SceneSetup(){

        Player* player = new Player("Player", glm::vec3(0), glm::vec3(0), glm::vec3(1.0));
        DebugObject* debugObj = new DebugObject("Debug", glm::vec3(2), glm::vec3(0), glm::vec3(2, 1, 1));
        PlaneMesh* mesh = new PlaneMesh();
        mesh->cam = camera;
        Axes* axes = new Axes("Axes", glm::vec3(0), glm::vec3(0), glm::vec3(2));
        Grid* grid = new Grid("Grid", glm::vec3(0), glm::vec3(0), glm::vec3(2));

        mainScene.addGameObject(player);
        mainScene.addGameObject(debugObj);
        mainScene.addGameObject(mesh);
        mainScene.addGameObject(axes);
        mainScene.addGameObject(grid);
        
    }

    int Run(){
        InitGLFW();
        InitGLEW();
        InitGL();
        InitCamera();

        InputSystem::getInstance().setWindow(window);

        SceneSetup();

        do{
            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            

            
            glMatrixMode ( GL_PROJECTION );
            glLoadIdentity ();
            glLoadMatrixf(glm::value_ptr(camera->GetP()));

            
            glMatrixMode ( GL_MODELVIEW );
            glLoadIdentity ();
            glLoadMatrixf(glm::value_ptr(camera->GetV() * camera->GetM()));

            camera->Update();
            mainScene.Update();

            glfwSwapBuffers(window);
            glfwPollEvents();


        } while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
            glfwWindowShouldClose(window) == 0 );

        delete camera;

        glfwTerminate();
        
        }
};
