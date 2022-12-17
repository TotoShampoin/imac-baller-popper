#include "linkedlist.h"

/* Linked List Node */

template <typename T>
LLNode<T>::LLNode(const T val) {
    this->value = val;
}

template <typename T>
LLNode<T>::~LLNode() {
    delete this->next;
}

template <typename T>
void LLNode<T>::add(LLNode<T>** L, const T v) {
    LLNode<T>* node = new LLNode(v);
    node->next = *L;
    *L = node;
}

template <typename T>
T LLNode<T>::shift(LLNode<T>** L) {
    LLNode<T>* node = *L;
    T value = node->value;
    *L = node->next;
    delete node;
    return value;
}

template <typename T>
LLNode<T>* filterOut(LLNode<T>** L, bool f(const T, void*), void* p) {
    LLNode<T>* scanner = *L;
    LLNode<T>* extracted_list = nullptr;
    bool is_valid;
    while(scanner) {
        is_valid = f(scanner->value, p);
        if(!is_valid) {
            T extract = LLNode<T>::shift(&scanner);
            LLNode<T>::add(&extracted_list, extract);
        }
        scanner = scanner->next;
    }
    return extracted_list;
}

template <typename T>
void LLNode<T>::forEach(LLNode<T>* L, void f(const T, void*), void* p) {
    LLNode<T>* node = *L;
    while(node) {
        f(node->value, p);
        node = node->next;
    }
}

void increment(void*, int* i) {
    (*i)++;
}
template <typename T>
int LLNode<T>::length(LLNode<T>* L) {
    int length = 0;
    LLNode<T>::forEach(L, increment, &length);
    return length;
}


/* Linked List */

template <typename T>
LinkedList<T>::LinkedList(LLNode<T>* L = nullptr) {
    this->head = L;
    this->length = LLNode<T>::length(L);
}

template <typename T>
LinkedList<T>::~LinkedList() {
    delete this->head;
}

template <typename T>
void LinkedList<T>::add(const T val) {
    LLNode<T>::add(&this->head, val);
    this->length++;
}

template <typename T>
T LinkedList<T>::shift() {
    LLNode<T> extract = LLNode<T>::shift(&this->head);
    return extract;
    this->length--;
}

template <typename T>
LinkedList<T>* LinkedList<T>::filterOut(bool f(const T, void*), void* p) {
    LLNode<T>* extracted = LLNode<T>::filterOut(&this->head, f, p);
    LinkedList<T>* exlist = new LinkedList(extracted);
    this->length -= exlist.length;
    return exlist;
}

template <typename T>
void LinkedList<T>::forEach(void f(const T, void*), void* p) {
    LLNode<T>::forEach(this->head, f, p);
}
