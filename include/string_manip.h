#ifndef __STRING_MANIP_H__
#define __STRING_MANIP_H__

#include <string>

/**
 * Fonction qui vérifie si une chaîne de caractère se termine par une autre.
 */
bool ends_with(std::string const & value, std::string const & ending);

/**
 * Fonction qui remplace toute instance de old_part dans str par new_part
 */
void replace(std::string* str, std::string old_part, std::string new_part);

/**
 * Fonction qui prend le nom d'un fichier et en sépare le nom de l'extension.
 */
void splitExtention(const char* path, char** name, char** ext);

#endif