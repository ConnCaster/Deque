#pragma once

#include <cmath>
#include <iostream>
#include <concepts>

const unsigned int kFive = 5;

//template <typename T>
//concept DC = std::is_default_constructible_v<T>;


template<class T>
class Deque {
public:
    Deque();

    Deque(const Deque &other);

    explicit Deque(size_t count);

    Deque(size_t count, const T &value);

    ~Deque();

    Deque<T> &operator=(const Deque &other);

    size_t size() const;

    bool empty();

    T &operator[](size_t index);

    T &at(size_t index);

    void push_back(const T &value);

    void pop_back();

    void push_front(const T &value);

    void pop_front();

    auto get_buckets_number() const {
        return number_buckets_;
    }

    auto get_front() const {
        return front_;
    }

    auto get_rear() const {
        return rear_;
    }

private:
    size_t size_;
    size_t number_buckets_;
    std::array<long, 2> front_;
    std::array<long, 2> rear_;
    T **buckets_;
};

template<class T>
Deque<T>::Deque()
        : size_{0}, number_buckets_{0}, front_{-1, 0}, rear_{-1, 0}, buckets_{nullptr} {}


template<class T>
Deque<T>::Deque(size_t count)
        : size_{count},
          number_buckets_{static_cast<size_t>(ceil(count / 5.0))},
          front_{0, 0},
          rear_{0, 0} {
//    static_assert(std::is_default_constructible_v<T> == true);
    buckets_ = new T *[number_buckets_];
    for (int i = 0; i < number_buckets_; ++i) {
        buckets_[i] = new T[kFive]{};
    }
    rear_[0] = number_buckets_ - 1;
    rear_[1] = (count % kFive == 0) ? 4 : count % kFive - 1;
}

template<typename T>
Deque<T>::Deque(size_t count, const T &value)
        : size_{count},
          number_buckets_{static_cast<size_t>(ceil(count / 5.0))},
          front_{0, 0},
          rear_{0, 0} {
    buckets_ = new T *[number_buckets_];
    for (int i = 0; i < number_buckets_; ++i) {
        buckets_[i] = new T[kFive];
    }
    if (count % kFive == 0) {
        for (int i = 0; i < number_buckets_; ++i) {
            for (int j = 0; j < kFive; ++j) {
                buckets_[i][j] = value;
            }
        }
    } else {
        for (int i = 0; i < number_buckets_ - 1; ++i) {
            for (int j = 0; j < kFive; ++j) {
                buckets_[i][j] = value;
            }
        }
        for (int j = 0; j < count % kFive; ++j) {
            buckets_[number_buckets_ - 1][j] = value;
        }
    }
    rear_[0] = number_buckets_ - 1;
    rear_[1] = (count % kFive == 0) ? 4 : count % kFive - 1;
}

//template<class T>
//Deque<T>::Deque(size_t count, const T &value)
//        :size_(count),
//         number_buckets_{static_cast<size_t>(ceil(count / 5.0))},
//         front_{0, 0}
//{
//    buckets_ = new T *[number_buckets_];
//    for (size_t i = 0; i < number_buckets_; ++i) {
//        if (i == number_buckets_ - 1) {
//            buckets_[i] = new T[kFive];
//            if (count % kFive == 0) {
//                for (int j = 0; j < kFive; ++j) {
//                    buckets_[i][j] = value;
//                }
//                rear_ = std::array<long, 2>{static_cast<long>(ceil(count / 5.0)) - 1, kFive - 1};
//            } else {
//                for (size_t j = 0; j < count % kFive; ++j) {
//                    buckets_[i][j] = value;
//                }
//                rear_ = std::array<long, 2>{number_buckets_ - 1, static_cast<long>(count % kFive - 1)};
//            }
//        } else {
//            buckets_[i] = new T[kFive];
//            for (int j = 0; j < kFive; ++j) {
//                buckets_[i][j] = value;
//            }
//        }
//    }
//}

template<class T>
Deque<T>::Deque(const Deque &other)
        : size_{other.size_},
          number_buckets_{other.number_buckets_},
          front_{other.front_},
          rear_{other.rear_} {
    buckets_ = new T *[number_buckets_];
    for (int i = 0; i < number_buckets_; ++i) {
        buckets_[i] = new T[kFive];
        for (int j = 0; j < kFive; ++j) {
            buckets_[i][j] = other.buckets_[i][j];
        }
    }
}

template<class T>
Deque<T> &Deque<T>::operator=(const Deque<T> &other) {
    if (this == &other) {
        return *this;
    }
    for (int i = 0; i < number_buckets_; ++i) {
        delete[] buckets_[i];
    }
    delete[] buckets_;
    size_ = other.size_;
    number_buckets_ = other.number_buckets_;
    front_ = other.front_;
    rear_ = other.rear_;
    buckets_ = new T *[number_buckets_];
    for (int i = 0; i < number_buckets_; ++i) {
        buckets_[i] = new T[kFive];
        for (int j = 0; j < kFive; ++j) {
            buckets_[i][j] = other.buckets_[i][j];
        }
    }
    return *this;
}

template<class T>
Deque<T>::~Deque() {
    for (int i = 0; i < number_buckets_; ++i) {
        delete[] buckets_[i];
    }
    delete[] buckets_;
}


template<class T>
size_t Deque<T>::size() const {
    return size_;
}

template<class T>
bool Deque<T>::empty() {
    return size_ == 0;
}

template<class T>
T &Deque<T>::operator[](size_t index) {
    return buckets_[front_[0] + index / kFive][index % kFive];
}

template<class T>
T &Deque<T>::at(size_t
                index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return buckets_[front_[0] + index / kFive][index % kFive];
}

//template <class T>
//void Deque<T>::push_back(const T& value) {
//    if (!buckets_) {
//        buckets_ = new T*[1];
//        buckets_[0] = new T[kFive];
//        buckets_[0][0] = value;
//        ++size_;
//        ++number_buckets_;
//        front_ = {0, 0};
//        rear_ = {0, 0};
//    } else {
//        if (rear_.first == number_buckets_ - 1 && rear_.second == kFive - 1) {
//            T** new_buckets = new T*[number_buckets_ * 3];
//            for (int i = number_buckets_; i < number_buckets_ * 2; ++i) {
//                new_buckets[i] = buckets_[i - number_buckets_];
//            }
//            delete[] buckets_;
//            buckets_ = new_buckets;
//            buckets_[number_buckets_ * 2][0] = value;
//            rear_.first = number_buckets_ * 2;
//            rear_.second = 0;
//            front_.first = number_buckets_;
//            number_buckets_ *= 3;
//            ++size_;
//        } else {
//            buckets_[rear_.first][rear_.second + 1] = value;
//            ++rear_.second;
//            ++size_;
//        }
//    }
//}
//
//template <class T>
//void Deque<T>::pop_back() {
//    if (rear_.second == 0) {
//        buckets_[rear_.first][rear_.second] = nullptr;
//        --rear_.first;
//        rear_.second = kFive - 1;
//        --size_;
//    } else {
//        buckets_[rear_.first][rear_.second] = nullptr;
//        --rear_.second;
//        --size_;
//    }
//}
//
//template <class T>
//void Deque<T>::push_front(const T& value) {
//    if (!buckets_) {
//        buckets_ = new T*[1];
//        buckets_[0] = new T[kFive];
//        buckets_[0][kFive - 1] = value;
//        ++size_;
//        ++number_buckets_;
//        front_ = {0, kFive - 1};
//        rear_ = {0, kFive - 1};
//    } else {
//        if (front_.first == 0 && front_.second == 0) {
//            T** new_buckets = new T*[number_buckets_ * 3];
//            for (int i = number_buckets_; i < number_buckets_ * 2; ++i) {
//                new_buckets[i] = buckets_[i - number_buckets_];
//            }
//            delete[] buckets_;
//            buckets_ = new_buckets;
//            buckets_[number_buckets_ - 1][kFive - 1] = value;
//            front_.first = number_buckets_ - 1;
//            front_.second = kFive - 1;
//            rear_.first = number_buckets_ * 2;
//            number_buckets_ *= 3;
//            ++size_;
//        } else {
//            buckets_[front_.first][front_.second - 1] = value;
//            --front_.second;
//            ++size_;
//        }
//    }
//}
//
//template <class T>
//void Deque<T>::pop_front() {
//    if (front_.second == kFive - 1) {
//        buckets_[front_.first][front_.second] = nullptr;
//        ++front_.first;
//        front_.second = 0;
//        --size_;
//    } else {
//        buckets_[front_.first][front_.second] = nullptr;
//        ++front_.second;
//        --size_;
//    }
//}
