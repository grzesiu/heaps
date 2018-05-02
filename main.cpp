#include <iostream>
#include <vector>

#include "dary.hpp"

int main()
{
    std::vector<int> nodes = {6, 3, 1, 4, 5, 0, 2};
    Dary<int> d(nodes, 3);
    while(!d.empty())
    {
        std::cout << d.top() << std::endl;
        d.pop();
    }
    return 0;
}