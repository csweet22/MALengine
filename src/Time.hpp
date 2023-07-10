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
            double currentTime = glfwGetTime();
            static double lastTime = glfwGetTime();
            double deltaTime = (currentTime - lastTime);
            lastTime = currentTime;
            return deltaTime;
        }
    private:
        Time() {} 
        Time(Time const&); 
};

#endif