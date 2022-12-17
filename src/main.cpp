#include "displayator.h"
#include "ball.h"
#include "linkedlistball.h"

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

void ballPhysics(Ball* ball, void* = nullptr) {
    ball->update();
    ball->applyCollisionsAndBounce(WIDTH, HEIGHT);
}
void ballGraphics(Ball* ball, void* _disp) {
    Displayator* disp = (Displayator*)_disp;
    disp->circle(
        ball->position.x,
        ball->position.y,
        ball->radius,
        ball->color
    );
}

int main(int argc, const char* argv[]) {
    // Variables
    Displayator* disp;
    bool cont;
    BallCollection* balls;

    // Initialisation
    srand(time(NULL));
    disp = new Displayator { WIDTH , HEIGHT };
    cont = true;
    balls = new BallCollection;
    for(int i = 0; i < 16; i++) {
        auto ball = new Ball;
        ball->position.x = randint(ball->radius, WIDTH - ball->radius);
        ball->position.y = randint(ball->radius, HEIGHT - ball->radius);
        ball->color = 0xFF000000 + randint(0x000000, 0xFFFFFF);
        balls->add(ball);
    }

    while(cont) {
        // Input
        event(&cont);

        // Physics
        balls->forEach(ballPhysics);
        

        // Graphics
        disp->clear();
        balls->forEach(ballGraphics, disp);
        disp->refresh();

    }

    // Delete
    delete disp;
    delete balls;
    return 0;
}
