#ifndef __GAME_H__
#define __GAME_H__

#include "menu.h"
#include "contants.h"
#include "displayator.h"

// Pour lancer une partie de jeu
bool game(Choice choice, Displayator* disp);

// Pour faire rebondir chaque balle sur les bords et sur les murs.
void ballPhysics(Ball* ball, void* _walls = nullptr);
// Pour afficher les balles.
void ballGraphics(Ball* ball, void* _disp);
// Pour détecter les balles est cliquées à la souris.
bool ballContact(Ball* ball, void* _position);

// Pour afficher les murs.
void wallGraphics(Wall* wall, void* _disp);

#endif