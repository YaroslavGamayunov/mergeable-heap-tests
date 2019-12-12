#include "HeapTest.h"
#include "../include/SkewHeap.h"
#include "../include/LeftistHeap.h"
#include "../include/BinomialHeap.h"

TEST_F(HeapTest, BinomialHeapTest) {
    runTests<BinomialHeap>();
}

TEST_F(HeapTest, LeftistHeapTest) {
    runTests<LeftistHeap>();
}

TEST_F(HeapTest, SkewHeapTest) {
    runTests<SkewHeap>();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}