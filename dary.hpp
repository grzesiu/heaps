#include <vector>

template <typename T>
class Dary
{
    std::vector<T> nodes;
    unsigned int d;
  public:
    Dary(std::vector<T> nodes, unsigned int d);
};

#include "dary.tpp"