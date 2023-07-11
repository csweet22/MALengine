#include "Application.hpp"

void Application::InitGLEW(){
    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
    }
    DEBUG_INIT("GLEW");
}

void Application::InitGLFW(){
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);

    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

void Application::InitGL(){
    // Dark blue background
    glClearColor(0.3f, 0.3f, 0.4f, 0.0f);

    // Enable depth testing.
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    DEBUG_INIT("OpenGL");
}

void Application::InitCamera(GLFWwindow* _window){
    camera = new OrbitalCamera();
    // camera = new FreeCamera();
    camera->window = _window;
}

void Application::InitInput(GLFWwindow* _window){
    InputSystem::getInstance().Init(_window);
    DEBUG_INIT("Input");
}

void Application::InitImGui(GLFWwindow* _window){
    

}

void Application::SceneSetup(){

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

void framebuffer_size_callback(GLFWwindow *_window, int width, int height){
    int vpSize[2];
    glfwGetFramebufferSize(_window, &vpSize[0], &vpSize[1]);
    glViewport(0, 0, vpSize[0], vpSize[1]);
}

int Application::Run(){
    InitGLFW();
    
    
    const char* glsl_version = "#version 400";
    // // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // //ImGui::StyleColorsLight();

    // // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    
    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;    
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    InitGLEW();
    InitGL();
    InitCamera(window);
    InitInput(window);


    SceneSetup();

    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    do{

// Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (true)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        
        glMatrixMode ( GL_PROJECTION );
        glLoadIdentity ();
        glLoadMatrixf(glm::value_ptr(camera->GetP()));

        
        glMatrixMode ( GL_MODELVIEW );
        glLoadIdentity ();
        glLoadMatrixf(glm::value_ptr(camera->GetV() * camera->GetM()));

        camera->Update();
        mainScene.Update();
        // DEBUG_INFO( std::to_string( Time::getInstance().GetDeltaTime() ) );

        
        // Rendering
        ImGui::Render();
        // int display_w, display_h;
        // glfwGetFramebufferSize(window, &display_w, &display_h);
        // glViewport(0, 0, display_w, display_h);
        // glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();


    } while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0 );

    delete camera;

    glfwTerminate();
    
}

