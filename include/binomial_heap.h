#ifndef HEAPS_BINOMIAL_HEAP_H
#define HEAPS_BINOMIAL_HEAP_H

#include <typeinfo>
#include <iostream>
#include "../src/iheap.h"
#include "../src/exceptions.h"

template<typename T>
class BinomialHeap : public IHeap<T> {
    struct Node {

        T key;
        int degree;
        Node *child;
        Node *sibling;

        void addChild(Node *node) {
            degree++;
            Node *firstChild = child;
            child = node;
            child->sibling = firstChild;
        }

        Node() : degree(-1), child(nullptr), sibling(nullptr) {}

        Node(T key) : key(key), degree(0), child(nullptr), sibling(nullptr) {};
    };

    Node *head = nullptr;

    BinomialHeap(Node *head) : head(head) {}

public:
    BinomialHeap() = default;

    explicit BinomialHeap(T key) {
        head = new Node(key);
    }

    void insert(T key) override {
        BinomialHeap<T> h(key);
        meld(h);
    }

    T getMin() override {
        if (head == nullptr) {
            throw EmptyHeapException();
        }
        Node *node = head;
        T minKey = head->key;
        while (node != nullptr) {
            minKey = std::min(minKey, node->key);
            node = node->sibling;
        }
        return minKey;
    }

    T extractMin() override {
        if (head == nullptr) {
            throw EmptyHeapException();
        }
        Node *minNode = head;
        Node *prevMinNode = nullptr;

        Node *node = head;
        Node *prev = nullptr;
        while (node != nullptr) {
            if (node->key < minNode->key) {
                minNode = node;
                prevMinNode = prev;
            }
            prev = node;
            node = node->sibling;
        }

        if (prevMinNode != nullptr) {
            prevMinNode->sibling = minNode->sibling;
        }

        T minKey = minNode->key;
        Node *child = minNode->child;
        delete minNode;
        BinomialHeap h(child);
        meld(h);
        return minKey;
    }

    void meld(IHeap<T> &x) override {
        if (this == &x) {
            return;
        }

        BinomialHeap *other = dynamic_cast<BinomialHeap<T> *>(&x);
        if (other == nullptr) {
            throw IncorrectHeapTypeException();
        }

        Node *resultBegin = new Node();
        Node *resultEnd = resultBegin;

        Node *thisNode = head;
        Node *otherNode = other->head;

        while (thisNode != nullptr && otherNode != nullptr) {
            if (thisNode->degree < otherNode->degree) {
                resultEnd->sibling = thisNode;
                thisNode = thisNode->sibling;
            } else {
                resultEnd->sibling = otherNode;
                otherNode = otherNode->sibling;
            }
            resultEnd = resultEnd->sibling;
        }

        if (thisNode != nullptr) {
            resultEnd->sibling = thisNode;
        } else if (otherNode != nullptr) {
            resultEnd->sibling = otherNode;
        }

        head = resultBegin->sibling;
        delete resultBegin;
        makeTreeOrdersUnique();
    }

    void makeTreeOrdersUnique() {
        Node *node = head;

        Node *resultBegin = new Node();
        Node *resultEnd = resultBegin;
        Node *previousNode = nullptr;


        // 1 1 2 -> 2 2
        // 1 1 2 4 -> 2 2 4 -> 4 4 -> 8

        while (node != nullptr) {
            Node *nextNode = node->sibling;
            if (resultEnd->degree != node->degree) {
                resultEnd->sibling = node;
                previousNode = resultEnd;
                resultEnd = resultEnd->sibling;
            } else {
                if (node->key < resultEnd->key) {
                    previousNode->sibling = node;
                    node->addChild(resultEnd);
                    resultEnd = node;
                } else {
                    resultEnd->addChild(node);
                }
            }
            node = nextNode;
        }
        resultEnd->sibling = nullptr;
        head = resultBegin->sibling;
        delete resultBegin;
    }
};

#endif //HEAPS_BINOMIAL_HEAP_H
