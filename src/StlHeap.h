#ifndef HEAPS_STL_HEAP_H
#define HEAPS_STL_HEAP_H

#include <set>
#include "IHeap.h"
#include "HeapExceptions.h"

template<typename T>
class StlHeap : public IHeap<T> {
    std::multiset<int> data;
public:
    StlHeap() = default;

    StlHeap(T key) {
        data.insert(key);
    }

    void insert(const T &key) override {
        data.insert(key);
    }

    T getMin() override {
        if (data.empty()) {
            throw EmptyHeapException();
        }
        return *data.begin();
    }

    T extractMin() override {
        if (data.empty()) {
            throw EmptyHeapException();
        }
        T minKey = *data.begin();
        data.erase(data.begin());
        return minKey;
    }

    void meld(IHeap<T> &other) override {
        if (this == &other) {
            return;
        }
        try {
            StlHeap<T> &otherCasted = dynamic_cast<StlHeap<T> &>(other);
            data.insert(otherCasted.data.begin(), otherCasted.data.end());
            otherCasted.data.clear();
        } catch (const std::bad_cast &e) {
            throw IncorrectHeapTypeException();
        }
    }

    unsigned int size() override {
        return data.size();
    }
};

#endif //HEAPS_STL_HEAP_H
