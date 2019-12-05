#ifndef HEAPS_TESTER_H
#define HEAPS_TESTER_H

#include <random>
#include "../src/stl_heap.h"
#include "assertions.h"

class Tester {
    enum OperationType {
        ADD, INSERT, GET_MIN, EXTRACT_MIN, MELD
    };

    static const int OPERATION_TYPE_COUNT = 5;
    static const unsigned int ITERATION_COUNT = 50000;

    struct Operation {
        OperationType type;
        int key;
        unsigned int id1, id2;
    };

    template<template<typename> class HeapType>
    class HeapWrapping {
        StlHeap<int> correctHeap;
        HeapType<int> testHeap;
    public:
        HeapWrapping() = default;

        explicit HeapWrapping(int key) {
            correctHeap = StlHeap<int>(key);
            testHeap = HeapType<int>(key);
        }

        void insert(int key) {
            correctHeap.insert(key);
            testHeap.insert(key);
            ASSERT_EQUAL(testHeap.size(), correctHeap.size());
        }

        void getMin() {
            ASSERT_EQUAL(correctHeap.extractMin(), testHeap.extractMin());
        }

        void extractMin() {
            ASSERT_EQUAL(testHeap.size(), correctHeap.size());
            ASSERT_EQUAL(correctHeap.extractMin(), testHeap.extractMin());
        }

        void meld(HeapWrapping<HeapType> &other) {
            correctHeap.meld(other.correctHeap);
            testHeap.meld(other.testHeap);

            ASSERT_EQUAL(testHeap.size(), correctHeap.size());
            ASSERT_EQUAL(other.correctHeap.size(), other.testHeap.size());
        }

        unsigned int size() {
            return correctHeap.size();
        }

    };

    std::vector<Operation> generateOperations() {
        std::vector<Operation> operations;
        int countOfHeaps = 0;

        std::mt19937 rnd(0);

        for (int i = 0; i < ITERATION_COUNT; i++) {
            if (countOfHeaps == 0) {
                operations.push_back(Operation{ADD});
                countOfHeaps++;
            } else {
                unsigned int id1 = rnd() % countOfHeaps;
                unsigned int id2 = rnd() % countOfHeaps;
                int key = rnd();

                auto currentOperationType = OperationType((size_t) (rnd() % OPERATION_TYPE_COUNT));
                if (currentOperationType == ADD) {
                    countOfHeaps++;
                }

                operations.push_back(Operation{currentOperationType, key, id1, id2});
            }
        }
        return operations;
    };

public:

    template<template<typename> class HeapType>
    void test() {

        std::vector<Operation> operations = generateOperations();
        std::vector<HeapWrapping<HeapType>> heaps;

        for (Operation &op : operations) {

            switch (op.type) {
                case ADD: {
                    ASSERT_NO_THROW(heaps.push_back(HeapWrapping<HeapType>(op.key)));
                    break;
                }

                case INSERT: {
                    ASSERT_NO_THROW(heaps[op.id1].insert(op.key));
                    break;
                }
                case GET_MIN: {
                    if (heaps[op.id1].size() == 0) {
                        ASSERT_THROW(heaps[op.id1].getMin(), EmptyHeapException);
                    } else {
                        ASSERT_NO_THROW(heaps[op.id1].getMin())
                    }
                    break;
                }

                case EXTRACT_MIN: {
                    if (heaps[op.id1].size() == 0) {
                        ASSERT_THROW(heaps[op.id1].extractMin(), EmptyHeapException);
                    } else {
                        ASSERT_NO_THROW(heaps[op.id1].extractMin());
                    }
                    break;
                }
                case MELD: {
                    ASSERT_NO_THROW(heaps[op.id1].meld(heaps[op.id2]));
                    break;
                }
            }
        }
    }

    Tester() = default;
};

#endif //HEAPS_TESTER_H
