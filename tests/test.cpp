#include <catch2/catch_all.hpp>
#include "deque.hpp"

TEST_CASE("Ctor default", "[Deque][Ctor]") {
    Deque<int> dq{};
    CHECK(dq.size() == 0);
    CHECK(dq.empty());
}

TEST_CASE("Ctor with 1 arg", "[Deque][Ctor]") {
    {
        Deque<int> dq{7};
        CHECK(dq.size() == 7);
        CHECK(dq.get_buckets_number() == 2);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 1);
        CHECK(dq.get_rear()[1] == 1);
    }
    {
        Deque<int> dq{5};
        CHECK(dq.size() == 5);
        CHECK(dq.get_buckets_number() == 1);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 0);
        CHECK(dq.get_rear()[1] == 4);
    }
    {
        Deque<int> dq{2};
        CHECK(dq.size() == 2);
        CHECK(dq.get_buckets_number() == 1);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 0);
        CHECK(dq.get_rear()[1] == 1);
    }
    {
        Deque<int> dq{10};
        CHECK(dq.size() == 10);
        CHECK(dq.get_buckets_number() == 2);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 1);
        CHECK(dq.get_rear()[1] == 4);
    }
    {
        Deque<int> dq{11};
        CHECK(dq.size() == 11);
        CHECK(dq.get_buckets_number() == 3);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 2);
        CHECK(dq.get_rear()[1] == 0);
    }
}

TEST_CASE("Assign operator", "[Deque][Ctor]") {
    {
        Deque<int> dq1{3};
        Deque<int> dq2{6};
        CHECK(dq1.size() == 3);
        CHECK(dq2.size() == 6);
        dq1 = dq2;
        CHECK(dq1.size() == 6);
        CHECK(dq2.size() == 6);
        CHECK(dq1[0] == dq2[0]);
        CHECK(dq1[5] == dq2[5]);
    }
}

TEST_CASE("Ctor copy", "[Deque][Ctor]") {
    {
        Deque<int> dq1{3};
        Deque<int> dq2{dq1};
        CHECK(dq1.size() == 3);
        CHECK(dq2.size() == 3);
        CHECK(dq1[0] == dq2[0]);
        CHECK(dq1[2] == dq2[2]);
    }
    {
        Deque<int> dq1{6};
        Deque<int> dq2{dq1};
        CHECK(dq1.size() == 6);
        CHECK(dq2.size() == 6);
        CHECK(dq1[0] == dq2[0]);
        CHECK(dq1[5] == dq2[5]);
    }
}