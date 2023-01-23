#include "displayator.h"
#include "ball.h"
#include "linkedlistball.h"
#include "wall.h"

#include "mymath.h"
#include <ctime>
#include <iostream>
using namespace std;

void ballPhysics(Ball* ball, void* = nullptr);
void ballGraphics(Ball* ball, void* _disp);
bool ballContact(Ball* ball, void* _p);

void wallGraphics(Wall* wall, void* _disp);
