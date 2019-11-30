#ifndef HEAPS_BINOMIAL_HEAP_H
#define HEAPS_BINOMIAL_HEAP_H

#include "../src/iheap.h"

template<typename T>
class BinomialHeap : IHeap<T> {
    struct Node {
        T key;
        int degree;
        Node *child;
        Node *sibling;
    };

    Node *head = nullptr;

public:
    void insert(T key) override {

    }

    T getMin() override {
        return nullptr;
    }

    T extractMin() override {
        return nullptr;
    }

    void meld(IHeap<T> &other) override {

    }
};

#endif //HEAPS_BINOMIAL_HEAP_H
