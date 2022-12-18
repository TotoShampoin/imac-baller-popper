#include "displayator.h"
#include "ball.h"
#include "linkedlistball.h"

#include "mymath.h"
#include <ctime>
#include <iostream>
using namespace std;

#define WIDTH 720
#define HEIGHT 540

struct MouseData {
    Vec2 position;
    bool click = false;
    bool is_down = false;
};

void event(bool* cont, MouseData* mouse) {
    int mx, my, mc;
    bool was_down = mouse->is_down;
    SDL_Event event_handler;
    SDL_PollEvent(&event_handler);
    switch (event_handler.type){
    case SDL_QUIT:
        *cont = false;
        break;
    default: break;
    }
    SDL_PumpEvents();
    mc = SDL_GetMouseState(&mx, &my);
    mouse->is_down = SDL_BUTTON(mc) == SDL_BUTTON_LEFT;
    if(mouse->is_down) {
        mouse->click = !was_down;
    } else {
        mouse->click = false;
    }
    mouse->position.x = mx;
    mouse->position.y = my;
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
        ball->color,
        ball->marked
    );
}
int indx;
bool ballContact(Ball* ball, void* _p) {
    Vec2 position = *(Vec2*)_p;
    bool res = !((ball->position - position).magnitude2() <= ball->radius * ball->radius);
    return res;
}

int main(int argc, const char* argv[]) {
    // Variables
    bool cont;
    Displayator* disp;
    BallCollection* balls;
    MouseData mouse;

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
        event(&cont, &mouse);

        // Physics
        balls->forEach(ballPhysics);
        indx = 0;
        if(mouse.click) {
            BallCollection* removed = balls->filterOut(ballContact, (void*)&mouse.position);
            delete removed;
        }

        // Graphics
        disp->clear();
        balls->forEach(ballGraphics, disp);
        disp->circle(mouse.position.x, mouse.position.y, 3, 0xFFFFFFFF, false);
        disp->refresh();

        // SDL_Delay(1000/60);
    }

    // Delete
    delete disp;
    delete balls;
    return 0;
}
