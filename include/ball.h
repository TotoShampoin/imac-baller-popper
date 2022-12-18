#ifndef __BALL_H__
#define __BALL_H__

#include "vector.h"
// #include "LinkedListBall.h"

#define MIN_RADIUS 32
#define MAX_RADIUS 48

struct Ball {
    Vec2 position, speed;
    int radius;
    unsigned int color = 0xFFFFFFFF;
    bool marked = false;

    Ball(float max_speed = 4);

    void update();
    void applyCollisionsAndBounce(int bound_width, int bound_height);
};

#endif
