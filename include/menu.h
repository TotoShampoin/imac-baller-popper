#include <string>
#include "displayator.h"

#define LEVEL_LIST_POSITION 128

struct Choice {
    bool go_to_level = true;
    std::string level = "";
};

Choice menu(Displayator* D);
