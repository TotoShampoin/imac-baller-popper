#ifndef __BALL_H__
#define __BALL_H__

#include "vector.h"
// #include "LinkedListBall.h"

#define MIN_RADIUS 16
#define MAX_RADIUS 24

#define MAX_SPEED 2

struct Ball {
    Vec2 position, speed;
    int radius;
    unsigned int color = 0xFFFFFFFF;
    bool marked = false;
    bool is_dead = false;
    int death_animation = 0;

    Ball(int screen_width, int screen_height, int color = 0xFFFFFF);
    Ball(Vec2 position, Vec2 speed, int r, int c);

    void update();
    void applyCollisionsAndBounce(int bound_width, int bound_height);
};

#endif
