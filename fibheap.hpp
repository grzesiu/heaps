#pragma once

#include <functional>

#include "heap.hpp"
#include "fibnode.hpp"

template <typename T>
class Fibheap : public Heap<Fibnode<T>, T>
{
public:
  Fibheap();
  Fibheap(std::function<bool(T const &, T const &)> comp);
  bool empty() const;
  int size() const;
  Fibnode<T> *top() const;
  void push(Fibnode<T> *node);
  void pop();
  void increase_priority(Fibnode<T> *node, T key);
  void erase(Fibnode<T> *node);

private:
  Fibnode<T> *root;
  int n = 0;
  int get_max_degree() const;
  void consolidate();
  Fibnode<T> *merge(Fibnode<T> *parent, Fibnode<T> *child);
  void insert(Fibnode<T> *parent, Fibnode<T> *child);
  void cut(Fibnode<T> *parent, Fibnode<T> *child);
  void cascading_cut(Fibnode<T> *node);
};

#include "fibheap.tpp"
