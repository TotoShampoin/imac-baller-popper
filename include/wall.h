#ifndef __WALL_H__
#define __WALL_H__

#include "vector.h"
#include "ball.h"

struct Wall {
    Vec2 pA, pB;

    Vec2 getDirection();

    bool detectCollision(Ball*);
    void redirect(Ball*);

    void bounceMechanics(Ball*);
};

struct WallCollection {
    Wall* walls;
    int length;
    WallCollection(int);
    ~WallCollection();

    Wall& operator[](int);

    void forEach(void(Wall*, void*), void* = nullptr);
    void bounceMechanics(Ball*);
};

#endif