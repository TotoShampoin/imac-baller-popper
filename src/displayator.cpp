#include "displayator.h"
#include <SDL2/SDL_assert.h>

Displayator::Displayator(int w, int h) {
    this->window = SDL_CreateWindow("awesome window", 
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        w, h,
        SDL_WINDOW_SHOWN
    );
    SDL_assert(this->window);
    this->renderer = SDL_CreateRenderer(this->window, -1, 
        SDL_RENDERER_PRESENTVSYNC |
        SDL_RENDERER_ACCELERATED
    );
    SDL_assert(this->renderer);
    SDL_assert(TTF_Init() == 0);
    this->font = TTF_OpenFont("assets/font.ttf", 32);
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
    filledCircleColor(this->renderer, x, y, r, 0xFE000000 + color);
    circleColor(this->renderer, x, y, r - 1, 0x55FFFFFF);
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
        .x = x, .y = y,
        .w = text_surface->w,
        .h = text_surface->h
    };
    SDL_RenderCopy(this->renderer, render, NULL, &position);
    SDL_DestroyTexture(render);
    SDL_FreeSurface(text_surface);
}
