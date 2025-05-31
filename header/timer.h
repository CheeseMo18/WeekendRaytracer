#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <ctime>

using namespace std::chrono;

class timer{
    public:
        void start(){
            startTime = steady_clock::now();
        }

        void end(){
            endTime = steady_clock::now();
        }

        double elapsedMilliSeconds(){
            return duration_cast<milliseconds>(endTime - startTime).count();
        }
    
    
    private:
        time_point<steady_clock> startTime;
        time_point<steady_clock> endTime;
};

#endif
