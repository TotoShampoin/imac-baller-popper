#include "wall.h"
#include <cmath>

Vec2 Wall::getDirection() {
    return pB - pA;
}

bool Wall::detectCollision(Ball* B) {
    Vec2& pO = B->position;
    float distance = abs((pB.x - pA.x)*(pA.y - pO.y) - (pA.x - pO.x)*(pB.y - pA.y)) / sqrtf((pB - pA).magnitude());
    B->marked = (distance < B->radius);
    return distance < B->radius;
}

void Wall::redirect(Ball* B) {
    Vec2 dir = this->getDirection();
    float angle_target = dir.angle() - B->speed.angle();
    Vec2 new_dir = Vec2::fromAngle(angle_target) * B->speed.magnitude();
    B->speed = dir.norm().cmpMul(new_dir);
}

void Wall::bounceMechanics(Ball* B) {
    if(!this->detectCollision(B)) return;
    this->redirect(B);
}


WallCollection::WallCollection(int length) {
    this->length = length;
    this->walls = new Wall[length];
}
WallCollection::~WallCollection() {
    delete[] this->walls;
}

Wall& WallCollection::operator[](int i) {
    return this->walls[i];
}

void WallCollection::forEach(void callback(Wall*, void*), void* ptr) {
    for(int i = 0; i < length; i++) {
        callback(&this->walls[i], ptr);
    }
}

void WallCollection::bounceMechanics(Ball* B) {
    for(int i = 0; i < length; i++) {
        this->walls[i].bounceMechanics(B);
    }
}
