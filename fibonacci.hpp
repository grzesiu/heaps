template <typename value_type>
class Fibonacci
{

  class Node
  {
  };

public:
  explicit priority_queue(const Compare &comp = Compare());
  bool empty() const;
  size_type size() const;
  const value_type &top() const;
  void push(const value_type &val);
  void pop();

private:
};