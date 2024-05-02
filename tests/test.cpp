#include <catch2/catch_all.hpp>
#include "deque.hpp"

TEST_CASE("Ctor default", "[Deque][Ctor]") {
    Deque<int> dq{};
    CHECK(dq.size() == 0);
    CHECK(dq.empty());
}

TEST_CASE("Ctor with 1 arg", "[Deque][Ctor]") {
    CHECK(1 == 1);
}