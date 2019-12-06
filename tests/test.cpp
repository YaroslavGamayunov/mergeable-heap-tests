
#include <gtest/gtest.h>
#include <random>
#include "../include/binomial_heap.h"
#include "../src/stl_heap.h"

class HeapTest : public ::testing::Test {

public:
    static const int OPERATION_TYPE_COUNT = 5;
    static const unsigned int ITERATION_COUNT = 100000;

    enum OperationType {
        ADD, INSERT, GET_MIN, EXTRACT_MIN, MELD
    };

    struct Operation {
        OperationType type;
        int key;
        unsigned int id1, id2;
    };

    std::vector<Operation> operations;

    void SetUp() override {
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
    }

    template<template<typename> class HeapType>
    void runTests() {
        std::vector<StlHeap<int>> correctHeaps;
        std::vector<HeapType<int>> subjectHeaps;
        
        for (Operation &op : operations) {
            switch (op.type) {

                case ADD: {
                    ASSERT_NO_THROW(correctHeaps.push_back(StlHeap<int>(op.key)));
                    ASSERT_NO_THROW(subjectHeaps.push_back(HeapType<int>(op.key)));
                    break;
                }

                case INSERT: {
                    ASSERT_NO_THROW(correctHeaps[op.id1].insert(op.key));
                    ASSERT_NO_THROW(subjectHeaps[op.id1].insert(op.key));
                    break;
                }
                case GET_MIN: {
                    if (correctHeaps[op.id1].size() == 0) {
                        ASSERT_THROW(correctHeaps[op.id1].getMin(), EmptyHeapException);
                        ASSERT_THROW(subjectHeaps[op.id1].getMin(), EmptyHeapException);
                    } else {
                        ASSERT_NO_THROW(correctHeaps[op.id1].getMin());
                        ASSERT_NO_THROW(subjectHeaps[op.id1].getMin());
                        ASSERT_EQ(correctHeaps[op.id1].getMin(), subjectHeaps[op.id1].getMin());
                    }
                    break;
                }

                case EXTRACT_MIN: {
                    if (correctHeaps[op.id1].size() == 0) {
                        ASSERT_THROW(correctHeaps[op.id1].extractMin(), EmptyHeapException);
                        ASSERT_THROW(subjectHeaps[op.id1].extractMin(), EmptyHeapException);
                    } else {
                        ASSERT_NO_THROW(correctHeaps[op.id1].extractMin());
                        ASSERT_NO_THROW(subjectHeaps[op.id1].extractMin());
                    }
                    break;
                }
                case MELD: {
                    ASSERT_NO_THROW(correctHeaps[op.id1].meld(correctHeaps[op.id2]));
                    ASSERT_NO_THROW(subjectHeaps[op.id1].meld(subjectHeaps[op.id2]));
                    break;
                }
            }

            ASSERT_EQ(correctHeaps[op.id1].size(), subjectHeaps[op.id1].size());
            ASSERT_EQ(correctHeaps[op.id2].size(), subjectHeaps[op.id2].size());
        }
    }
};

TEST_F(HeapTest, BinomialHeapTest) {
    runTests<BinomialHeap>();
}

TEST_F(HeapTest, StlHeapTest) {
    runTests<StlHeap>();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}