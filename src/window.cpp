//window.cpp
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>
#include "Window.h"

using namespace std;

TTF_Font *Window::font = nullptr;
SDL_Renderer *Window::renderer = nullptr;


Window::Window(const string &title, int width, int height)
:_title(title), _width(width), _height(height)
{
    _closed = !init();
    load_font();
}

Window::~Window(){
    SDL_DestroyRenderer(renderer);
    close_font();
    SDL_DestroyWindow(_window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Window::load_font(){ font = TTF_OpenFont("res/consola.ttf", 11); };
void Window::close_font(){ TTF_CloseFont(font); };

bool Window::init(){

    if (SDL_Init(SDL_INIT_VIDEO) != 0){ cerr << "Failed to init SDL.\n"; return false; }
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG){ cerr << "Failed to init SDL img\n"; return false; }
    if (TTF_Init() == -1){ cerr << "Failed to init TTF img\n"; return false; }

    _window = SDL_CreateWindow(
        _title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        _width, _height,
        0  // SDL_WINDOW_RESIZABLE
    );

    if (_window == nullptr) { cerr << "Failed to create window! :/ \n"; return false; }

    renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    // SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

    if (renderer == nullptr) { cerr << "Failed to create renderer!\n"; return false; }

    return true;
}

void Window::pollEvents(SDL_Event &event){

    int shift = SDL_GetModState() & KMOD_LSHIFT || SDL_GetModState() & KMOD_RSHIFT;
    int ctrl = SDL_GetModState() & KMOD_LCTRL || SDL_GetModState() & KMOD_RCTRL;

    switch (event.type){

        case SDL_QUIT:
            _closed = true; break;

        case SDL_KEYDOWN:

            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    _closed = true;
                    break;
                case SDLK_UP:
                    if (shift)
                        std::cout << "UP plus" << std::endl;  
                    else if (ctrl)
                        std::cout << "UP negative" << std::endl; 
                    else
                        std::cout << "UP empty" << std::endl; 

                    break;
                default:
                    break;
            }
            break;

        default:
            break;
    }
}

void Window::clear() const {

    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);
}

