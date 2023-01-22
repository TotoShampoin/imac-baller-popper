#include "menu.h"
#include "level.h"
#include "string_manip.h"
#include <iostream>
#include <dirent.h>

using namespace std;

void readLevels(string** levels, int* nb_levels);

Choice menu(Displayator* D) {
    std::string* levels;
    int nb_levels = 0, page = 0;
    MouseData mouse;
    bool cont;
    string name, chosen;

    readLevels(&levels, &nb_levels);

    cont = true;
    while(cont) {
        D->event(&cont, &mouse);
        if(!cont) return Choice { false };

        D->clear();
        for(int i = 0; i < 8; i++) {
            if(i + page >= nb_levels) {
            D->text("no entry", 24, LEVEL_LIST_POSITION + i * 24, 0xFF000055, 16);
                continue;
            }
            name = levels[i + page];
            replace(&name, "_", "-");
            replace(&name, ".ball", "");

            if(
                mouse.position.y >= LEVEL_LIST_POSITION + (i  ) * 24 &&
                mouse.position.y <  LEVEL_LIST_POSITION + (i+1) * 24
            ) {
                D->rect(0, LEVEL_LIST_POSITION + i * 24, 480, 24, 0xFF550000);
                if(mouse.click) {
                    cont = false;
                    chosen = levels[i + page];
                    D->rect(0, LEVEL_LIST_POSITION + i * 24, 480, 24, 0xFF555500);
                }
            }
            
            D->text(name.c_str(), 24, LEVEL_LIST_POSITION + i * 24, 0xFFFFFFFF, 16);
        }
        D->refresh();
    }

    do {
        D->event(&cont, &mouse);
    } while(mouse.is_down);

    return Choice { true, chosen.c_str() };
}

// Pour toute la partie lire un dossier:
// https://c-for-dummies.com/blog/?p=3246
void readLevels(string** levels, int* nb_levels) {
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

    int i = 0;
    rewinddir(level_dir);
    while( (entry = readdir(level_dir)) ) {
        string name = entry->d_name;
        if(ends_with(name, ".ball")) {
            (*levels)[i] = name;
            i++;
        }
    }

    closedir(level_dir);
}