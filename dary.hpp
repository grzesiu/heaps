#include <vector>

template <typename T>
class Dary
{
    std::vector<T> nodes;
    unsigned int d;

  public:
    Dary(std::vector<T> nodes, unsigned int d);
    bool empty() const;
    unsigned int size() const;
    T top() const;
    void push(T val);
    void pop();
};

#include "dary.tpp"