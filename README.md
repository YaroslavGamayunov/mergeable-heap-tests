<p align="center">
 <img src = "https://upload.wikimedia.org/wikipedia/commons/thumb/c/cf/Binomial_Trees.svg/1280px-Binomial_Trees.svg.png" height = 400>
</p>

# Mergeable Heaps Tests
In this project you can find implementation and test tools of three types of heap datastructure: **binomial heap**, **leftist heap** and **skew heap**

Гамаюнов Ярослав, Б05-923


# Heaps
## Binomial heap
This heap is a list of trees with unique orders. You can find more infromation on [wikipedia page](https://en.wikipedia.org/wiki/Binomial_heap "Binomial Heap")
## Leftist and Skew heaps
These heaps are almost similar because [skew heap](https://en.wikipedia.org/wiki/Skew_heap "Skew Heap") is a self-adjusting form of [leftist heap](https://en.wikipedia.org/wiki/Leftist_tree "Leftist Heap")


# Project
This project requires:
+ **CMake** 3.12+
+ **g++6**
[Google Test](https://github.com/google/googletest "Google Test") library is used to perform unit testing. You don't have do install it manually, it will be downloaded automatically after building the project
## Quick start
```
$ mkdir -p build,
$ cd build
$ cmake ..
$ make
```
## Tests
```
$ ctest
```
## Heap usage
### Construction
```C++
 BinomialHeap<int> heap1;  // creates empty heap with nodes whose 'key' field has int type
 BinomialHeap<int> heap2(3);  // creates heap with one element with key = 3
```
### Melding
```C++
heap1.meld(heap2); // now heap1 contains all elements of heap2 and heap2 is empty
```
### Insertion
```C++
heap.insert(123); // insert new node with key = 123
```
### Getting minimal value
```C++
heap.getMin(); // returns minimal key presented in the heap
heap.extractMin(); // returns minimal key presented in the heap and removes one node with this key
```
### Getting size
```C++
heap.size(); // returns number of nodes in the heap
```
