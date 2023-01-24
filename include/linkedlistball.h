#ifndef __LINKEDLISTBALL_H__
#define __LINKEDLISTBALL_H__
#include "ball.h"

/**
 * Une classe de noeud pour les listes chaînées de balles.
 * Les comportements de ses méthodes sont décrites dans la classe des listes chaînées.
 * Les méthodes ici sont statiques afin d'éviter toute prise de tête avec le this.
 */
struct LLBall {
    Ball* value;
    LLBall* next = nullptr;
    LLBall(Ball*);
    ~LLBall();

static void add(LLBall**, Ball*);
static Ball* shift(LLBall**);
static LLBall* filterOut(LLBall**, bool(Ball*, void*), void*);
static void forEach(LLBall*, void(Ball*, void*), void*);
static int length(LLBall*);
};

/**
 * Une liste chaînée de balles (via des pointeurs).
 */
struct LinkedListBall {
    LLBall* head = nullptr;
    int length = 0;
    LinkedListBall(LLBall* = nullptr);
    ~LinkedListBall();

    /**
     * Crée un noeud et le place en tête de la liste.
     */
    void add(Ball* element);

    /**
     * Extrait le premier noeud de la liste, et renvoit sa valeur (la balle).
     */
    Ball* shift();

    /**
     * Effectue un test sur chaque noeud via la fonction fallback, 
     * extrait tout ceux qui renvoient false, et les renvoit via une nouvelle liste chaînée.
     */
    LinkedListBall* filterOut(bool fallback(Ball*, void*), void* params = nullptr);

    /**
     * Exécute la fonction fallback sur toutes les balles de la liste.
     */
    void forEach(void fallback(Ball*, void*), void* params = nullptr);
};

typedef LinkedListBall BallCollection;

#endif
