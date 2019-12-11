#ifndef HEAPS_BASE_NODE_H
#define HEAPS_BASE_NODE_H

template<typename T, typename NodeType>
class BaseNode {
public:
    T key;
    NodeType *left;
    NodeType *right;


    BaseNode(const T &key) {
        this->key = key;
        left = nullptr;
        right = nullptr;
    }

    // cuts ties with other nodes
    void detach() {
        left = nullptr;
        right = nullptr;
    }

    // Law of The Big Five
    BaseNode(const BaseNode &other) {
        key = other.key;
        left = other.left == nullptr ? nullptr : new NodeType(other.left);
        right = other.right == nullptr ? nullptr : new NodeType(other.right);
    }

    BaseNode(BaseNode &&other) noexcept {
        key = other.key;

        left = other.left;
        other.left = nullptr;

        right = other.right;
        other.right = nullptr;
    }

    BaseNode &operator=(const BaseNode &other) {
        if (this == &other) {
            return this;
        }
        BaseNode tmp(other);

        this->right = nullptr;
        this->left = nullptr;

        swap(*this, tmp);
        return *this;
    }

    BaseNode &operator=(const BaseNode &&other) {
        if (this == &other) {
            return this;
        }

        this->right = nullptr;
        this->left = nullptr;

        swap(*this, other);
        return *this;
    }

    ~BaseNode() {
        delete left;
        delete right;
    }
};

#endif //HEAPS_BASE_NODE_H
