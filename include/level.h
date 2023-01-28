#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <fstream>
#include <iostream>

#include "linkedlistball.h"
#include "wall.h"
#include "string_manip.h"

#define DIR_LEVEL "assets/levels/"
#define DIR_SAVE "assets/saves/"

/**
 * Une structure qui connait les informations sur la partie de jeu en cours (une partie par niveau).
 */
struct SaveState {
    std::string level_path;
    int nb_clicks = 0;
    int nb_success = 0;
    int score = 0;
};

// Fonctions de chargement et de sauvegarde, pour le dernier score du joueur.
SaveState loadState(std::string);
void saveState(SaveState*);

/**
 * Une structure de niveau, connaissant ses balles et ses murs, ainsi que son fichier.
 */
struct Level {
    std::string path;
    BallCollection* balls;
    WallCollection* walls;

    Level(const char* path);
    ~Level();
};

#endif