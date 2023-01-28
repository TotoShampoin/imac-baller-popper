#ifndef __BALL_H__
#define __BALL_H__

#include "vector.h"
#include "mymath.h"
// #include "LinkedListBall.h"

#define MIN_RADIUS 16
#define MAX_RADIUS 24

#define MAX_SPEED 2

/**
 * Une classe représentant une balle, en jeu.
 * Une balle connait sa position, sa vitesse, son rayon et sa couleur.
 */
struct Ball {
    Vec2 position;
    Vec2 speed;
    int radius;
    unsigned int color = 0xFFFFFFFF;

    Ball(int screen_width, int screen_height, int color = 0xFFFFFF);
    Ball(Vec2 position, Vec2 speed, int r, int c);

    // Applique la vitesse de la balle pour mettre à jour sa position.
    void update();
    // Fait rebondir la balle sur le bord de l'écran
    void applyCollisionsAndBounce(int bound_width, int bound_height);
};

#endif
