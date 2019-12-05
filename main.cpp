#include <iostream>
#include <set>
#include <vector>
#include "src/iheap.h"
#include "include/binomial_heap.h"
#include "tests/assertions.h"
#include "tests/tester.h"

int main() {

    BinomialHeap<int> h;
    Tester tester;
    tester.test<StlHeap>();


    return 0;
}