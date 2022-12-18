#include "linkedlistball.h"

/* Linked List Node */

LLBall::LLBall(Ball* val) {
    this->value = val;
}

LLBall::~LLBall() {
    delete this->next;
}

void LLBall::add(LLBall** L, Ball* v) {
    LLBall* node = new LLBall(v);
    node->next = *L;
    *L = node;
}

Ball* LLBall::shift(LLBall** L) {
    LLBall* node = *L;
    Ball* value = node->value;
    *L = node->next;
    node->next = nullptr;
    delete node;
    return value;
}

LLBall* LLBall::filterOut(LLBall** L, bool f(Ball*, void*), void* p) {
    LLBall** scanner = L;
    LLBall* extracted_list = nullptr;
    bool is_valid;
    while(*scanner) {
        is_valid = f((*scanner)->value, p);
        if(!is_valid) {
            Ball* extract = LLBall::shift(scanner);
            LLBall::add(&extracted_list, extract);
        } else {
            scanner = &(*scanner)->next;
        }
    }
    return extracted_list;
}

void LLBall::forEach(LLBall* L, void f(Ball*, void*), void* p) {
    LLBall* node = L;
    while(node) {
        f(node->value, p);
        node = node->next;
    }
}

void increment(Ball*, void* i) {
    (*(int*)i)++;
}
int LLBall::length(LLBall* L) {
    int length = 0;
    LLBall::forEach(L, increment, &length);
    return length;
}


/* Linked List */

LinkedListBall::LinkedListBall(LLBall* L) {
    this->head = L;
    this->length = LLBall::length(L);
}

LinkedListBall::~LinkedListBall() {
    delete this->head;
}

void LinkedListBall::add(Ball* val) {
    LLBall::add(&this->head, val);
    this->length++;
}

Ball* LinkedListBall::shift() {
    Ball* extract = LLBall::shift(&this->head);
    this->length--;
    return extract;
}

LinkedListBall* LinkedListBall::filterOut(bool f(Ball*, void*), void* p) {
    LLBall* extracted = LLBall::filterOut(&this->head, f, p);
    LinkedListBall* exlist = new LinkedListBall(extracted);
    this->length -= exlist->length;
    return exlist;
}

void LinkedListBall::forEach(void f(Ball*, void*), void* p) {
    LLBall::forEach(this->head, f, p);
}
