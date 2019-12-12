#ifndef HEAPS_BINOMIAL_HEAP_H
#define HEAPS_BINOMIAL_HEAP_H

#include <typeinfo>
#include <iostream>
#include "../src/IHeap.h"
#include "../src/HeapExceptions.h"
#include "../src/nodes/BinomialNode.h"

template<typename T>
class BinomialHeap : public IHeap<T> {
public:
    void insert(const T &key) override {
        BinomialHeap<T> h(key);
        meld(h);
    }

    T getMin() override {
        if (heapSize == 0) {
            throw EmptyHeapException();
        }
        BinomialNode<T> *node = head;
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
        BinomialNode<T> *minNode = head;
        BinomialNode<T> *prevMinNode = nullptr;

        BinomialNode<T> *node = head;
        BinomialNode<T> *prev = nullptr;
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
        } else {
            head = head->sibling;
        }

        T minKey = minNode->key;
        BinomialNode<T> *child = minNode->child;

        minNode->detach();
        delete minNode;

        BinomialHeap h(child);
        meld(h);

        heapSize--;
        if (heapSize == 0) {
            head = nullptr;
        }

        return minKey;
    }

    void meld(IHeap<T> &x) override {
        if (this == &x) {
            return;
        }

        auto *other = dynamic_cast<BinomialHeap<T> *>(&x);
        if (other == nullptr) {
            throw IncorrectHeapTypeException();
        }

        BinomialNode<T> *resultBegin = new BinomialNode<T>();
        BinomialNode<T> *resultEnd = resultBegin;

        BinomialNode<T> *thisNode = head;
        BinomialNode<T> *otherNode = other->head;

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

        resultBegin->detach();
        delete resultBegin;

        heapSize += other->heapSize;
        other->heapSize = 0;
        other->head = nullptr;
        makeDegreesUnique();
    }

    BinomialHeap() = default;

    explicit BinomialHeap(const T &key) {
        head = new BinomialNode<T>(key);
        heapSize = 1;
    }

    // Law of The Big Five
    BinomialHeap(const BinomialHeap &other) {

        if (other.head != nullptr) {
            head = new BinomialNode<T>(*other.head);
        }
        heapSize = other.heapSize;
    }

    BinomialHeap(BinomialHeap &&other) noexcept {
        head = other.head;
        other.head = nullptr;

        heapSize = other.heapSize;
        other.heapSize = 0;
    }


    BinomialHeap &operator=(const BinomialHeap &other) {
        if (this == &other) {
            return *this;
        }
        BinomialHeap tmp(other);

        head = nullptr;
        heapSize = 0;

        swap(*this, tmp);
        return *this;
    }

    BinomialHeap &operator=(const BinomialHeap &&other) noexcept {
        if (this == &other) {
            return *this;
        }

        head = nullptr;
        heapSize = 0;

        swap(*this, other);
        return *this;
    }

    ~BinomialHeap() {
        delete head;
    }

    //

    unsigned int size() override {
        return heapSize;
    }

private:
    BinomialNode<T> *head = nullptr;
    unsigned int heapSize = 0;

    void makeDegreesUnique() {
        BinomialNode<T> *node = head;

        BinomialNode<T> *resultBegin = new BinomialNode<T>(); // begin of the list containing trees with unique degrees
        BinomialNode<T> *resultEnd = resultBegin;
        BinomialNode<T> *previousNode = nullptr;


        while (node != nullptr) {
            BinomialNode<T> *nextNode = node->sibling;
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
        resultBegin->sibling = nullptr;
        delete resultBegin;
    }

    explicit BinomialHeap(BinomialNode<T> *head) : head(head) {} // shallow copy
};

#endif //HEAPS_BINOMIAL_HEAP_H