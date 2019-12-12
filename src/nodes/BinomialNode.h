#ifndef HEAPS_BINOMIAL_NODE_H
#define HEAPS_BINOMIAL_NODE_H

template<typename T>
class BinomialNode {
public:
    T key;
    int degree;
    BinomialNode *child;
    BinomialNode *sibling;

    // cuts ties with other nodes
    void detach() {
        child = nullptr;
        sibling = nullptr;
    }

    void addChild(BinomialNode *node) {
        degree++;
        BinomialNode *firstChild = child;
        child = node;
        child->sibling = firstChild;
    }

    BinomialNode() : degree(-1), child(nullptr), sibling(nullptr) {}

    explicit BinomialNode(const T &key) : key(key), degree(0), child(nullptr), sibling(nullptr) {};

    // Law of The Big Five

    BinomialNode(const BinomialNode &other) {
        key = other.key;
        degree = other.degree;
        child = other.child == nullptr ? nullptr : new BinomialNode(*other.child);
        sibling = other.sibling == nullptr ? nullptr : new BinomialNode(*other.sibling);
    }

    BinomialNode(BinomialNode &&other) noexcept {
        key = other.key;
        degree = other.degree;

        child = other.child;
        other.child = nullptr;

        sibling = other.sibling;
        other.sibling = nullptr;
    }

    BinomialNode &operator=(const BinomialNode &other) {
        if (this == &other) {
            return *this;
        }
        BinomialNode tmp(other);

        child = nullptr;
        sibling = nullptr;

        std::swap(*this, tmp);
        return *this;
    }

    BinomialNode &operator=(BinomialNode &&other) noexcept {
        if (this == &other) {
            return *this;
        }

        child = nullptr;
        sibling = nullptr;

        std::swap(*this, other);
        return *this;
    }

    ~BinomialNode() {
        delete child;
        delete sibling;
    }
};

#endif //HEAPS_BINOMIAL_NODE_H
