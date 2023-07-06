#include "GlobalIncludes.hpp"

#include "Scene.hpp"
#include "GameObject.hpp"


class Application {
public:
    GLFWwindow* window;
    Scene mainScene;
    int screenW = 700;
    int screenH = 700;

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
        glClearColor(0.2f, 0.2f, 0.3f, 0.0f);

        // Enable depth testing.
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        
        DEBUG_INIT("OpenGL");
    }

    void SceneSetup(){

        GameObject testObj1;
        testObj1.name = "Obj 1";
        GameObject testObj2;
        testObj2.name = "Obj 2";

        mainScene.addGameObject(testObj1);
        mainScene.addGameObject(testObj2);
        
        for (auto & element : *(mainScene.getGameObjects())) 
        {
            DEBUG_LOG("Element Name: " + element.name);
        }
    }

    int Init(){
        InitGLFW();
        InitGLEW();
        InitGL();
        SceneSetup();

        do{
            
            mainScene.Update();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glfwSwapBuffers(window);
            glfwPollEvents();


        } while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
            glfwWindowShouldClose(window) == 0 );

        glfwTerminate();
        
        }
};
