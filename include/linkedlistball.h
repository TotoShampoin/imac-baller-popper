#ifndef __LINKEDLISTBALL_H__
#define __LINKEDLISTBALL_H__
#include "ball.h"

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
 * @brief A linked list of balls (pointers).
 */
struct LinkedListBall {
    LLBall* head = nullptr;
    int length = 0;
    LinkedListBall(LLBall* = nullptr);
    ~LinkedListBall();

    /**
     * @brief Adds element to the linked list.
     */
    void add(Ball* element);

    /**
     * @brief Extracts the first element from the linked list and returns it.
     */
    Ball* shift();

    /**
     * @brief Tests all elements with fallback, extracts all elements that 
     * returned false, and returns them as a new linked list.
     */
    LinkedListBall* filterOut(bool fallback(Ball*, void*), void* params = nullptr);

    /**
     * @brief Executes fallback with all elements, in order.
     */
    void forEach(void fallback(Ball*, void*), void* params = nullptr);
};
typedef LinkedListBall BallCollection;

#endif
