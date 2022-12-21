#include "ball.h"

#include "mymath.h"
#include <cmath>

Ball::Ball(int screen_width, int screen_height, int color) {
    float angle = ((float)rand()/0x7FFFFFFF) * M_PI * 2;
    float speed = ((float)rand()/0x7FFFFFFF) * MAX_SPEED;
    this->radius = randint(MIN_RADIUS, MAX_RADIUS);
    this->position.x = randint(this->radius, screen_width - this->radius);
    this->position.y = randint(this->radius, screen_height - this->radius);
    this->speed.x = cos(angle) * speed;
    this->speed.y = sin(angle) * speed;
    this->color = color;
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
