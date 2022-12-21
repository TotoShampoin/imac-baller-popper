#ifndef __BALL_H__
#define __BALL_H__

#include "vector.h"
// #include "LinkedListBall.h"

#define MIN_RADIUS 32
#define MAX_RADIUS 48

#define MAX_SPEED 4

struct Ball {
    Vec2 position, speed;
    int radius;
    unsigned int color = 0xFFFFFFFF;

    Ball(int screen_width, int screen_height, int color = 0xFFFFFF);

    void update();
    void applyCollisionsAndBounce(int bound_width, int bound_height);
};

#endif
