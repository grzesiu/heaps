#pragma once

template <typename I, typename K>
class Node
{
public:
  Node(I id, K key);
  I get_id() const;
  K get_key() const;

protected:
  I id;
  K key;
};

#include "node.tpp"