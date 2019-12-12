#ifndef HEAPS_SKEW_HEAP_H
#define HEAPS_SKEW_HEAP_H

#include "../src/IHeap.h"
#include "../src/BaseHeap.h"
#include "../src/nodes/SkewNode.h"

template<typename T>
class SkewHeap : public BaseHeap<T, SkewNode<T>> {
public:
    SkewHeap() : BaseHeap<T, SkewNode<T>>() {}

    SkewHeap(const T &key) : BaseHeap<T, SkewNode<T>>(key) {}
};

#endif //HEAPS_SKEW_HEAP_H
