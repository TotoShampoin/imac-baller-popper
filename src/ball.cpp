#include "ball.h"

#include "mymath.h"
#include <cmath>

Ball::Ball(float max_speed) {
    float angle = ((float)rand()/0x7FFFFFFF) * M_PI * 2;
    float speed = ((float)rand()/0x7FFFFFFF) * max_speed;
    this->position.x = 0;
    this->position.y = 0;
    this->speed.x = cos(angle) * speed;
    this->speed.y = sin(angle) * speed;
    this->radius = randint(MIN_RADIUS, MAX_RADIUS);
}

void Ball::update() {
    this->position += this->speed;
}

void Ball::applyCollisionsAndBounce(int bound_width, int bound_height) {
    if(
        this->position.x - this->radius <= 0 || 
        this->position.x + this->radius > bound_width
    ) {
        this->speed.x *= -1;
    }
    if(
        this->position.y - this->radius <= 0 || 
        this->position.y + this->radius > bound_height
    ) {
        this->speed.y *= -1;
    }
}
