#pragma once

#include "node.hpp"
#include "fibheap.hpp"

template<typename I, typename K>
class Fibnode : public Node<I, K> {
    template<typename, typename>
    friend
    class Fibheap;

public:
    Fibnode(I id, K key);

    bool is_marked() const;

private:
    bool marked = false;
    int degree = 0;
    Fibnode *parent = nullptr;
    Fibnode *left = nullptr;
    Fibnode *right = nullptr;
    Fibnode *child = nullptr;
};

#include "fibnode.tpp"