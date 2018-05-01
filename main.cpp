#include <iostream>
#include <vector>

#include "dary.hpp"

int main()
{
    std::vector<int> nodes = {1, 2, 3, 4};
    Dary<int> d(nodes, 3);
    return 0;
}