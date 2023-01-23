#include "string_manip.h"

// https://stackoverflow.com/questions/874134/find-out-if-string-ends-with-another-string-in-c
bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

void replace(std::string* str, std::string old_part, std::string new_part) {
    for(long unsigned int i = 0; i < str->size(); i++) {
        if(std::equal(old_part.begin(), old_part.end(), str->begin() + i)) {
            str->replace(i, old_part.size(), new_part);
        };
    }
}

void splitExtention(const char* path, char** name, char** ext) {
    const char* tmp = path;

    int path_length = 0;
    while(*(tmp++)) path_length++;

    *name = new char[path_length+1];
    *ext = new char[5];
    bool to_ext = false;
    int i = 0;

    for(tmp = path; *tmp; tmp++) {
        if(*tmp == '.') {
            to_ext = true;
            (*name)[i] = '\0';
            i = 0;
            continue;
        }
        if(!to_ext) (*name)[i] = *tmp;
        else (*ext)[i] = *tmp;
        i++;
    }
    (*ext)[i] = '\0';
}
