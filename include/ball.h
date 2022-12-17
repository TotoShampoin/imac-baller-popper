#ifndef __BALL_H__
#define __BALL_H__

#include "vector.h"
#include "linkedlist.h"

#define MIN_RADIUS 32
#define MAX_RADIUS 48

struct Ball {
    Vec2 position, speed;
    int radius;
    unsigned int color = 0xFFFFFFFF;

    Ball(float max_speed = 4);

    void update();
    void applyCollisionsAndBounce(int bound_width, int bound_height);
};

typedef LinkedList<Ball*> BallCollection;

#endif