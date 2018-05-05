#include <iostream>

#include "fibheap.hpp"

int main()
{
    Fibheap<int> f;
    Fibnode<int> *nodes[100];

    for (int i = 0; i < 100; i++)
    {
        nodes[i] = new Fibnode<int>(i);
        f.push(nodes[i]);
    }
    std::cout << f.top()->get_key() << std::endl;

    f.increase_priority(nodes[50], -1);

    std::cout << f.top()->get_key() << std::endl;

    f.pop();

    std::cout << f.top()->get_key() << std::endl;

    f.erase(nodes[99]);
    std::cout << nodes[99]->get_key() << std::endl;

    for (int i = 0; i < 100; i++)
    {
        delete nodes[i];
    }
    
    return 0;
}