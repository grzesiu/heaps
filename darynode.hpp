#pragma once

#include "node.hpp"
#include "fibheap.hpp"

template <typename T>
class Darynode : public Node<T>
{
  template <typename>
  friend class Daryheap;

public:
  Darynode(T key, int i);

private:
  int i;
};

#include "darynode.tpp"