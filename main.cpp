#include <iostream>

#include "fibonacci.hpp"

int main()
{
    Fibonacci<int> f;
    f.push(4);
    std::cout << f.top()->get_key() << std::endl;
    f.pop();
    f.push(4);
    f.push(2);
    f.push(8);
    f.push(10);
    std::cout << f.top()->get_key() << std::endl;
    f.pop();
    std::cout << f.top()->get_key() << std::endl;
    f.pop();
    std::cout << f.top()->get_key() << std::endl;
    f.pop();
    std::cout << f.top()->get_key() << std::endl;
    f.pop();
    std::cout << f.top()->get_key() << std::endl;
    return 0;
}