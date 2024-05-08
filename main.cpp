#include <iostream>
#include "deque.hpp"

int main() {
    Deque<int> dq;
    dq.push_front(1);
    dq.push_front(2);
    dq.push_front(3);
    dq.push_front(4);
    dq.push_front(5);
    dq.push_front(6);
    for (int i = 0; i < dq.size(); ++i) {
        std::cout << dq[i] << " ";
    }


    return 0;
}
