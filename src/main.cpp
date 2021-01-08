#include <SDL2/SDL.h>
#include <string>
#include <sstream>
#include <iostream>
#include <time.h>
#include <ctime>
#include <vector>
#include <cctype>
#include <fstream>
#include <iomanip>
#include "Window.h"
// #include "XEvent.h"
#include "EpochFunctions.h"
#include "GraphDrawing.h"

int FPS = 20;

std::vector<std::string> lines;

void pollEvents(Window &window){
    SDL_Event event;

    if (SDL_PollEvent(&event)){
        window.pollEvents(event);
    }
}

void collect_data_into_xevents(struct XEvent * events){

    int index = 0;
    for (auto s: lines){

        // 0                 1    2   3
        // 08/05/2020 11:05, 10.2,---,l
        std::vector<std::string> info = split_string(s, ",");

        auto *xev     =  &events[index];
        xev->epoch    =  epoch_from_string(info[0]);
        xev->fullstr  =  s;
        xev->comment  =  strip_string(info[2]);
        xev->tod      =  strip_string(info[3]);

        if (xev->tod != "c"){
            std::string sfloat = strip_string(info[1]);
            xev->glucose = std::stof(sfloat);
        }

        index++;
    }
}

int main(int argc, char* args[])
{

    load_csv_file(lines);
    int num_lines = lines.size();
    XEvent events[num_lines];
    collect_data_into_xevents(events);

    int start = 0;

    // std::cout << events[6].glucose << std::endl;

    Window window("Sugars", 1800, 550);
    GraphDrawing graph("test");

    // for (auto ev: events){
    //     std::cout << ev.epoch << std::endl;
    // }

    while (!window.isClosed()){

        pollEvents(window);
        graph.draw(events, num_lines);

        SDL_Delay(FPS);
        window.clear();
        start++;
        if (start > 4000) start = 0;

    }

    return 0;

}