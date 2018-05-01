#include <functional>

template <typename T>
class Fibonacci
{
public:
  class Node
  {
    friend class Fibonacci;
    T key;
    bool marked = false;
    unsigned int degree = 0;
    Node(T key);
    Node *parent = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *child = nullptr;

  public:
    bool is_marked() const;
    T get_key() const;
  };
  Fibonacci();
  Fibonacci(std::function<bool(T const &, T const &)> comp);
  bool empty() const;
  unsigned int size() const;
  Node *top() const;
  Node *push(T val);
  void pop();
  void decrease_priority(Node *node, T key);

private:
  Node *root;
  unsigned int n = 0;
  Node *push(Node *node);
  unsigned int get_max_degree() const;
  void consolidate();
  Node *merge(Node *parent, Node *child);
  void insert(Node *parent, Node *child);
  void cut(Node *parent, Node *child);
  void cascading_cut(Node *node);
};

#include "fibonacci.tpp"
