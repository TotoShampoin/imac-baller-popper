#include "main.h"

int main(int argc, const char* argv[]) {
    // Variables
    bool cont;
    Displayator* disp;
    BallCollection* balls;
    MouseData mouse;
    int maxball;

    // Initialisation
    srand(time(NULL));
    disp = new Displayator { WIDTH , HEIGHT };
    balls = new BallCollection;
    maxball = (argc == 1) ? 16 : argc - 1;
    for(int i = 0; i < maxball; i++) {
        int color = (argc == 1) 
            ? randint(0x000000, 0xFFFFFF) 
            : std::stoi(argv[i + 1], 0, 16);
        balls->add(new Ball(WIDTH, HEIGHT, color));
    }

    // Game loop
    cont = true;
    while(cont) {
        // Input
        event(&cont, &mouse);

        // Physics
        balls->forEach(ballPhysics);
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
        disp->text(16, 16, to_string(balls->length).c_str());
        disp->refresh();

        // SDL_Delay(1000/60);
    }

    // Delete
    delete disp;
    delete balls;
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

void ballPhysics(Ball* ball, void*) {
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

bool ballContact(Ball* ball, void* _p) {
    Vec2 position = *(Vec2*)_p;
    bool res = !((ball->position - position).magnitude2() <= ball->radius * ball->radius);
    return res;
}
