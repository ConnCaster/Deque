#include <catch2/catch_all.hpp>
#include "deque.hpp"

//TEST_CASE("Ctor default original", "[Deque][Ctor]") {
//    std::deque<int> dq{};
//    CHECK(dq.size() == 0);
//    CHECK(dq.empty());
//}

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
        CHECK(dq1.get_buckets_number() == 1);
        CHECK(dq2.get_buckets_number() == 2);
        dq1 = dq2;
        CHECK(dq1.size() == 6);
        CHECK(dq2.size() == 6);
        CHECK(dq1.get_buckets_number() == 2);
        CHECK(dq2.get_buckets_number() == 2);
    }
    {
        Deque<int> dq1{3};
        Deque<int> dq2{5};
        CHECK(dq1.size() == 3);
        CHECK(dq2.size() == 5);
        CHECK(dq1.get_buckets_number() == 1);
        CHECK(dq2.get_buckets_number() == 1);
        dq1 = dq2;
        CHECK(dq1.size() == 5);
        CHECK(dq2.size() == 5);
        CHECK(dq1.get_buckets_number() == 1);
        CHECK(dq2.get_buckets_number() == 1);
    }
    SECTION("Assign after ctor with 2 args"){
        {
            Deque<int> dq1{3, 99};
            Deque<int> dq2{6, 77};
            CHECK(dq1.size() == 3);
            CHECK(dq2.size() == 6);
            CHECK(dq1.get_buckets_number() == 1);
            CHECK(dq2.get_buckets_number() == 2);
            dq1 = dq2;
            CHECK(dq1.size() == 6);
            CHECK(dq2.size() == 6);
            CHECK(dq1.get_buckets_number() == 2);
            CHECK(dq2.get_buckets_number() == 2);
            CHECK(dq1[0] == dq2[0]);
            CHECK(dq1[5] == dq2[5]);
            CHECK(dq1[0] == 77);
            CHECK(dq1[5] == 77);
        }
        {
            Deque<int> dq1{3, 99};
            Deque<int> dq2{5, 77};
            CHECK(dq1.size() == 3);
            CHECK(dq2.size() == 5);
            CHECK(dq1.get_buckets_number() == 1);
            CHECK(dq2.get_buckets_number() == 1);
            dq1 = dq2;
            CHECK(dq1.size() == 5);
            CHECK(dq2.size() == 5);
            CHECK(dq1.get_buckets_number() == 1);
            CHECK(dq2.get_buckets_number() == 1);
            CHECK(dq1[0] == dq2[0]);
            CHECK(dq1[4] == dq2[4]);
            CHECK(dq1[0] == 77);
            CHECK(dq1[4] == 77);
        }
    }
}

TEST_CASE("Ctor copy", "[Deque][Ctor]") {
    {
        Deque<int> dq1{3};
        Deque<int> dq2{dq1};
        CHECK(dq1.size() == 3);
        CHECK(dq2.size() == 3);
        CHECK(dq1.get_buckets_number()== dq2.get_buckets_number());
        CHECK(dq1.get_rear() == dq2.get_rear());
    }
    {
        Deque<int> dq1{6};
        Deque<int> dq2{dq1};
        CHECK(dq1.size() == 6);
        CHECK(dq2.size() == 6);
        CHECK(dq1.get_buckets_number()== dq2.get_buckets_number());
        CHECK(dq1.get_rear() == dq2.get_rear());
    }
}

TEST_CASE("Ctor with 2 arg", "[Deque][Ctor]") {
    {
        Deque<int> dq{1, 99};
        CHECK(dq.size() == 1);
        CHECK(dq.get_buckets_number() == 1);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 0);
        CHECK(dq.get_rear()[1] == 0);
        CHECK(dq[0] == 99);
    }
    {
        Deque<int> dq{5, 99};
        CHECK(dq.size() == 5);
        CHECK(dq.get_buckets_number() == 1);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 0);
        CHECK(dq.get_rear()[1] == 4);
        CHECK(dq[0] == 99);
        CHECK(dq[4] == 99);
    }
    {
        Deque<int> dq{7, 99};
        CHECK(dq.size() == 7);
        CHECK(dq.get_buckets_number() == 2);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 1);
        CHECK(dq.get_rear()[1] == 1);
        CHECK(dq[0] == 99);
        CHECK(dq[4] == 99);
        CHECK(dq[5] == 99);
        CHECK(dq[6] == 99);
    }
}

TEST_CASE("PushBack", "[Deque][Push]") {
    {
        Deque<int> dq;
        CHECK(dq.size() == 0);
        CHECK(dq.get_buckets_number() == 0);
        CHECK(dq.get_front()[0] == -1);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == -1);
        CHECK(dq.get_rear()[1] == 0);

        dq.push_back(99);
        CHECK(dq[0] == 99);
        CHECK(dq.size() == 1);
        CHECK(dq.get_buckets_number() == 1);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 0);
        CHECK(dq.get_rear()[1] == 0);
    }
    {
        Deque<int> dq{1};
        CHECK(dq.size() == 1);
        CHECK(dq[0] == 0);
        CHECK(dq.get_buckets_number() == 1);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 0);
        CHECK(dq.get_rear()[1] == 0);

        dq.push_back(99);
        CHECK(dq[0] == 0);
        CHECK(dq[1] == 99);
        CHECK(dq.size() == 2);
        CHECK(dq.get_buckets_number() == 1);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 0);
        CHECK(dq.get_rear()[1] == 1);
    }
    {
        Deque<int> dq{5};
        CHECK(dq.size() == 5);
        CHECK(dq[4] == 0);
        CHECK(dq.get_buckets_number() == 1);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 0);
        CHECK(dq.get_rear()[1] == 4);

        dq.push_back(99);
        CHECK(dq[4] == 0);
        CHECK(dq[5] == 99);
        CHECK(dq.size() == 6);
        CHECK(dq.get_buckets_number() == 2);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 1);
        CHECK(dq.get_rear()[1] == 0);
    }
}


TEST_CASE("PushFront", "[Deque][Push]") {
    {
        Deque<int> dq;
        CHECK(dq.size() == 0);
        CHECK(dq.get_buckets_number() == 0);
        CHECK(dq.get_front()[0] == -1);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == -1);
        CHECK(dq.get_rear()[1] == 0);

        dq.push_front(99);
        CHECK(dq[0] == 99);
        CHECK(dq.size() == 1);
        CHECK(dq.get_buckets_number() == 1);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 4);
        CHECK(dq.get_rear()[0] == 0);
        CHECK(dq.get_rear()[1] == 4);
    }
    {
        Deque<int> dq{1};
        CHECK(dq.size() == 1);
        CHECK(dq[0] == 0);
        CHECK(dq.get_buckets_number() == 1);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 0);
        CHECK(dq.get_rear()[1] == 0);

        dq.push_front(99);
        CHECK(dq[0] == 99);
        CHECK(dq[1] == 0);
        CHECK(dq.size() == 2);
        CHECK(dq.get_buckets_number() == 2);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 4);
        CHECK(dq.get_rear()[0] == 1);
        CHECK(dq.get_rear()[1] == 0);
    }
    {
        Deque<int> dq{5};
        CHECK(dq.size() == 5);
        CHECK(dq[0] == 0);
        CHECK(dq[4] == 0);
        CHECK(dq.get_buckets_number() == 1);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 0);
        CHECK(dq.get_rear()[1] == 4);

        dq.push_front(99);
        CHECK(dq[0] == 99);
        CHECK(dq[1] == 0);
        CHECK(dq[5] == 0);
        CHECK(dq.size() == 6);
        CHECK(dq.get_buckets_number() == 2);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 4);
        CHECK(dq.get_rear()[0] == 1);
        CHECK(dq.get_rear()[1] == 4);

        dq.push_front(99);
        CHECK(dq[0] == 99);
        CHECK(dq[1] == 99);
        CHECK(dq[2] == 0);
        CHECK(dq[6] == 0);
        CHECK(dq.size() == 7);
        CHECK(dq.get_buckets_number() == 2);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 3);
        CHECK(dq.get_rear()[0] == 1);
        CHECK(dq.get_rear()[1] == 4);
    }
}

TEST_CASE("PopBack", "[Deque][Pop]") {
    {
        Deque<int> dq{1};
        CHECK(dq.size() == 1);
        CHECK(dq.get_buckets_number() == 1);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 0);
        CHECK(dq.get_rear()[1] == 0);

        dq.pop_back();
        CHECK(dq.size() == 0);
        CHECK(dq.get_buckets_number() == 0);
        CHECK(dq.get_front()[0] == -1);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == -1);
        CHECK(dq.get_rear()[1] == 0);
    }
    {
        Deque<int> dq{2};
        CHECK(dq.size() == 2);
        CHECK(dq.get_buckets_number() == 1);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 0);
        CHECK(dq.get_rear()[1] == 1);

        dq.pop_back();
        CHECK(dq.size() == 1);
        CHECK(dq.get_buckets_number() == 1);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 0);
        CHECK(dq.get_rear()[1] == 0);
    }
    {
        Deque<int> dq{5};
        CHECK(dq.size() == 5);
        CHECK(dq.get_buckets_number() == 1);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 0);
        CHECK(dq.get_rear()[1] == 4);

        dq.pop_back();
        CHECK(dq.size() == 4);
        CHECK(dq.get_buckets_number() == 1);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 0);
        CHECK(dq.get_rear()[1] == 3);
    }
    {
        Deque<int> dq{6};
        CHECK(dq.size() == 6);
        CHECK(dq.get_buckets_number() == 2);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 1);
        CHECK(dq.get_rear()[1] == 0);

        dq.pop_back();
        CHECK(dq.size() == 5);
        CHECK(dq.get_buckets_number() == 1);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 0);
        CHECK(dq.get_rear()[1] == 4);
    }
    {
        Deque<int> dq{};
        CHECK(dq.size() == 0);
        CHECK(dq.get_buckets_number() == 0);
        CHECK(dq.get_front()[0] == -1);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == -1);
        CHECK(dq.get_rear()[1] == 0);

        dq.push_front(99);
        CHECK(dq[0] == 99);
        CHECK(dq.size() == 1);
        CHECK(dq.get_buckets_number() == 1);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 4);
        CHECK(dq.get_rear()[0] == 0);
        CHECK(dq.get_rear()[1] == 4);

        dq.pop_back();
        CHECK(dq.size() == 0);
        CHECK(dq.get_buckets_number() == 0);
        CHECK(dq.get_front()[0] == -1);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == -1);
        CHECK(dq.get_rear()[1] == 0);
    }
    {
        Deque<int> dq{5};
        CHECK(dq.size() == 5);
        CHECK(dq.get_buckets_number() == 1);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 0);
        CHECK(dq.get_rear()[1] == 4);

        dq.push_front(99);
        CHECK(dq[0] == 99);
        CHECK(dq.size() == 6);
        CHECK(dq.get_buckets_number() == 2);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 4);
        CHECK(dq.get_rear()[0] == 1);
        CHECK(dq.get_rear()[1] == 4);

        dq.pop_back();
        CHECK(dq.size() == 5);
        CHECK(dq.get_buckets_number() == 2);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 4);
        CHECK(dq.get_rear()[0] == 1);
        CHECK(dq.get_rear()[1] == 3);
    }
    {
        Deque<int> dq{6};
        CHECK(dq.size() == 6);
        CHECK(dq.get_buckets_number() == 2);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 1);
        CHECK(dq.get_rear()[1] == 0);

        dq.push_front(99);
        CHECK(dq[0] == 99);
        CHECK(dq.size() == 7);
        CHECK(dq.get_buckets_number() == 3);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 4);
        CHECK(dq.get_rear()[0] == 2);
        CHECK(dq.get_rear()[1] == 0);

        dq.pop_back();
        CHECK(dq.size() == 6);
        CHECK(dq.get_buckets_number() == 2);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 4);
        CHECK(dq.get_rear()[0] == 1);
        CHECK(dq.get_rear()[1] == 4);
    }
}

TEST_CASE("PopFront", "[Deque][Pop]") {
    {
        Deque<int> dq{1};
        CHECK(dq.size() == 1);
        CHECK(dq.get_buckets_number() == 1);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 0);
        CHECK(dq.get_rear()[1] == 0);

        dq.pop_front();
        CHECK(dq.size() == 0);
        CHECK(dq.get_buckets_number() == 0);
        CHECK(dq.get_front()[0] == -1);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == -1);
        CHECK(dq.get_rear()[1] == 0);
    }
    {
        Deque<int> dq{2};
        CHECK(dq.size() == 2);
        CHECK(dq.get_buckets_number() == 1);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 0);
        CHECK(dq.get_rear()[1] == 1);

        dq.pop_front();
        CHECK(dq.size() == 1);
        CHECK(dq.get_buckets_number() == 1);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 1);
        CHECK(dq.get_rear()[0] == 0);
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

        dq.pop_front();
        CHECK(dq.size() == 4);
        CHECK(dq.get_buckets_number() == 1);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 1);
        CHECK(dq.get_rear()[0] == 0);
        CHECK(dq.get_rear()[1] == 4);
    }
    {
        Deque<int> dq{6};
        CHECK(dq.size() == 6);
        CHECK(dq.get_buckets_number() == 2);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 1);
        CHECK(dq.get_rear()[1] == 0);

        dq.pop_front();
        CHECK(dq.size() == 5);
        CHECK(dq.get_buckets_number() == 2);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 1);
        CHECK(dq.get_rear()[0] == 1);
        CHECK(dq.get_rear()[1] == 0);
    }
    {
        Deque<int> dq{};
        CHECK(dq.size() == 0);
        CHECK(dq.get_buckets_number() == 0);
        CHECK(dq.get_front()[0] == -1);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == -1);
        CHECK(dq.get_rear()[1] == 0);

        dq.push_front(99);
        CHECK(dq[0] == 99);
        CHECK(dq.size() == 1);
        CHECK(dq.get_buckets_number() == 1);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 4);
        CHECK(dq.get_rear()[0] == 0);
        CHECK(dq.get_rear()[1] == 4);

        dq.pop_front();
        CHECK(dq.size() == 0);
        CHECK(dq.get_buckets_number() == 1);
        CHECK(dq.get_front()[0] == -1);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == -1);
        CHECK(dq.get_rear()[1] == 0);
    }
    {
        Deque<int> dq{5};
        CHECK(dq.size() == 5);
        CHECK(dq.get_buckets_number() == 1);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 0);
        CHECK(dq.get_rear()[1] == 4);

        dq.push_front(99);
        CHECK(dq[0] == 99);
        CHECK(dq.size() == 6);
        CHECK(dq.get_buckets_number() == 2);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 4);
        CHECK(dq.get_rear()[0] == 1);
        CHECK(dq.get_rear()[1] == 4);

        dq.pop_front();
        CHECK(dq.size() == 5);
        CHECK(dq.get_buckets_number() == 2);
        CHECK(dq.get_front()[0] == 1);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 1);
        CHECK(dq.get_rear()[1] == 4);
    }
    {
        Deque<int> dq{6};
        CHECK(dq.size() == 6);
        CHECK(dq.get_buckets_number() == 2);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 1);
        CHECK(dq.get_rear()[1] == 0);

        dq.push_front(99);
        CHECK(dq[0] == 99);
        CHECK(dq.size() == 7);
        CHECK(dq.get_buckets_number() == 3);
        CHECK(dq.get_front()[0] == 0);
        CHECK(dq.get_front()[1] == 4);
        CHECK(dq.get_rear()[0] == 2);
        CHECK(dq.get_rear()[1] == 0);

        dq.pop_front();
        CHECK(dq.size() == 6);
        CHECK(dq.get_buckets_number() == 3);
        CHECK(dq.get_front()[0] == 1);
        CHECK(dq.get_front()[1] == 0);
        CHECK(dq.get_rear()[0] == 2);
        CHECK(dq.get_rear()[1] == 0);
    }
}