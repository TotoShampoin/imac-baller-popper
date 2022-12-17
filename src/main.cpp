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
    // Initialisation
    auto disp = new Displayator { WIDTH , HEIGHT };
    bool cont = true;

    srand(time(NULL));

    int len = 16;
    Ball* ball = new Ball[len];
    for(int i = 0; i < len; i++) {
        ball[i].position.x = randint(ball[i].radius, WIDTH - ball[i].radius);
        ball[i].position.y = randint(ball[i].radius, HEIGHT - ball[i].radius);
        ball[i].color = 0xFF000000 + randint(0x000000, 0xFFFFFF);
    }

    while(cont) {
        // Input
        event(&cont);

        // Physics
        for(int i = 0; i < len; i++) {
            ball[i].update();
            ball[i].applyCollisionsAndBounce(WIDTH, HEIGHT);
        }

        // Graphics
        disp->clear();
        for(int i = 0; i < len; i++) {
            disp->circle(
                ball[i].position.x,
                ball[i].position.y,
                ball[i].radius,
                ball[i].color
            );
        }
        disp->refresh();
    }
    delete disp;
    return 0;
}
