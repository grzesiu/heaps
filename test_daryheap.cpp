#include <iostream>
#include <vector>

#include "daryheap.hpp"

int main()
{
    std::vector<int> nodes = {6, 3, 1, 4, 5, 2};
    Daryheap<int> d(nodes, 3);
    while (!d.empty())
    {
        std::cout << d.top() << std::endl;
        d.pop();
    }
    return 0;
}