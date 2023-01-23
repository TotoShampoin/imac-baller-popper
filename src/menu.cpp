#include "menu.h"
#include "level.h"
#include "string_manip.h"
#include <iostream>
#include <dirent.h>

using namespace std;

void readLevels(string** levels, int** scores, int* nb_levels);

Choice menu(Displayator* D) {
    string* levels; int* scores;
    int nb_levels = 0, page = 0;
    MouseData mouse;
    bool cont;
    string name, chosen;
    
    Image* logo = D->loadImage("assets/logo.png");

    readLevels(&levels, &scores, &nb_levels);

    cont = true;
    while(cont) {
        D->event(&cont, &mouse);
        if(!cont) {
            SDL_FreeSurface(logo->image);
            delete logo;
            return Choice { false };
        }

        D->clear();
        D->image(logo, 120, 0);
        for(int i = 0; i < 8; i++) {
            if(i + page >= nb_levels) {
                D->text("_", 48, LEVEL_LIST_POSITION + i * 24, 0xFF000055, 16);
                continue;
            }
            name = levels[i + page];
            replace(&name, ".ball", "");

            if(
                mouse.position.y >= LEVEL_LIST_POSITION + (i  ) * 24 &&
                mouse.position.y <  LEVEL_LIST_POSITION + (i+1) * 24
            ) {
                D->rect(0, LEVEL_LIST_POSITION + i * 24, 480, 24, 0xFF550055);
                if(mouse.click) {
                    cont = false;
                    chosen = levels[i + page];
                    D->rect(0, LEVEL_LIST_POSITION + i * 24, 480, 24, 0xFF5500AA);
                }
            }
            D->text(name.c_str(), 48, LEVEL_LIST_POSITION + i * 24, 0xFFFFFFFF, 16);
            D->text(to_string(scores[i + page]).c_str(), 320, LEVEL_LIST_POSITION + i * 24, 0xFFAA55FF, 16);
        }
        D->rect( 96, LEVEL_LIST_POSITION + 8 * 24, 48, 24, 0xFFAA5500);
        D->rect(320, LEVEL_LIST_POSITION + 8 * 24, 48, 24, 0xFFAA5500);
        if(
            mouse.position.y >= LEVEL_LIST_POSITION + 8 * 24 &&
            mouse.position.y <  LEVEL_LIST_POSITION + 8 * 24 + 24
        ) {
            if(
                mouse.position.x >=  96 && 
                mouse.position.x <   96 + 48
            ) {
                D->rect( 96, LEVEL_LIST_POSITION + 8 * 24, 48, 24, 0xFFFF8800);
                if(mouse.click && page > 0) {
                    page--;
                }
            }
            if(
                mouse.position.x >= 320 && 
                mouse.position.x <  320 + 48
            ) {
                D->rect(320, LEVEL_LIST_POSITION + 8 * 24, 48, 24, 0xFFFF8800);
                if(mouse.click && (page+1) * 8 < nb_levels) {
                    page++;
                }
            }
        }
        D->text("<",  96 + 18, LEVEL_LIST_POSITION + 8 * 24, 0xFFFFFFFF, 20);
        D->text(">", 358 - 18, LEVEL_LIST_POSITION + 8 * 24, 0xFFFFFFFF, 20);
        D->refresh();
    }

    do {
        D->event(&cont, &mouse);
    } while(mouse.is_down);

    SDL_FreeSurface(logo->image);
    delete logo;

    return Choice { true, chosen.c_str() };
}

// Pour toute la partie lire un dossier:
// https://c-for-dummies.com/blog/?p=3246
void readLevels(string** levels, int** scores, int* nb_levels) {
    DIR* level_dir = opendir(DIR_LEVEL);
    SDL_assert(level_dir != NULL);
    struct dirent* entry;

    // On compte le nombre de fichiers
    *nb_levels = 0;
    while( (entry = readdir(level_dir)) ) {
        string name = entry->d_name;
        if(ends_with(name, ".ball")) {
            (*nb_levels)++;
        }
    }

    *levels = new string[*nb_levels + 1];
    *scores = new int[*nb_levels + 1];

    int i = 0;
    rewinddir(level_dir);
    while( (entry = readdir(level_dir)) ) {
        string name = entry->d_name;
        if(ends_with(name, ".ball")) {
            SaveState record = loadState(name);
            (*levels)[i] = name;
            (*scores)[i] = record.score;
            i++;
        }
    }

    closedir(level_dir);
}
