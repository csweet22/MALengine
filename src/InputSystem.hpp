#ifndef INPUTSYSTEM_HPP
#define INPUTSYSTEM_HPP

class InputSystem
{
    public:
        GLFWwindow* window;
        static InputSystem& getInstance()
        {
            static InputSystem instance; 
            return instance;
        }
        void setWindow(GLFWwindow* _window){
            window = _window;
        }
        bool getKeyPress(int KEY, int EVENT){
            return (glfwGetKey(window, KEY ) == EVENT);
        }
    private:
        InputSystem() {} 
        InputSystem(InputSystem const&); 
        // void operator=(InputSystem const&); 
    // public:
        // InputSystem(InputSystem const&) {}
        // void operator=(InputSystem const&) {}
};

#endif