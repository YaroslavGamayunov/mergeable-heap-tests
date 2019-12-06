#ifndef HEAPS_BINOMIAL_HEAP_H
#define HEAPS_BINOMIAL_HEAP_H

#include <typeinfo>
#include <iostream>
#include "../src/iheap.h"
#include "../src/heap_exceptions.h"

template<typename T>
class BinomialHeap : public IHeap<T> {
    class Node {
    public:
        T key;
        int degree;
        Node *child;
        Node *sibling;

        void detach() {
            child = nullptr;
            sibling = nullptr;
        }

        void addChild(Node *node) {
            degree++;
            Node *firstChild = child;
            child = node;
            child->sibling = firstChild;
        }

        // Law of The Big Five

        Node(const Node &other) {
            key = other.key;
            degree = other.degree;
            child = other.child == nullptr ? nullptr : new Node(*other.child);
            sibling = other.sibling == nullptr ? nullptr : new Node(*other.sibling);
        }

        Node(Node &&other) noexcept {
            key = other.key;
            degree = other.degree;

            child = other.child;
            other.child = nullptr;

            sibling = other.sibling;
            other.sibling = nullptr;
        }

        Node &operator=(const Node &other) {
            if (this == &other) {
                return *this;
            }
            Node tmp(other);

            child = nullptr;
            sibling = nullptr;

            std::swap(*this, tmp);
            return *this;
        }

        Node &operator=(Node &&other) noexcept {
            if (this == &other) {
                return *this;
            }

            child = nullptr;
            sibling = nullptr;

            std::swap(*this, other);
            return *this;
        }

        ~Node() {
            delete child;
            delete sibling;
        }

        //

        Node() : degree(-1), child(nullptr), sibling(nullptr) {}

        explicit Node(T key) : key(key), degree(0), child(nullptr), sibling(nullptr) {};
    };

    explicit BinomialHeap(Node *head) : head(head) {} // shallow copy

    void makeDegreesUnique() {
        Node *node = head;

        Node *resultBegin = new Node();
        Node *resultEnd = resultBegin;
        Node *previousNode = nullptr;


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
        resultBegin->sibling = nullptr;
        delete resultBegin;
    }

    Node *head = nullptr;
    unsigned int heapSize = 0;

public:
    BinomialHeap() = default;

    explicit BinomialHeap(T key) {
        head = new Node(key);
        heapSize = 1;
    }

    // Law of The Big Five
    BinomialHeap(const BinomialHeap &other) {
        head = new Node(*other.head);
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

    void insert(T key) override {
        BinomialHeap<T> h(key);
        meld(h);
    }

    T getMin() override {
        if (heapSize == 0) {
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
        } else {
            head = head->sibling;
        }

        T minKey = minNode->key;
        Node *child = minNode->child;

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

        resultBegin->detach();
        delete resultBegin;

        heapSize += other->heapSize;
        other->heapSize = 0;
        other->head = nullptr;
        makeDegreesUnique();
    }

    unsigned int size() override {
        return heapSize;
    }
};

#endif //HEAPS_BINOMIAL_HEAP_H