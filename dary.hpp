#include <vector>

template <typename T>
class Dary
{
  int d;
  std::vector<T> nodes;
  void heapify(int i);
  int parent(int i);
  int left(int i);
  int right(int i);

public:
  Dary(const std::vector<T> &nodes, int d);
  bool empty() const;
  int size() const;
  T top() const;
  void push(T val);
  void pop();
};

#include "dary.tpp"