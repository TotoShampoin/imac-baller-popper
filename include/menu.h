#include <string>
#include "displayator.h"

#define LEVEL_LIST_POSITION 128

/**
 * Une structure permettant de savoir quel niveau est choisit, 
 * ou si le joueur veut fermer le jeu.
 */
struct Choice {
    bool go_to_level = true;
    std::string level = "";
};

// Toute la boucle du menu dans cette fonction.
Choice menu(Displayator* D);
