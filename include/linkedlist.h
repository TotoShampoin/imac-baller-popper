#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

template <typename T>
struct LLNode {
    T value;
    LLNode<T>* next = nullptr;
    LLNode(const T);
    ~LLNode();

static void add(LLNode<T>**, const T);
static T shift(LLNode<T>**);
static LLNode<T>* filterOut(LLNode<T>**, bool(const T, void*), void*);
static void forEach(LLNode<T>*, void(const T, void*), void*);
static int length(LLNode<T>*);
};

/**
 * @brief A linked list. Better contain pointers in it.
 * 
 * @tparam T 
 */
template <typename T>
struct LinkedList {
    LLNode<T>* head = nullptr;
    int length = 0;
    LinkedList(LLNode<T>* = nullptr);
    ~LinkedList();

    /**
     * @brief Adds element to the linked list.
     */
    void add(const T element);

    /**
     * @brief Extracts the first element from the linked list and returns it.
     */
    T shift();

    /**
     * @brief Tests all elements with fallback, extracts all elements that 
     * returned false, and returns them as a new linked list.
     */
    LinkedList<T>* filterOut(bool fallback(const T, void*), void* params = nullptr);

    /**
     * @brief Executes fallback with all elements, in order.
     */
    void forEach(void fallback(const T, void*), void* params = nullptr);
};

#endif
