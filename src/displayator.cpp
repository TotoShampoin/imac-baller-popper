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
}

Displayator::~Displayator() {
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
    for(int i = 0; i < 3; i++) {
        circleColor(this->renderer, x, y, r + i, color);
    }
}
