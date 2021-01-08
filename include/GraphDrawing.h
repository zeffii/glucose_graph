#pragma once
#include "Window.h"
// #include "EpochFunctions.h"

class GraphDrawing
{
    public:
        GraphDrawing(std::string test);
        void SDLX_draw_dotted_line(SDL_Renderer *renderer, SDL_Color color, int x, int y, int h);
        void draw(struct XEvent * events, int length);
        void filter_epoch_data(std::string fullstr, std::string token, int epoch, std::vector<int> &tokens);

    private:
        std::string ntitle;
        int counter_once = 0;
        int distance = 0;
        int whole_days = 0;
        int epoch_start = 0;
};