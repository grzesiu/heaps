#include <functional>

template <typename T>
class Fibonacci
{

  class Node
  {
  public:
    Node(T key);
    bool is_marked() const;
    bool get_value() const;

  private:
    bool marked = false;
    T key;
    Node *parent;
    Node *left;
    Node *right;
    Node *child;
  };

public:
  Fibonacci();
  Fibonacci(std::function<bool(T const &, T const &)> comp);
  bool empty() const;
  unsigned int size() const;
  const T &top() const;
  void push(const T &val);
  void pop();
  void decrease_key(Node &node, T key);
};

#include "fibonacci.tpp"
