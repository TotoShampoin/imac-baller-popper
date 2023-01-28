#include "game.h"
#include <iostream>
using namespace std;

bool game(Choice choice, Displayator* disp) {
    // Variables
    bool cont, keep_open;
    Level* level;
    SaveState save_state;
    MouseData mouse;

    // Initialisation
    level = new Level((DIR_LEVEL + choice.level).c_str());
    save_state = {
        choice.level,
        0, 0, 0
    };

    // Game loop
    cont = true;
    while(true) {
        // Input
        disp->event(&cont, &mouse);
        if(!cont) {
            keep_open = false;
            break;
        }

        // Physics
        level->balls->forEach(ballPhysics, level->walls);
        if(mouse.click) {
            BallCollection* removed = level->balls->filterOut(ballContact, (void*)&mouse.position);
            save_state.nb_clicks++;
            if(removed->length == 0) {
                int color = randint(0x000000, 0xFFFFFF);
                level->balls->add(new Ball(WIDTH, HEIGHT, color));
                save_state.score -= 500;
                if(save_state.score < 0) save_state.score = 0;
            } else {
                save_state.score += pow(2, removed->length - 1) * 250;
                save_state.nb_success++;
            }
            delete removed;
        }

        // Graphics
        disp->clear();
        level->balls->forEach(ballGraphics, disp);
        level->walls->forEach(wallGraphics, disp);
        disp->text(to_string(save_state.score).c_str(), 16, 16);
        disp->refresh();

        SDL_Delay(1000/60);

        if(level->balls->length <= 0) {
            saveState(&save_state);
            break;
        }
    }
    delete level;
    if(!keep_open) return false;
    
    SDL_Delay(1000);

    string pop_rate = (to_string(100 * save_state.nb_success / save_state.nb_clicks)+"%");
    string score = to_string(save_state.score);
    while(true) {
        disp->event(&cont, &mouse);
        if(!cont) {
            keep_open = false;
            break;
        }
        if(mouse.click) break;

        disp->clear();
        disp->text("Popped!", 120, 64, 0xFFAA55FF, 64);
        disp->text("Score :", 120, 160, 0xFFFFFFFF, 16);
        disp->text(score.c_str(), 340 - (score.length() * 5), 160, 0xFFFFFFFF, 16);
        disp->text("Pop rate :", 120, 180, 0xFFFFFFFF, 16);
        disp->text(pop_rate.c_str(), 335 - (pop_rate.length() * 5), 180, 0xFFFFFFFF, 16);
        disp->refresh();
    }
    return true;
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
        ball->color + 0xAA000000
    );
    disp->circle(
        ball->position.x,
        ball->position.y,
        ball->radius - 1,
        0x55FFFFFF,
        false
    );
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
        0xFFFFFFFF
    );
}
