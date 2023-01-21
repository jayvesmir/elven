#pragma once
#include <chrono>
using namespace std::chrono;

class Timer {
public:
    std::chrono::time_point<system_clock> start, end;
    std::chrono::duration<float> duration;
    const char* title;

    Timer(const char* title) : title(title){
        start = std::chrono::high_resolution_clock::now();
    }

    ~Timer() {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;

        printf("[%s] Finished in %fs\n", title, duration.count());
    }
    
};