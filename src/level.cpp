#include "level.h"
#include "string_manip.h"
#include <SDL2/SDL.h>
using namespace std;

int count = 10;
float readNextNumber(fstream* file) {
    string next;
    float number = 0;
    do {
        *file >> next;
        try {
            number = stof(next);
            break;
        } catch(const std::exception& e) {
            continue;
        }
    } while(!file->eof());
    return number;
}

SaveState loadState(std::string level_name) {
    try {
        fstream file;
        string file_name = string(DIR_SAVE) + level_name;
        replace(&file_name, ".ball", ".sav");
        file.open(file_name, ios::in);
        SaveState state = {
            string(level_name)
        };
        file >> state.nb_clicks >> state.nb_success >> state.score;
        file.close();
        return state;
    }
    catch(const std::exception& e) {
        return SaveState {
            string(level_name),
            0, 0, 0
        };
    }
}
void saveState(SaveState* state) {
    fstream file;
    string file_name = string(DIR_SAVE) + state->level_path;
    replace(&file_name, ".ball", ".sav");
    file.open(file_name, ios::out | ios::trunc);
    file << state->nb_clicks << " " << state->nb_success << " " << state->score;
    file.close();
}

Level::Level(const char* path) {
    fstream file;
    file.open(path, ios::in);

    string head;
    int number, r, c;
    Vec2 pA, pB;

    // WALLS
    number = readNextNumber(&file);
    this->walls = new WallCollection(number);
    for(int w = 0; w < number; w++) {
        pA.x = readNextNumber(&file);
        pA.y = readNextNumber(&file);
        pB.x = readNextNumber(&file);
        pB.y = readNextNumber(&file);
        (*this->walls)[w].pA = pA;
        (*this->walls)[w].pB = pB;
    }

    // BALLS
    number = readNextNumber(&file);
    this->balls = new BallCollection;
    for(int b = 0; b < number; b++) {
        pA.x = readNextNumber(&file);
        pA.y = readNextNumber(&file);
        pB.x = readNextNumber(&file);
        pB.y = readNextNumber(&file);
        r = readNextNumber(&file);
        c = readNextNumber(&file);
        this->balls->add(new Ball(pA, pB / 100., r, c));
    }

    file.close();

    this->path = path;
}

Level::~Level() {
    delete this->walls;
    delete this->balls;
}
