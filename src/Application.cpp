#include "Application.hpp"

void framebuffer_size_callback(GLFWwindow *_window, int width, int height){
    int vpSize[2];
    glfwGetFramebufferSize(_window, &vpSize[0], &vpSize[1]);
    glViewport(0, 0, vpSize[0], vpSize[1]);
}

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
    Camera* fc = new FreeCamera();
    fc->window = _window;
    cameraList.emplace_back(fc);

    Camera* oc = new OrbitalCamera();
    oc->window = _window;
    cameraList.emplace_back(oc);
    
    camera = cameraList.at(camIndex);
    camera->window = _window;
}

void Application::InitInput(GLFWwindow* _window){
    InputSystem::getInstance().Init(_window);
    DEBUG_INIT("Input");
}

void Application::InitImGui(GLFWwindow* _window){
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
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void Application::SceneSetup(){

    Player* player = new Player("Player", glm::vec3(0), glm::vec3(0), glm::vec3(1.0));
    DebugObject* debugObj = new DebugObject("Debug", glm::vec3(0), glm::vec3(0), glm::vec3(0.4));
    mesh = new PlaneMesh(-4.0, 4.0, 0.2);
    // mesh = new SphereMesh(4, 32, 32);
    mesh->cam = camera;
    mesh->name = "Plane Mesh";
    Axes* axes = new Axes("Axes", glm::vec3(0), glm::vec3(0), glm::vec3(2));
    Grid* grid = new Grid("Grid", glm::vec3(0), glm::vec3(0), glm::vec3(2));
    // axes->enabled = false;

    // mainScene.addGameObject(player);
    mainScene.addGameObject(debugObj);
    mainScene.addGameObject(mesh);
    mainScene.addGameObject(axes);
    mainScene.addGameObject(grid);


    int boidCount = 50;

    for(int i = 0; i < boidCount; i++){
        FakeBoid* fb = new FakeBoid("Boyd!" + std::to_string(i), glm::vec3(0), glm::vec3(0), glm::vec3(0.05));
        fb->SetParent(debugObj);
        mainScene.addGameObject(fb);
        
        for(int j = 0; j < boidCount; j++){
            FakeBoid* fb2 = new FakeBoid("Boyd!" + std::to_string(i) + std::to_string(j + boidCount), glm::vec3(0), glm::vec3(0), glm::vec3(0.05));
            fb2->SetParent(fb);
            mainScene.addGameObject(fb2);
        }
    }

    
}

void recursiveTreeFill(GameObject* currentObject){
    if (ImGui::TreeNode(currentObject->name.c_str())){
        ImGui::Checkbox("Enabled", &(currentObject->enabled));
        for(auto & child : currentObject->children){
            recursiveTreeFill(child);
        }
        ImGui::TreePop();
        
    }
    

    // if (currentObject->children.size() > 0){
    //     for(auto & child : currentObject->children){
            // if (ImGui::TreeNode(child->name.c_str()))
            // {
            //     // ImGui::Text("Enabled:");
            //     // ImGui::SameLine();
            //     ImGui::Checkbox("Enabled", &(child->enabled));
            //     recursiveTreeFill(child);
            //     ImGui::TreePop();

    //         }
    //     }
    // }
     
}

int Application::Run(){

    srand (time(NULL));

    InitGLFW();
    InitImGui(window);
    InitGLEW();
    InitGL();
    InitCamera(window);
    InitInput(window);

    SceneSetup();

        

    do{

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        static int pressed = 1;

        if (InputSystem::getInstance().getKeyPress(GLFW_KEY_R, GLFW_PRESS) && pressed){
            pressed = 0;
            camera = cameraList.at((++camIndex) % cameraList.size());
            mesh->cam = camera;
        }
        if(InputSystem::getInstance().getKeyPress(GLFW_KEY_R, GLFW_RELEASE)){
            pressed = 1;
        }

        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

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

            if (ImGui::TreeNode("Basic trees"))
            {
                GameObject* currObject = mainScene.getGameObjects()->at(0);
                std::vector<GameObject*> rootObjects;
                
                for (int i = 0; i < mainScene.getGameObjects()->size(); i++)
                {
                    if (i == 0)
                        ImGui::SetNextItemOpen(true, ImGuiCond_Once);

                    if(mainScene.getGameObjects()->at(i)->parent == nullptr){
                        // if (ImGui::TreeNode(mainScene.getGameObjects()->at(i)->name.c_str()))
                        // {
                            // ImGui::Text("Enabled:");
                            // ImGui::SameLine();
                            // ImGui::Checkbox("Enabled", &(mainScene.getGameObjects()->at(i)->enabled));
                            recursiveTreeFill(mainScene.getGameObjects()->at(i));
                            // ImGui::TreePop();
                        // }
                    }

                }

                // for (int i = 0; i < mainScene.getGameObjects()->size(); i++)
                // {
                //     if (i == 0)
                //         ImGui::SetNextItemOpen(true, ImGuiCond_Once);

                //     if (ImGui::TreeNode(mainScene.getGameObjects()->at(i)->name.c_str()))
                //     {
                //         ImGui::Text("Enabled:");
                //         ImGui::SameLine();
                //         ImGui::Checkbox("Another Window", &(mainScene.getGameObjects()->at(i)->enabled));
                //         ImGui::TreePop();
                //     }
                // }
                ImGui::TreePop();
            }

            // ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
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

        
        // Rendering Imgui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();

        Time::getInstance().UpdateDeltaTime();


    } while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0 );

    delete camera;

    glfwTerminate();
    
}

