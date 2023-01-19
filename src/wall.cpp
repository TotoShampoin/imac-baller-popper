#include "wall.h"
#include <cmath>

Vec2 Wall::getDirection() {
    return pB - pA;
}

// bool Wall::detectCollision(Ball* B) {
//     Vec2& pO = B->position;
//     float distance = abs((pB.x - pA.x)*(pA.y - pO.y) - (pA.x - pO.x)*(pB.y - pA.y)) / sqrtf((pB - pA).magnitude());
//     B->marked = (distance < B->radius);
//     return distance < B->radius;
// }

bool Wall::detectLineCollision(Ball* B) {
    Vec2 u = this->getDirection();
    Vec2 AC = B->position - pA;
    float num = u.x * AC.y - u.y * AC.x;
    if(num < 0) num = -num;
    float denom = u.magnitude();
    float CI = num / denom;
    return (CI < B->radius);
}

bool Wall::detectCollision(Ball* B) {
    if(!detectLineCollision(B)) return false;
    Vec2 AB = this->getDirection(),
         AC = B->position - pA,
         BC = B->position - pB;
    float pscal1 = AB.dotProd(AC);
    float pscal2 = (-AB).dotProd(BC);
    return (pscal1 >= 0 && pscal2 >= 0) || (AC.magnitude() < B->radius) || (BC.magnitude() < B->radius);
}

Vec2 Wall::impact(Vec2& pC) {
    Vec2 u = this->getDirection(), 
         AC = pC - pA;
    float ti = u.dotProd(AC) / u.magnitude2();
    Vec2 u_ti = u * ti;
    return this->pA + u_ti;
}
Vec2 Wall::normal(Vec2& pC) {
    Vec2 u = this->getDirection(),
         AC = pC - pA;
    float parenthesis = u.x * AC.y - u.y * AC.x;
    Vec2 N {
        -u.y * parenthesis,
        u.x * parenthesis
    };
    float norme = N.magnitude();
    return N / norme;
}

// void Wall::bounce(Ball* B) {
//     Vec2 dir = this->getDirection();
//     float angle_target = dir.angle() - B->speed.angle();
//     Vec2 new_dir = Vec2::fromAngle(angle_target) * B->speed.magnitude();
//     B->speed = dir.norm().cmpProd(new_dir);
// }

void Wall::bounce(Ball* B) {
    Vec2 N = this->normal(B->position);
    float pscal = B->speed.dotProd(N);
    Vec2 N_prod = N * (-2) * pscal;
    B->speed = B->speed + N_prod;
}

void Wall::bounceMechanics(Ball* B) {
    if(!this->detectCollision(B)) return;
    this->bounce(B);
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
