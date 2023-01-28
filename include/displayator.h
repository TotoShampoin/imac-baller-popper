#ifndef __DISPLAYATOR_H__
#define __DISPLAYATOR_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "SDL2_gfxPrimitives.h"
#include "vector.h"
#include "string_manip.h"

#define DEFAULT_FONT_SIZE 32

/**
 * Une structure comportant des informations sur la position et le clic de la souris.
 */
struct MouseData {
    Vec2 position;
    bool click = false;
    bool is_down = false;
};

/**
 * Une petite structure permettant d'utiliser des images avec des dimensions virtuelles, indépendante de la vraie taille de l'image.
 * Plus d'informations sur pourquoi utiliser des dimensions virtuelles dans la classe Displayator.
 */
struct Image {
    SDL_Surface* image;
    int width, height;
    int scale;
};

/**
 * Une classe qui englobe toute la logique de SDL pour l'affichage (et la gestion événementielle).
 * Elle fournie principalement des fonctions pour dessiner à l'écran.
 * 
 * Le Displayator connait notamment ses dimensions, ainsi qu'un facteur d'échelle.
 * Ainsi, je peux définir une dimension fixe d'écran (en l'occurrence 480x360) tout en ayant une fenêtre de la taille que je souhaite.
 * 
 * C'est aussi le Displayator qui connait la police de caractère à utiliser pour l'interface (il n'y en aura qu'une).
 */
struct Displayator {
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    int width, height;
    float scale; // Le facteur d'échelle

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
    void image(Image* img, int x, int y);

    void getMouse(MouseData*);
    void event(bool*, MouseData*);

    /**
     * Supposons que l'on charge logo.png et que le facteur d'échelle est de 2:
     * Alors cette fonction cherche l'existence d'un logo@2x.png au préallable, afin d'utiliser une image de meilleure qualité.
     */
    Image* loadImage(const char* path);
};

#endif
