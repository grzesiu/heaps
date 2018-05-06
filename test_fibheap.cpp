#include <iostream>

#include "fibheap.hpp"

int main()
{
    Fibheap<int, int> f;

    for (int i = 0; i < 100; i++)
    {
        f.push(i, i);
    }
    std::cout << f.top().second << std::endl;

    f.increase_priority(50, -1);

    std::cout << f.top().second << std::endl;

    f.pop();

    std::cout << f.top().second << std::endl;

    f.erase(99);
    std::cout << f.size() << std::endl;
    
    return 0;
}