#include <fstream>
#include <iostream>
#include <string>

#include "linkedlistball.h"
#include "wall.h"

#define DIR_LEVEL "assets/levels/"
#define DIR_SAVE "assets/saves/"

struct SaveState {
    std::string level_path;
    int nb_clicks = 0;
    int nb_success = 0;
    int score = 0;
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

