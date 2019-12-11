#ifndef HEAPS_SKEW_NODE_H
#define HEAPS_SKEW_NODE_H

#include "BaseNode.h"

template<typename T>
class SkewNode : public BaseNode<T, SkewNode<T>> {
public:
    static SkewNode<T> *meld(SkewNode<T> *x, SkewNode<T> *y) {
        if (x == nullptr) {
            return y;
        }
        if (y == nullptr) {
            return x;
        }
        if (x->key < y->key) {
            SkewNode<T> *tmp = x->right;
            x->right = x->left;
            x->left = meld(y, tmp);
            return x;
        }
        return meld(y, x);
    }

    SkewNode(T key) : BaseNode<T, SkewNode<T>>(key) {}
};


#endif //HEAPS_SKEW_NODE_H
