// graphdrawing.cpp
#include "Window.h"
#include "GraphDrawing.h"
// #include "XEvent.h"
// #include <iterator>

void set_color(SDL_Renderer *renderer, SDL_Color col){
    SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
}

void GraphDrawing::filter_epoch_data(std::string fullstr, std::string token, int epoch, std::vector<int> &tokens){
    if (fullstr.substr(0, 2) == token){

        int pxval = ((epoch - epoch_start) / 86400) * 7;
        if (tokens.empty()){
            tokens.push_back(pxval);
            return;
        }
        
        for (auto fd: tokens){
            if (pxval == fd)
                return;
        }
        tokens.push_back(pxval);
    }    
}


GraphDrawing::GraphDrawing(std::string test){
    ntitle = test;

};

void GraphDrawing::SDLX_draw_dotted_line(SDL_Renderer *renderer, SDL_Color color, int x, int y, int h){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    int numpoints = h / 4;
    SDL_Point pointset[numpoints];

    int j = 0;
    for (int i = y; i < y + h; i += 4){
        pointset[j] = {x, i};
        j +=1;
    }
    SDL_RenderDrawPoints(renderer, pointset, numpoints);
};

void GraphDrawing::draw(struct XEvent * events, int length){

    epoch_start = events[0].whole_day;
    int bottom_y = 450;

    if (counter_once == 0){
        // do this only once
        distance = events[length-1].epoch - events[0].epoch;
        whole_days = distance / 86400;
        std::cout << whole_days << std::endl;
        counter_once++;
    }

    std::vector<int> first_days;
    std::vector<int> minor_ticks;
    // {"06", "11", "16", "21", "26"};

    SDL_Point parray[length * 4];
    int x_offset = 20;

    int cx = 0;
    for (int i = 0; i < length; i++) {

        auto ev = events[i];
        int px = ((ev.epoch - epoch_start) / 86400) * 7;

        int pxx = x_offset + px;
        int pxy = bottom_y - (ev.glucose * 10);

        if (ev.glucose == 0.0)
            pxy = -5;

        parray[cx].x = pxx;       // [x][ ]
        parray[cx].y = pxy;       // [ ][ ]
        
        parray[cx+1].x = pxx + 1; // [ ][x]
        parray[cx+1].y = pxy;     // [ ][ ]
        
        parray[cx+2].x = pxx + 1; // [ ][ ]
        parray[cx+2].y = pxy + 1; // [ ][x]
        
        parray[cx+3].x = pxx;     // [ ][ ]
        parray[cx+3].y = pxy + 1; // [x][ ]

        filter_epoch_data(ev.fullstr, "01", ev.epoch, first_days);
        filter_epoch_data(ev.fullstr, "06", ev.epoch, minor_ticks);
        filter_epoch_data(ev.fullstr, "11", ev.epoch, minor_ticks);
        filter_epoch_data(ev.fullstr, "16", ev.epoch, minor_ticks);
        filter_epoch_data(ev.fullstr, "21", ev.epoch, minor_ticks);
        filter_epoch_data(ev.fullstr, "26", ev.epoch, minor_ticks);

        cx += 4;

    }

    SDL_Color color = {242, 122, 122, 255};
    SDL_SetRenderDrawColor(Window::renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoints(Window::renderer, parray, length*4);

    SDL_Color cx_axis = {74, 72, 73, 255};
    SDL_SetRenderDrawColor(Window::renderer, cx_axis.r, cx_axis.g, cx_axis.b, cx_axis.a);
    SDL_RenderDrawLine(Window::renderer, x_offset, bottom_y, (x_offset + whole_days * 7), bottom_y);

    SDL_Color col_ident = {74, 72, 73, 255};
    for (auto fd: first_days){
        int first_day_marker_x = x_offset + fd;
        SDLX_draw_dotted_line(Window::renderer, col_ident, first_day_marker_x, 50, 400);
    }

    SDL_Color col_ident2 = {54, 52, 53, 255};
    float guides[6] = {4.7, 7.3, 10.0, 15.0, 20.0, 25.0};
    for (auto nf: guides){
        set_color(Window::renderer, col_ident2);
        int ypos = bottom_y - (nf * 10);
        SDL_RenderDrawLine(Window::renderer, x_offset, ypos, (x_offset + whole_days * 7), ypos);        
    }

    // std::cout << minor_ticks[0] << std::endl;
    // SDL_Color col_ident3 = {74, 72, 73, 255};
    // set_color(Window::renderer, col_ident3);
    for (auto tick: minor_ticks){
        int xpos = x_offset + tick;
        SDL_RenderDrawLine(Window::renderer, xpos, bottom_y, xpos, bottom_y + 10);
    }

}
