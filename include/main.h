#include "displayator.h"
#include "ball.h"
#include "linkedlistball.h"

#include "mymath.h"
#include <ctime>
#include <iostream>
using namespace std;

#define WIDTH 1280
#define HEIGHT 720

struct MouseData {
    Vec2 position;
    bool click = false;
    bool is_down = false;
};

void event(bool* cont, MouseData* mouse);
void ballPhysics(Ball* ball, void* = nullptr);
void ballGraphics(Ball* ball, void* _disp);
bool ballContact(Ball* ball, void* _p);
