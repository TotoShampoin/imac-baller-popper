#include <fstream>
#include <iostream>
#include <string>

#include "linkedlistball.h"
#include "wall.h"

#define DIR_LEVEL "assets/levels/"
#define DIR_SAVE "assets/saves/"

struct SaveState {
    std::string level_path;
    int nb_clicks;
    int nb_success;
    int score;
};

SaveState loadState(std::string);
void saveState(SaveState*);

struct Level {
    std::string path;
    BallCollection* balls;
    WallCollection* walls;

    Level(const char* path);
    ~Level();
};

