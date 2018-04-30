#include <iostream>

#include "fibonacci.hpp"

int main()
{
    Fibonacci<int> f;
    f.push(4);
    f.push(2);
    f.push(10);
    std::cout << f.top();
    return 0;
}