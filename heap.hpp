#include <iostream>

#include "node.hpp"

template <typename N, typename T>
class Heap
{
public:
  virtual bool empty() const = 0;
  virtual int size() const = 0;
  virtual N *top() const = 0;
  virtual void push(N *node) = 0;
  virtual void pop() = 0;
  virtual void increase_priority(N *node, T key) = 0;
  virtual void erase(N *node) = 0;
};