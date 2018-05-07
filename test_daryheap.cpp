#include <iostream>
#include <vector>

#include "daryheap.hpp"

int main()
{

    std::vector<Darynode<int, int>> nodes;
    for (int i = 99; i >= 0; i--)
    {
        nodes.push_back(Darynode<int, int>(i, i));
    }

    Daryheap<int, int> d(nodes, 3);

    for (int i = 0; i < 100; i++)
    {
        std::cout << d.top().first << " " << d.top().second << std::endl;
        d.pop();
    }

    return 0;
}