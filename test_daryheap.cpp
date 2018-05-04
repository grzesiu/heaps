#include <iostream>
#include <vector>

#include "daryheap.hpp"

int main()
{

    std::vector<Darynode<int> *> nodes(100);
    for (int i = 99; i >= 0; i--)
    {
        nodes[i] = new Darynode<int>(i, 99 - i);
    }

    Daryheap<int> d(nodes, 3);

    while (!d.empty())
    {
        std::cout << d.top()->get_key() << std::endl;
        d.pop();
    }

    return 0;
}