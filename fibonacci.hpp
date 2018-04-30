#include <functional>

template <typename T>
class Fibonacci
{
public:
  class Node
  {
    friend class Fibonacci;
    T key;
    bool is_marked() const;
    bool get_key() const;
    bool marked = false;
    unsigned int degree = 0;
    Node(T key);
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
  void push(T val);
  void pop();
  void decrease_key(Node *node, T key);

private:
  Node *root;
  unsigned int n = 0;
  void push(Node *node);
  unsigned int max_degree() const;
  void consolidate();
};

#include "fibonacci.tpp"
