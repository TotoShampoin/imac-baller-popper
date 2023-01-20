#include "displayator.h"
#include <SDL2/SDL_assert.h>

Displayator::Displayator(int w, int h, float s) {
    this->scale = s;
    SDL_assert(SDL_Init(SDL_INIT_EVERYTHING) == 0);
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
    this->font = TTF_OpenFont("assets/font.ttf", 32 * s);
    SDL_assert(this->font);
}

Displayator::~Displayator() {
    TTF_CloseFont(this->font);
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
}

void Displayator::clear() {
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);
}

void Displayator::refresh() {
    SDL_RenderPresent(this->renderer);
}

void Displayator::circle(int x, int y, int r, Uint32 color) {
    int X = x * this->scale,
        Y = y * this->scale,
        R = r * this->scale;
    filledCircleColor(this->renderer, X, Y, R, 0xAA000000 + color);
    circleColor(this->renderer, X, Y, R - 1, 0x55FFFFFF);
}
void Displayator::line(int x0, int y0, int x1, int y1, Uint32 color) {
    int X0 = x0 * this->scale,
        Y0 = y0 * this->scale,
        X1 = x1 * this->scale,
        Y1 = y1 * this->scale;
    lineColor(this->renderer, X0, Y0, X1, Y1, 0xFF000000 + color);
}

void Displayator::text(int x, int y, const char* text, Uint32 color) {
    SDL_Color clr = {
        .r = (Uint32)(color >>  0),
        .g = (Uint32)(color >>  8),
        .b = (Uint32)(color >> 16),
        .a = 0xFF,
    };
    SDL_Surface* text_surface = TTF_RenderText_Blended(this->font, text, clr);
    SDL_Texture* render = SDL_CreateTextureFromSurface(this->renderer, text_surface);
    SDL_Rect position = {
        .x = x * this->scale, .y = y * this->scale,
        .w = text_surface->w,
        .h = text_surface->h
    };
    SDL_RenderCopy(this->renderer, render, NULL, &position);
    SDL_DestroyTexture(render);
    SDL_FreeSurface(text_surface);
}

void Displayator::getMouse(MouseData* mouse) {
    int mx, my, mc;
    bool was_down = mouse->is_down;
    mc = SDL_GetMouseState(&mx, &my);
    mouse->is_down = SDL_BUTTON(mc) == SDL_BUTTON_LEFT;
    if(mouse->is_down) {
        mouse->click = !was_down;
    } else {
        mouse->click = false;
    }
    mouse->position.x = mx / this->scale;
    mouse->position.y = my / this->scale;
}
