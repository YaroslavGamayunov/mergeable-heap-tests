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
};

#endif //HEAPS_LEFTIST_HEAP_H
