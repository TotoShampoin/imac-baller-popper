#ifndef __DISPLAYATOR_H__
#define __DISPLAYATOR_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_gfxPrimitives.h>

struct Displayator {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* screen;
    Displayator(int width, int height);
    ~Displayator();

    void clear();
    void refresh();

    void circle(int x, int y, int r, Uint32 color, bool fill = false);
};

#endif
