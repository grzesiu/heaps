#include <iostream>

#include "fibonacci.hpp"

int main()
{
    Fibonacci<int> f;
    Fibonacci<int>::Node **nodes = new Fibonacci<int>::Node *[100];

    for (int i = 0; i < 100; i++)
    {
        nodes[i] = f.push(i);
    }
    std::cout << f.top()->get_key() << std::endl;

    f.decrease_priority(nodes[50], -1);

    std::cout << f.top()->get_key() << std::endl;

    f.pop();

    std::cout << f.top()->get_key() << std::endl;

    f.erase(nodes[99]);
    std::cout << nodes[99]->get_key() << std::endl;
    return 0;
}