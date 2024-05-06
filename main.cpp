#include <iostream>
#include "deque.hpp"

int main() {
    Deque<int> dq;
    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);
    dq.push_back(4);
    dq.push_back(5);
    dq.push_back(6);
    for (int i = 0; i < dq.size(); ++i) {
        std::cout << dq[i] << " ";
    }


    return 0;
}
