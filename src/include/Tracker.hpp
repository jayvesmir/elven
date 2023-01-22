#pragma once
#include "Ayanami.hpp"

class ProgressTracker {
public:
    ProgressTracker(const char* title, int64_t total) : title(title), total(total) {}
    void update(int increment = 1) { done += increment; done = fmin(done, total); }
    void change_title(const char* new_title) { title = new_title; }
    void write() {
        fprintf(stderr, "\r[%s] %d%% done (%ld items remaining)     ", title, (int)(double(done)/total*100), total-done);
        fflush(stderr);
    }
private:
    const char* title;
    int64_t total;
    int64_t done = 0;
};