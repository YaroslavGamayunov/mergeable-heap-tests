#ifndef HEAPS_LEFTIST_HEAP_H
#define HEAPS_LEFTIST_HEAP_H


#include <algorithm>
#include "../src/BaseHeap.h"
#include "../src/nodes/LeftistNode.h"

template<typename T>
class LeftistHeap : public BaseHeap<T, LeftistNode<T>> {
public:
    LeftistHeap() : BaseHeap<T, LeftistNode<T>>() {}

    LeftistHeap(const T &key) : BaseHeap<T, LeftistNode<T>>(key) {
        BaseHeap<T, LeftistNode<T>>::head->rank = 0;
    }

    void meld(IHeap<T> &x) override {
        if (this == &x) {
            return;
        }

        BaseHeap<T, LeftistNode<T>> *other = dynamic_cast<BaseHeap<T, LeftistNode<T>> *>(&x);
        if (other == nullptr) {
            throw IncorrectHeapTypeException();
        }
        BaseHeap<T, LeftistNode<T>>::head = LeftistNode<T>::meld(BaseHeap<T, LeftistNode<T>>::head,
                                                                 other->BaseHeap<T, LeftistNode<T>>::head);
        other->head = nullptr;
        BaseHeap<T, LeftistNode<T>>::heapSize += other->heapSize;
        other->heapSize = 0;

    }
};

#endif //HEAPS_LEFTIST_HEAP_H
