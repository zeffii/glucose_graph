#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>
#include "XEvent.h"

using namespace std;

class Window {
    public:

        Window(const string &title, int width, int height);
        ~Window();

        void load_font();
        void close_font();
        void pollEvents(SDL_Event &event);

        void clear() const;
        inline bool isClosed() const { return _closed; }

    private:
        bool init();
        string _title;
        int _width = 800;
        int _height = 600;
        bool _closed = false;

        SDL_Window *_window = nullptr;
    public:
        static SDL_Renderer *renderer;
        static TTF_Font *font;
        const Uint8 *keyState = SDL_GetKeyboardState(NULL);

};