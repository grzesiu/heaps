#include <functional>

template <typename T>
class Fibonacci
{
public:
  class Node
  {
  public:
    Node(T key);
    bool is_marked() const;
    bool get_value() const;

  private:
    T key;
    bool marked = false;
    Node *parent = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *child = nullptr;
  };
  Fibonacci();
  Fibonacci(std::function<bool(T const &, T const &)> comp);
  bool empty() const;
  unsigned int size() const;
  const T top() const;
  void push(Node *node);
  const T pop();
  void decrease_key(Node *node, T key);

private:
  Node *root;
  unsigned int n = 0;
};

#include "fibonacci.tpp"
