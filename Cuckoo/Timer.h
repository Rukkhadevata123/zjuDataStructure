#include <chrono>
#include <iostream>

class Timer
{
public:
    Timer() : start_time_point(std::chrono::high_resolution_clock::now()) {}

    ~Timer()
    {
        stop();
    }

    void stop()
    {
        auto end_time_point = std::chrono::high_resolution_clock::now();
        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(start_time_point).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_time_point).time_since_epoch().count();

        auto duration = end - start;
        double seconds = duration * 0.000001;

        std::cout << std::fixed << std::setprecision(4) << "Duration: " << seconds << " seconds" << std::endl;
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time_point;
};