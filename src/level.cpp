#include "level.h"
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
