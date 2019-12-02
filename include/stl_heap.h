#ifndef HEAPS_STL_HEAP_H
#define HEAPS_STL_HEAP_H

#include <set>
#include "../src/iheap.h"
#include "../src/exceptions.h"

template<typename T>
class StlHeap : public IHeap<T> {
    std::multiset<T> data;
public:
    void insert(T key) override {
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
        try {
            std::set<T> otherData = dynamic_cast<StlHeap<T> &>(other).data();
            this->data.insert(otherData.begin(), otherData.end());
        } catch (std::bad_cast e) {
            throw IncorrectHeapTypeException();
        }
    }
};

#endif //HEAPS_STL_HEAP_H
