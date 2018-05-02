#include <vector>

template <typename T>
class Dary
{
  int d;
  void heapify(int i);
  int parent(int i);
  int left(int i);
  int right(int i);

public:
  std::vector<T> nodes;
  Dary(const std::vector<T> &nodes, int d);
  bool empty() const;
  int size() const;
  T top() const;
  void push(T val);
  void pop();
};

#include "dary.tpp"