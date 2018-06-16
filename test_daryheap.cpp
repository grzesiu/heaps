#include <iostream>
#include <vector>

#include "daryheap.hpp"

int main() {

    Daryheap<int, int> d(3);
    for (int i = 9; i >= 0; i--) {
        d.push(i, i);
    }

    d.increase_priority(8, 5);
    d.increase_priority(9, 3);
    d.increase_priority(2, 0);

    while (!d.empty()) {
        std::cout << d.top().first << " " << d.top().second << std::endl;
        d.pop();
    }
    return 0;
}