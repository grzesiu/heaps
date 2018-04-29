#include <iostream>

#include "fibonacci.hpp"

int main()
{
    Fibonacci<int> fibonacci;
    std::cout << fibonacci.empty() << std::endl;
    return 0;
}