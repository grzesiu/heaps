#pragma once

#include "node.hpp"

template <typename T>
class Fibnode : public Node<T>
{
public:
  Fibnode(T key);
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