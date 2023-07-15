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
            return time;
        }
        void UpdateDeltaTime(){
            double currentTime = glfwGetTime();
            static double lastTime = glfwGetTime();
            deltaTime = (currentTime - lastTime);
            lastTime = currentTime;
        }
        void UpdateTime(){
            time = time + 0.1;
        }
    private:
        double time = 0.0;
        double deltaTime = 0;
        Time() {} 
        Time(Time const&); 
};

#endif