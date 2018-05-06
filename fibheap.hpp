#pragma once

#include <functional>
#include <map>
#include <utility>

#include "heap.hpp"
#include "fibnode.hpp"

template <typename I, typename K>
class Fibheap : public Heap<Fibnode<I, K>, I, K>
{
public:
  Fibheap();
  Fibheap(std::function<bool(K const &, K const &)> comp);
  ~Fibheap();
  bool empty() const;
  int size() const;
  std::pair<I, K> top() const;
  void push(I id, K key);
  void pop();
  void increase_priority(I id, K key);
  void erase(I id);

private:
  std::map<I, Fibnode<I, K> *> nodes;
  Fibnode<I, K> *root;
  int get_max_degree() const;
  void consolidate();
  Fibnode<I, K> *merge(Fibnode<I, K> *parent, Fibnode<I, K> *child);
  void insert(Fibnode<I, K> *parent, Fibnode<I, K> *child);
  void cut(Fibnode<I, K> *parent, Fibnode<I, K> *child);
  void cascading_cut(Fibnode<I, K> *node);
};

#include "fibheap.tpp"
