#include "game.h"

#include <cmath>
#include <ctime>
#include <iostream>
using namespace std;

int main(int argc, const char* argv[]) {
    // Variables
    bool cont, keep_open;
    Displayator* disp;
    Choice choice;

    float scale;

    // Initialisation
    srand(time(NULL));
    scale = (argc == 1) ? 1 : stof(argv[1]);
    disp = new Displayator { WIDTH , HEIGHT , scale };

    keep_open = true;
    while(keep_open) {
        // Menu zone
        choice = menu(disp);
        if(!choice.go_to_level) {
            keep_open = false;
            break;
        }
        SDL_Delay(250);
        keep_open = game(choice, disp);
    }
    delete disp;
    return 0;
}

