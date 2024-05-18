#include <iostream>
#include "deque.hpp"
#include <deque>

int main() {
    Deque<int> dq;
    std::deque<int> d;
    dq.push_front(1);
    dq.push_front(2);
    dq.push_front(3);
    dq.push_front(4);
    dq.push_front(5);
    dq.push_front(6);
    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);
    dq.push_back(4);
    dq.push_back(5);
    dq.push_back(6);
    for (int i = 0; i < dq.size(); ++i) {
        std::cout << dq[i] << " ";
    }
    std::cout << std::endl << dq.size() << std::endl;
    dq.pop_front();
    dq.pop_front();
    dq.pop_front();
    dq.pop_back();
    dq.pop_back();
    dq.pop_back();

    std::cout << dq.size() << std::endl;
    for (int i = 0; i < dq.size(); ++i) {
        std::cout << dq[i] << " ";
    }


    return 0;
}
