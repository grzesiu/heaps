#pragma once

#include <vector>

#include "heap.hpp"
#include "darynode.hpp"

template <typename T>
class Daryheap : public Heap<Darynode<T>, T>
{
public:
  Daryheap(const std::vector<Darynode<T> *> nodes, int d);
  bool empty() const;
  int size() const;
  Darynode<T> *top() const;
  void push(Darynode<T> *node);
  void pop();
  void increase_priority(Darynode<T> *node, T key);
  void erase(Darynode<T> *node);

private:
  int d;
  std::vector<Darynode<T> *> nodes;
  void heapify(int i);
  int parent_index(int i);
  int left_index(int i);
  int right_index(int i);
  void swap_indices(int i, int j);
};

#include "daryheap.tpp"