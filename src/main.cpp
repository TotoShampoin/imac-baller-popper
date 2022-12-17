#include "displayator.h"
#include "ball.h"

#include "mymath.h"
#include <ctime>

#define WIDTH 720
#define HEIGHT 540

void event(bool* cont) {
    SDL_Event e;
    SDL_PollEvent(&e);
    switch (e.type){
    case SDL_QUIT:
        *cont = false;
    default:
        break;
    }
}

int main(int argc, const char* argv[]) {
    // Variables
    Displayator* disp;
    bool cont;
    Ball* ball;

    // Initialisation
    srand(time(NULL));
    disp = new Displayator { WIDTH , HEIGHT };
    cont = true;
    ball = new Ball;
    ball->position.x = randint(ball->radius, WIDTH - ball->radius);
    ball->position.y = randint(ball->radius, HEIGHT - ball->radius);
    ball->color = 0xFF000000 + randint(0x000000, 0xFFFFFF);

    while(cont) {
        // Input
        event(&cont);

        // Physics
        ball->update();
        ball->applyCollisionsAndBounce(WIDTH, HEIGHT);

        // Graphics
        disp->clear();
        disp->circle(
            ball->position.x,
            ball->position.y,
            ball->radius,
            ball->color
        );
        disp->refresh();
    }
    delete disp;
    return 0;
}
