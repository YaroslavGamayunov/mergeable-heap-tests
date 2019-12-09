#ifndef HEAPS_LEFTIST_NODE_H
#define HEAPS_LEFTIST_NODE_H

#include "BaseNode.h"
#include <algorithm>

template<typename T>
class LeftistNode : public BaseNode<T, LeftistNode<T>> {
public:
    int rank;

    LeftistNode(T key) : BaseNode<T, LeftistNode<T>>(key) {
        rank = 0;
    }

    LeftistNode(LeftistNode<T> *node) : BaseNode<T, LeftistNode<T>>(node->key) {
        rank = node->rank;
        BaseNode<T, LeftistNode<T>>::key = node->key;
        BaseNode<T, LeftistNode<T>>::left = node->left == nullptr ? nullptr : new LeftistNode<T>(node->left);
        BaseNode<T, LeftistNode<T>>::right = node->right == nullptr ? nullptr : new LeftistNode<T>(node->right);
    }

    static LeftistNode<T> *meld(LeftistNode<T> *x, LeftistNode<T> *y) {
        if (x == nullptr) {
            return y;
        }
        if (y == nullptr) {
            return x;
        }
        if (y->BaseNode<T, LeftistNode<T>>::key < x->BaseNode<T, LeftistNode<T>>::key) {
            std::swap(x, y);
        }

        x->right = meld(x->right, y);

        int rankLeft = x->left == nullptr ? 0 : x->left->rank;
        int rankRight = x->right == nullptr ? 0 : x->right->rank;

        if (rankLeft < rankRight) {
            std::swap(x->left, x->right);
        }
        x->rank = std::min(rankLeft, rankRight) + 1;
        return x;
    }
};

#endif //HEAPS_LEFTIST_NODE_H
