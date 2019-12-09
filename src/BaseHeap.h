#ifndef HEAPS_BASEHEAP_H
#define HEAPS_BASEHEAP_H

#include "IHeap.h"
#include "HeapExceptions.h"

template<typename T, typename NodeType>
class BaseHeap : public IHeap<T> {
    explicit BaseHeap(NodeType *head) {
        this->head = head;
    }

public:

    unsigned int heapSize;
    NodeType *head;  // todo hide these public fields

    BaseHeap() : heapSize(0), head(nullptr) {}

    BaseHeap(const T &key) {
        head = new NodeType(key);
        heapSize = 1;
    }

    // Law of The Big Five
    BaseHeap(const BaseHeap &other) {
        if (other.head != nullptr) {
            head = new NodeType(*other.head);
        }
        heapSize = other.heapSize;
    }

    BaseHeap(BaseHeap &&other) noexcept {
        head = other.head;
        other.head = nullptr;

        heapSize = other.heapSize;
        other.heapSize = 0;
    }


    BaseHeap &operator=(const BaseHeap &other) {
        if (this == &other) {
            return *this;
        }
        BaseHeap tmp(other);

        head = nullptr;
        heapSize = 0;

        swap(*this, tmp);
        return *this;
    }

    BaseHeap &operator=(const BaseHeap &&other) noexcept {
        if (this == &other) {
            return *this;
        }

        head = nullptr;
        heapSize = 0;

        swap(*this, other);
        return *this;
    }

    ~BaseHeap() {
        delete head;
    }

    //

    void insert(const T &key) override {
        NodeType *node = new NodeType(key);
        head = NodeType::meld(head, node);
        heapSize++;
    }

    T getMin() override {
        if (head == nullptr) {
            throw EmptyHeapException();
        }
        return head->key;
    }

    T extractMin() override {
        if (head == nullptr) {
            throw EmptyHeapException();
        }
        T minKey = head->key;

        NodeType *mergedChildren = NodeType::meld(head->left, head->right);

        head->detach();
        delete head;

        head = mergedChildren;
        heapSize--;
        return minKey;
    }

    unsigned int size() override {
        return heapSize;
    }
};

#endif //HEAPS_BASEHEAP_H
