#pragma once
#include <chrono>
using namespace std::chrono;

class Timer {
public:
#ifdef _WIN32
    std::chrono::steady_clock::time_point start, end;
#else
    std::chrono::time_point<system_clock> start, end;
#endif
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