#pragma once

template <typename T>
class Node
{
public:
  Node(T key);
  T get_key() const;

protected:
  T key;
};

#include "node.tpp"