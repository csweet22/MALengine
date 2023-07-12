#ifndef TIME_HPP
#define TIME_HPP

class Time
{
    public:
        static Time& getInstance()
        {
            static Time instance; 
            return instance;
        }
        double GetDeltaTime(){            
            return deltaTime;
        }
        double GetTime(){            
            return glfwGetTime();
        }
        void UpdateDeltaTime(){
            double currentTime = glfwGetTime();
            static double lastTime = glfwGetTime();
            deltaTime = (currentTime - lastTime);
            lastTime = currentTime;
        }
    private:
        double deltaTime = 0;
        Time() {} 
        Time(Time const&); 
};

#endif