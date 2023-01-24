#include "displayator.h"
#include "ball.h"
#include "linkedlistball.h"
#include "wall.h"

#include "mymath.h"
#include <ctime>
#include <iostream>
using namespace std;

// Pour faire rebondir chaque balle sur les bords et sur les murs.
void ballPhysics(Ball* ball, void* _walls = nullptr);
// Pour afficher les balles.
void ballGraphics(Ball* ball, void* _disp);
// Pour détecter les balles est cliquées à la souris.
bool ballContact(Ball* ball, void* _position);

// Pour afficher les murs.
void wallGraphics(Wall* wall, void* _disp);
