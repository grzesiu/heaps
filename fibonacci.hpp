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
    int degree = 0;
    Node(T key);
    Node *parent = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *child = nullptr;

  public:
    bool is_marked() const;
    T get_key() const;
    Node *get_parent() const;
    Node *get_left() const;
    Node *get_right() const;
    Node *get_child() const;
  };
  Fibonacci();
  Fibonacci(std::function<bool(T const &, T const &)> comp);
  bool empty() const;
  int size() const;
  Node *top() const;
  Node *push(T val);
  void pop();
  void increase_priority(Node *node, T key);
  void erase(Node *node);

private:
  Node *root;
  int n = 0;
  Node *push(Node *node);
  int get_max_degree() const;
  void consolidate();
  Node *merge(Node *parent, Node *child);
  void insert(Node *parent, Node *child);
  void cut(Node *parent, Node *child);
  void cascading_cut(Node *node);
};

#include "fibonacci.tpp"
