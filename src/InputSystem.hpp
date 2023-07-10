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
        bool getKeyPress(int KEY, int EVENT){
            return (glfwGetKey(window, KEY ) == EVENT);
        }
        bool getMousePress(int KEY, int EVENT){
            return (glfwGetMouseButton(window, KEY ) == EVENT);
        }
        void Init(GLFWwindow* _window){
            window = _window;
            glfwSetCursorPosCallback(window, cursor_position_callback);
        }
        static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
        }
        double GetMousePosX(){
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            return xpos;
        }
        double GetMousePosY(){
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            return ypos;
        }
    private:
        InputSystem() {} 
        InputSystem(InputSystem const&); 
};

#endif