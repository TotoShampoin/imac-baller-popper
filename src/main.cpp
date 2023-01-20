#include "main.h"
#include "level.h"

#define WIDTH 480
#define HEIGHT 360

int main(int argc, const char* argv[]) {
    // Variables
    bool cont;
    Displayator* disp;
    Level* level;
    MouseData mouse;
    int maxball, maxwall;

    // Initialisation
    srand(time(NULL));
    maxball = 16;
    maxwall = 1;
    disp = new Displayator { WIDTH , HEIGHT , 2 };
    level = new Level("assets/levels/lvl_000.ball");

    // Game loop
    cont = true;
    while(cont) {
        // Input
        event(&cont, &mouse, disp);

        // Physics
        level->balls->forEach(ballPhysics, level->walls);
        if(mouse.click) {
            BallCollection* removed = level->balls->filterOut(ballContact, (void*)&mouse.position);
            if(removed->length == 0) {
                int color = randint(0x000000, 0xFFFFFF);
                level->balls->add(new Ball(WIDTH, HEIGHT, color));
            }
            delete removed;
        }

        // Graphics
        disp->clear();
        level->balls->forEach(ballGraphics, disp);
        level->walls->forEach(wallGraphics, disp);
        disp->text(16, 16, to_string(level->balls->length).c_str());
        disp->refresh();

        // SDL_Delay(1000/60);
    }

    // Delete
    delete disp;
    delete level;
    return 0;
}


void event(bool* cont, MouseData* mouse, Displayator* D) {
    SDL_Event event_handler;
    SDL_PollEvent(&event_handler);
    switch (event_handler.type){
    case SDL_QUIT:
        *cont = false;
        break;
    default:
        SDL_PumpEvents();
        break;
    }
    D->getMouse(mouse);
}

void ballPhysics(Ball* ball, void* _walls) {
    WallCollection* walls = (WallCollection*)_walls;
    ball->update();
    ball->applyCollisionsAndBounce(WIDTH, HEIGHT);
    walls->bounceMechanics(ball);
}

void ballGraphics(Ball* ball, void* _disp) {
    Displayator* disp = (Displayator*)_disp;
    disp->circle(
        ball->position.x,
        ball->position.y,
        ball->radius,
        ball->color
    );
    if(ball->marked)
        disp->circle(ball->position.x, ball->position.y, 4, 0xFFFFFF);
}

bool ballContact(Ball* ball, void* _p) {
    Vec2 position = *(Vec2*)_p;
    bool res = !((ball->position - position).magnitude2() <= ball->radius * ball->radius);
    return res;
}

void wallGraphics(Wall* wall, void* _disp) {
    Displayator* disp = (Displayator*)_disp;
    disp->line(
        wall->pA.x,
        wall->pA.y,
        wall->pB.x,
        wall->pB.y,
        0xFFFFFF
    );
}
