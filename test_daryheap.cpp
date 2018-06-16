#include <iostream>
#include <vector>

#include "daryheap.hpp"

int main() {

    Daryheap<int, int> d(3);
    for (int i = 9; i >= 0; i--) {
        d.push(i, i);
    }

    d.increase_priority(9, 5);

    while (!d.empty()) {
        std::cout << d.top().first << " " << d.top().second << std::endl;
        d.pop();
    }
    return 0;
}