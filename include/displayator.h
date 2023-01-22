#ifndef __DISPLAYATOR_H__
#define __DISPLAYATOR_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "SDL2_gfxPrimitives.h"
#include "vector.h"

#define DEFAULT_FONT_SIZE 32

struct MouseData {
    Vec2 position;
    bool click = false;
    bool is_down = false;
};

struct Displayator {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* screen;
    TTF_Font* font;
    int width, height;
    float scale;

    Displayator(int width, int height, float scale = 1);
    ~Displayator();

    void changeScale(float scale);

    void clear();
    void refresh();

    void circle(int x, int y, int r, Uint32 color, bool filled = true);
    void line(int x0, int y0, int x1, int y1, Uint32 color);
    void rect(int x, int y, int w, int h, Uint32 color, bool filled = true);
    void text(const char* text, int x, int y, Uint32 color = 0xFFFFFFFF, int size = DEFAULT_FONT_SIZE);

    void image(SDL_Surface* img, int x, int y);

    void getMouse(MouseData*);
    void event(bool*, MouseData*);
};

#endif
