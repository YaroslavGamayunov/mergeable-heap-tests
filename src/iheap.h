#ifndef HEAPS_IHEAP_H
#define HEAPS_IHEAP_H

template<typename T>
class IHeap {
public:

    virtual void insert(T key) = 0;

    virtual T getMin() = 0;

    virtual T extractMin() = 0;

    virtual unsigned int size() = 0;

    virtual void meld(IHeap<T> &other) = 0;

};

#endif //HEAPS_IHEAP_H
