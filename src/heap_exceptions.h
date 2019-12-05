#ifndef HEAPS_HEAP_EXCEPTIONS_H
#define HEAPS_HEAP_EXCEPTIONS_H


class IncorrectHeapTypeException : public std::exception {
public:
    const char *what() const noexcept override {
        return "Heap can't be converted to another because their types are different";
    }
};

class EmptyHeapException : public std::exception {
    char *what() const noexcept override {
        return "Heap is empty and its element can't be accessed";
    }
};

#endif //HEAPS_HEAP_EXCEPTIONS_H
