#ifndef __MENU_H__
#define __MENU_H__

#include "displayator.h"
#include "level.h"

#define LEVEL_LIST_POSITION 128

/**
 * Une structure permettant de savoir quel niveau est choisit, 
 * ou si le joueur veut fermer le jeu.
 */
struct Choice {
    bool go_to_level = true;
    std::string level = "";
};

// Lit le dossier assets/levels et met les infos dans des tables.
void readLevels(std::string** levels, int** scores, int* nb_levels);

// Toute la boucle du menu dans cette fonction.
Choice menu(Displayator* D);

#endif