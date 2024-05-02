#include <iostream>
#include "deque.hpp"

int main() {
    Deque<int> dq{8};
    for (int i = 0; i < dq.size(); ++i) {
        std::cout << dq[i] << " ";
    }


    return 0;
}
