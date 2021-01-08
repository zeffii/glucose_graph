#pragma once
#include <vector>
#include <string>

struct XEvent{
    int epoch = 0;
    std::string fullstr = "unfilled";
    std::string comment = "N/A";
    std::string tod = "N/A";
    int day = 0;
    int month = 0;
    int year = 1972;
    float glucose = 0.0;
};