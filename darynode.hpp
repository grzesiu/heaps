#pragma once

#include "node.hpp"
#include "fibheap.hpp"

template<typename I, typename K>
class Darynode : public Node<I, K> {
    template<typename, typename>
    friend
    class Daryheap;

public:
    Darynode(I id, K key);
};

#include "darynode.tpp"