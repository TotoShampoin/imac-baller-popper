#include "main.h"

int main(int argc, const char* argv[]) {
    // Variables
    bool cont;
    Displayator* disp;
    BallCollection* balls;
    WallCollection* walls;
    MouseData mouse;
    int maxball;
    int maxwall;

    // Initialisation
    srand(time(NULL));
    maxball = (argc == 1) ? 16 : argc - 1;
    maxwall = 1;
    disp = new Displayator { WIDTH , HEIGHT };
    balls = new BallCollection;
    walls = new WallCollection(maxwall);
    for(int i = 0; i < maxball; i++) {
        int color = (argc == 1) 
            ? randint(0x000000, 0xFFFFFF) 
            : std::stoi(argv[i + 1], 0, 16);
        balls->add(new Ball(WIDTH, HEIGHT, color));
    }
    for(int i = 0; i < maxwall; i++) {
        (*walls)[i].pA = {120, 240};
        (*walls)[i].pB = {160, 620};
    }

    // Game loop
    cont = true;
    while(cont) {
        // Input
        event(&cont, &mouse);

        // Physics
        balls->forEach(ballPhysics, walls);
        if(mouse.click) {
            BallCollection* removed = balls->filterOut(ballContact, (void*)&mouse.position);
            if(removed->length == 0) {
                int color = randint(0x000000, 0xFFFFFF);
                balls->add(new Ball(WIDTH, HEIGHT, color));
            }
            delete removed;
        }

        // Graphics
        disp->clear();
        balls->forEach(ballGraphics, disp);
        walls->forEach(wallGraphics, disp);
        disp->text(16, 16, to_string(balls->length).c_str());
        disp->refresh();

        // SDL_Delay(1000/60);
    }

    // Delete
    delete disp;
    delete balls;
    delete walls;
    return 0;
}


void event(bool* cont, MouseData* mouse) {
    int mx, my, mc;
    bool was_down = mouse->is_down;
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
