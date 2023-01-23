#include "displayator.h"
#include "string_manip.h"
#include <SDL2/SDL_assert.h>

#include <filesystem>
#include <iostream>
using namespace std;

Displayator::Displayator(int w, int h, float s) {
    SDL_assert(SDL_Init(SDL_INIT_EVERYTHING) == 0);
    this->width = w;
    this->height = h;
    this->scale = s;
    this->window = SDL_CreateWindow("Ballers", 
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        w * s, h * s,
        SDL_WINDOW_SHOWN
    );
    SDL_assert(this->window);
    this->renderer = SDL_CreateRenderer(this->window, -1, 
        SDL_RENDERER_PRESENTVSYNC |
        SDL_RENDERER_ACCELERATED
    );
    SDL_assert(this->renderer);
    SDL_assert(TTF_Init() == 0);
    this->font = TTF_OpenFont("assets/font.ttf", DEFAULT_FONT_SIZE * s);
    SDL_assert(this->font);
}

Displayator::~Displayator() {
    TTF_CloseFont(this->font);
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
}

void Displayator::changeScale(float s) {
    this->scale = s;
    if(!this->window) return;
    SDL_SetWindowSize(this->window, this->width * s, this->height * s);
}

void Displayator::clear() {
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);
}

void Displayator::refresh() {
    SDL_RenderPresent(this->renderer);
}

void Displayator::circle(int x, int y, int r, Uint32 color, bool filled) {
    int X = x * this->scale,
        Y = y * this->scale,
        R = r * this->scale;
    if(filled)
        filledCircleColor(this->renderer, X, Y, R, color);
    else
        circleColor(this->renderer, X, Y, R, color);
}

void Displayator::line(int x0, int y0, int x1, int y1, Uint32 color) {
    int X0 = x0 * this->scale,
        Y0 = y0 * this->scale,
        X1 = x1 * this->scale,
        Y1 = y1 * this->scale;
    lineColor(this->renderer, X0, Y0, X1, Y1, color);
}

void Displayator::rect(int x, int y, int w, int h, Uint32 color, bool filled) {
    int X = x * this->scale,
        Y = y * this->scale,
        W = w * this->scale,
        H = h * this->scale;
    if(filled) {
        SDL_Color clr = {
            .r = (Uint32)(color >>  0),
            .g = (Uint32)(color >>  8),
            .b = (Uint32)(color >> 16),
            .a = (Uint32)(color >> 24),
        };
        SDL_SetRenderDrawColor(this->renderer, clr.r, clr.g, clr.b, clr.a);
        SDL_Rect rect { X, Y, W, H };
        SDL_RenderFillRect(this->renderer, &rect);
    } else {
        rectangleColor(this->renderer, X, Y, W, H, color);
    }
}

void Displayator::text(const char* text, int x, int y, Uint32 color, int size) {
    TTF_SetFontSize(this->font, size * this->scale);
    SDL_Color clr = {
        .r = (Uint32)(color >>  0),
        .g = (Uint32)(color >>  8),
        .b = (Uint32)(color >> 16),
        .a = (Uint32)(color >> 24),
    };
    SDL_Surface* text_surface = TTF_RenderText_Blended(this->font, text, clr);
    this->image(text_surface, x, y);
    SDL_FreeSurface(text_surface);
}

void Displayator::image(SDL_Surface* img, int x, int y) {
    SDL_Texture* render = SDL_CreateTextureFromSurface(this->renderer, img);
    SDL_Rect position = {
        .x = x * this->scale, .y = y * this->scale,
        .w = img->w, .h = img->h
    };
    SDL_RenderCopy(this->renderer, render, NULL, &position);
    SDL_DestroyTexture(render);
}
void Displayator::image(Image* img, int x, int y) {
    SDL_Texture* render = SDL_CreateTextureFromSurface(this->renderer, img->image);
    SDL_Rect position = {
        .x = x * this->scale, .y = y * this->scale,
        .w = img->width * this->scale, .h = img->height * this->scale
    };
    SDL_RenderCopy(this->renderer, render, NULL, &position);
    SDL_DestroyTexture(render);
}

void Displayator::getMouse(MouseData* mouse) {
    int mx, my, mc;
    bool was_down = mouse->is_down;
    mc = SDL_GetMouseState(&mx, &my);
    mouse->is_down = (SDL_BUTTON(mc) == SDL_BUTTON_LEFT);
    if(mouse->is_down) {
        mouse->click = !was_down;
    } else {
        mouse->click = false;
    }
    mouse->position.x = mx / this->scale;
    mouse->position.y = my / this->scale;
}

void Displayator::event(bool* cont, MouseData* mouse) {
    SDL_Event event_handler;
    while(SDL_PollEvent(&event_handler)) {
        switch (event_handler.type){
        case SDL_QUIT:
            *cont = false;
            break;
        }
    }
    this->getMouse(mouse);
}

Image* Displayator::loadImage(const char* path) {
    char *name, *ext;
    splitExtention(path, &name, &ext);
    std::string x3_str = std::string(name) + "@3x." + ext;
    std::string x2_str = std::string(name) + "@2x." + ext;
    const char* x3 = x3_str.c_str();
    const char* x2 = x2_str.c_str();
    if(this->scale > 2 && std::filesystem::exists(x3)) {
        SDL_Surface* img = IMG_Load(x3);
        return new Image {
            img, img->w / 3, img->h / 3, 3
        };
    }
    if(this->scale > 1 && std::filesystem::exists(x2)) {
        SDL_Surface* img = IMG_Load(x2);
        return new Image {
            img, img->w / 2, img->h / 2, 2
        };
    }
    SDL_Surface* img = IMG_Load(path);
    return new Image {
        img, img->w, img->h, 1
    };
}
