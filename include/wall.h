#ifndef __WALL_H__
#define __WALL_H__

#include "ball.h"

/**
 * Une classe représentant un mur, en jeu.
 * Un mur connait ses points aux extrémitées.
 */
struct Wall {
    Vec2 pA, pB;

    Vec2 getDirection();

    bool detectLineCollision(Ball*);
    bool detectCollision(Ball*);
    Vec2 impact(Vec2&);
    Vec2 normal(Vec2&);
    void bounce(Ball*);

    /**
     * Applique les algorithmes de collision et de rebondissement
     * de la balle sur le mur en une seule fonction.
     */
    void bounceMechanics(Ball*);
};

/**
 * Une classe représentant une table de murs.
 * Aucune logique de variation de la taille n'est appliquée ici.
 */
struct WallCollection {
    Wall* walls;
    int length;
    WallCollection(int);
    ~WallCollection();

    Wall& operator[](int);

    /**
     * Exécute la fonction fallback sur tous les murs de la table.
     */
    void forEach(void(Wall*, void*), void* = nullptr);
    /**
     * Applique les algorithmes de collision et de rebondissement
     * de la balle sur tous les murs.
     */
    void bounceMechanics(Ball*);
};

#endif