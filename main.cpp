#include <iostream>
#include <vector>

#include "dary.hpp"

int main()
{
    std::vector<int> nodes = {6, 3, 1, 4, 5, 0, 2};
    Dary<int> d(nodes, 3);
    for (int i = 0; i < d.size(); i++)
    {
        std::cout << d.nodes[i] << " ";
    }
    return 0;
}