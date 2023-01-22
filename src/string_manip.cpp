#include "string_manip.h"

// https://stackoverflow.com/questions/874134/find-out-if-string-ends-with-another-string-in-c
bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

void replace(std::string* str, std::string old_part, std::string new_part) {
    for(int i = 0; i < str->size(); i++) {
        if(std::equal(old_part.begin(), old_part.end(), str->begin() + i)) {
            str->replace(i, old_part.size(), new_part);
        };
    }
}
