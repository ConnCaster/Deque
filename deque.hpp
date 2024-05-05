#pragma once

#include <cmath>
#include <iostream>
#include <array>

const unsigned int kFive = 5;
const double kFiveDouble = 5.0;

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

    const T &operator[] (size_t index) const;

    T &at(size_t index);

    const T &at(size_t index) const;

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
          number_buckets_{static_cast<size_t>(ceil(count / kFiveDouble))},
          front_{0, 0},
          rear_{0, 0} {
              try {
                  buckets_ = new T *[number_buckets_];
              } catch (...) {
                  throw;
              }

    for (int i = 0; i < number_buckets_; ++i) {
        try{
            buckets_[i] = new T[kFive]{};
        } catch (...) {
            for (int j = 0; j < i-1; ++j) {
                delete[]buckets_[j];
            }
            delete[] buckets_;
            throw;
        }
    }
    rear_[0] = number_buckets_ - 1;
    rear_[1] = (count % kFive == 0) ? 4 : count % kFive - 1;
}

template<typename T>
Deque<T>::Deque(size_t count, const T &value)
        : size_{count},
          number_buckets_{static_cast<size_t>(ceil(count / kFiveDouble))},
          front_{0, 0},
          rear_{0, 0} {
      try{
          buckets_ = new T *[number_buckets_];
      }catch (...) {
          throw;
      }
      for (int i = 0; i < number_buckets_; ++i) {
          try{
          buckets_[i] = new T[kFive]{value,value,value,value,value};  // это дикий костыль!
          } catch (...) {
              for (int j = 0; j < i-1; ++j) {
                  delete[]buckets_[j];
              }
              delete[] buckets_;
              throw;
          }
      }
      rear_[0] = number_buckets_ - 1;
      rear_[1] = (count % kFive == 0) ? 4 : count % kFive - 1;


}

/*template<typename T>
Deque<T>::Deque(size_t count, const T &value)
        : size_{count},
          number_buckets_{static_cast<size_t>(ceil(count / 5.0))},
          front_{0, 0},
          rear_{0, 0} {
    if constexpr (!std::is_default_constructible_v<T>) {
        throw std::exception();
    } else {
        buckets_ = new T *[number_buckets_];
        for (int i = 0; i < number_buckets_; ++i) {
            buckets_[i] = new T[kFive]{};
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
    }

    rear_[0] = number_buckets_ - 1;
    rear_[1] = (count % kFive == 0) ? 4 : count % kFive - 1;
}*/

template<class T>
Deque<T>::Deque(const Deque &other)
        : size_{other.size_},
          number_buckets_{other.number_buckets_},
          front_{other.front_},
          rear_{other.rear_} {
    if (size_ != 0) {
        try{
            buckets_ = new T *[number_buckets_];
        }catch (...) {
            throw;
        }
        for (int i = 0; i < number_buckets_-1; ++i) {
            try{
                buckets_[i] = new T[kFive]{T{0},T{0},T{0},T{0},T{0}};
            } catch (...) {
                for (int j = 0; j < i-1; ++j) {
                    delete[]buckets_[j];
                }
                delete[] buckets_;
                throw;
            }
            for (int j = 0; j < kFive; ++j) {
                buckets_[i][j] = other.buckets_[i][j];
            }
        }
        try{
            buckets_[number_buckets_-1] = new T[kFive]{T{0},T{0},T{0},T{0},T{0}};
        } catch (...) {
            for (int j = 0; j < number_buckets_-1; ++j) {
                delete[]buckets_[j];
            }
            delete[] buckets_;
            throw;
        }
        for (int j = 0; j < other.rear_[1]; ++j) {
            buckets_[number_buckets_-1][j] = other.buckets_[number_buckets_-1][j];
        }
    } else {
        buckets_ = nullptr;
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
    try{
        buckets_ = new T *[number_buckets_];
    }catch (...) {
        throw;
    }
    for (int i = 0; i < number_buckets_; ++i) {
        try{
        buckets_[i] = new T[kFive];
        } catch (...) {
            for (int j = 0; j < i-1; ++j) {
                delete[]buckets_[j];
            }
            delete[] buckets_;
            throw;
        }
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
const T &Deque<T>::operator[](size_t index) const {
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

template<class T>
const T &Deque<T>::at(size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return buckets_[front_[0] + index / kFive][index % kFive];
}


template <class T>
void Deque<T>::push_back(const T& value) {
        if (!buckets_) {
            try{
                buckets_ = new T*[1];
            } catch (...) {
                throw;
            }
            try {
                buckets_[0] = new T[kFive]{value, value, value, value, value};
            } catch (...) {
                delete[] buckets_;
                throw;
            }
            try {
                buckets_[0][0] = value;
            } catch (...) {
                throw;
            }
            ++size_;
            ++number_buckets_;
            front_ = {0, 0};
            rear_ = {0, 0};
        } else {
            if (rear_[0] == number_buckets_ - 1 && rear_[1] == kFive - 1) {
                T **new_buckets = nullptr;
                try {
                    new_buckets = new T *[number_buckets_ + 1];
                } catch (...) {
                    throw;
                }
                for (int i = 0; i < number_buckets_; ++i) {
                    try{
                        new_buckets[i] = new T[kFive]{value, value, value, value, value};
                    } catch (...) {
                        for (int j = 0; j < i - 1; ++j) {
                            delete[] new_buckets[j];
                        }
                        delete[] new_buckets;
                        throw;
                    }
                    for (int j = 0; j < kFive; ++j) {
                        new_buckets[i][j] = buckets_[i][j];
                    }
                }
                for (int i = 0; i < number_buckets_; ++i) {
                    delete[] buckets_[i];
                }
                delete[] buckets_;
                buckets_ = new_buckets;
                try {
                    buckets_[number_buckets_] = new T[kFive]{value, value, value, value, value};
                } catch(...) {
                    for (int j = 0; j < number_buckets_; ++j) {
                        delete[] buckets_[j];
                    }
                    delete[] buckets_;
                    throw;
                }
                try {
                    buckets_[number_buckets_][0] = value;
                } catch (...) {
                    for (int j = 0; j < number_buckets_; ++j) {
                        delete[] buckets_[j];
                    }
                    delete[] buckets_;
                    throw;
                }
                ++number_buckets_;
                rear_[0] = number_buckets_-1;
                rear_[1] = 0;
                ++size_;
            } else {
                try {
                    buckets_[rear_[0]][rear_[1] + 1] = value;
                } catch (...) {
                    for (int j = 0; j < number_buckets_; ++j) {
                        delete[] buckets_[j];
                    }
                    delete[] buckets_;
                    throw;
                }
                ++rear_[1];
                ++size_;
            }
        }
}

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
