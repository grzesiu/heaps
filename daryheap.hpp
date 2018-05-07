#pragma once

#include <vector>
#include <map>
#include <utility>

#include "heap.hpp"
#include "darynode.hpp"

template <typename I, typename K>
class Daryheap : public Heap<Darynode<I, K>, I, K>
{
public:
  Daryheap(const std::vector<Darynode<I, K>> &nodes, int d);
  bool empty() const;
  int size() const;
  std::pair<I, K> top() const;
  void push(I id, K key);
  void pop();
  void increase_priority(I id, K key);
  void erase(I id);

private:
  int d;
  std::map<I, int> indices;
  std::vector<Darynode<I, K>> nodes;
  void heapify(int i);
  int parent_index(int i);
  int left_index(int i);
  int right_index(int i);
  void swap(int i, int j);
};

#include "daryheap.tpp"