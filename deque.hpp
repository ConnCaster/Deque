#pragma once

#include <cmath>
#include <iostream>
#include <array>
#include <deque>

const unsigned int kFive = 1000;
const double kFiveDouble = 1000.0;


template<typename T>
class Deque;

template<typename T>
class Iterator {
private:
    friend class Deque<T>;

    Deque<T> *ptr_dq;
    size_t index;
public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T *;
    using reference = T &;


    Iterator() : ptr_dq{nullptr}, index{0} {}

    Iterator(Deque<T>& deque, size_t index) : ptr_dq{&deque}, index{index} {}

    Iterator(const Iterator &p) :
            ptr_dq{p.ptr_dq}, index{p.index} {}

    Iterator operator=(const Iterator &p) {
        if (this == &p) return *this;
        ptr_dq = p.ptr_dq;
        index = p.index;
        return *this;
    }


    Iterator &operator++() {
        index++;
        ptr_dq = &(ptr_dq[index]);
        return *this;
    }

//    Iterator& operator++() const{
//        ptr_dq++;
//        return *this;
//    }

    Iterator operator++(int) {
        Iterator tmp = *this;
        index++;
        ptr_dq = &(ptr_dq[index]);
        return tmp;
    }

//    Iterator operator++(int) const {
//        Iterator tmp = *this;
//        ++(*this);
//        return tmp;
//    }

    Iterator &operator--() {
        index--;
        ptr_dq = &(ptr_dq[index]);
        return *this;
    }

//    Iterator& operator--() const {
//        ptr_dq--;
//        return *this;
//    }

    Iterator operator--(int) {
        Iterator tmp = *this;
        index--;
        ptr_dq = &(ptr_dq[index]);
        return tmp;
    }

//    Iterator operator--(int) const {
//        Iterator tmp = *this;
//        --(*this);
//        return tmp;
//    }

    T &operator*() {
        return *ptr_dq[index];
    }

    T *operator->() {
        return ptr_dq[index];
    }


    friend Iterator operator+(const Iterator &it, const difference_type &n) {
        Iterator tmp = it;
        tmp += n;
        return tmp;
    }

    friend Iterator operator-(const Iterator &it, const difference_type &n) {
        Iterator tmp = it;
        tmp -= n;
        return tmp;
    }


    Iterator& operator+=(const difference_type& value) {
        index += value;
        ptr_dq = &(ptr_dq[index]);
        return *this;
    }

    Iterator& operator-=(const difference_type& value) {
        index -= value;
        ptr_dq = &(ptr_dq[index]);
        return *this;
    }

    friend difference_type operator-(const Iterator& a, const Iterator& b) {
        return a.index - b.index;
    }


    friend bool operator<(const Iterator& a, const Iterator& b) {
        return a.index < b.index;
    }

    friend bool operator>(const Iterator& a, const Iterator& b) {
        return a.index > b.index;
    }

    friend bool operator<=(const Iterator& a, const Iterator& b) {
        return a.index <= b.index;
    }

    friend bool operator>=(const Iterator& a, const Iterator& b) {
        return a.index >= b.index;
    }

    friend bool operator==(const Iterator& a, const Iterator& b) {
        return a.index == b.index;
    }

    friend bool operator!=(const Iterator& a, const Iterator& b) {
        return a.index != b.index;
    }

};

template<class T>
class Deque {
public:
    Deque();

    Deque(const Deque &other);

    explicit Deque(size_t count);

    Deque(size_t count, const T &value);

    ~Deque();

    Deque &operator=(const Deque &other);

    size_t size() const;

    bool empty();

    T &operator[](size_t index);

    const T &operator[](size_t index) const;

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


    using iterator = Iterator<T>;

    using _Iterator = Deque<T>::iterator;
    using _Const_Iterator = Deque<const T>::iterator;
    using _ReverseIterator = std::reverse_iterator<_Iterator>;
    using _Const_ReverseIterator = std::reverse_iterator<_Const_Iterator>;

    _Iterator begin() {
        if (front_[0] == -1) return _Iterator();
        return _Iterator(*this, 0);
    }

    _Const_Iterator begin() const {
        if (front_[0] == -1) return _Const_Iterator();
        return _Const_Iterator(*this, 0);
    }

    _Iterator end() {
        if (rear_[0] == -1) return _Iterator();
        return _Iterator(*this, this->size_);
    }

    _Const_Iterator end() const {
        if (rear_[0] == -1) return _Const_Iterator();
        return _Const_Iterator(*this, this->size_);
    }

    _Const_Iterator cbegin() const {
        if (front_[0] == -1) return _Const_Iterator();
        return _Const_Iterator(*this, 0);
    }

    _Const_Iterator cend() const {
        if (rear_[0] == -1) return _Const_Iterator();
        return _Const_Iterator(*this, this->size_);
    }


    //=============================================================

    _ReverseIterator rbegin() {
        return _ReverseIterator(end());
    }

    _Const_ReverseIterator rbegin() const {
        return ReverseIterator(end());
    }

    _ReverseIterator rend() {
        return _ReverseIterator(begin());
    }

    _Const_ReverseIterator rend() const {
        return ReverseIterator(begin());
    }

    _Const_ReverseIterator rcbegin() const {
        return ReverseIterator(end());
    }

    _Const_ReverseIterator rcend() const {
        return ReverseIterator(begin());
    }

    /*ReverseIterator rbegin() {
        if (rear_[0] == -1) return ReverseIterator();
        return ReverseIterator(&buckets_[rear_[0]][rear_[1]]);
    }

    Const_ReverseIterator rbegin() const {
        if (rear_[0] == -1) return Const_ReverseIterator();
        return Const_ReverseIterator(&buckets_[rear_[0]][rear_[1]]);
    }


    ReverseIterator rend() {
        if (front_[0] == -1) return ReverseIterator();
        return ReverseIterator(&buckets_[front_[0]][front_[1]]);
    }

    Const_ReverseIterator rend() const {
        if (front_[0] == -1) return Const_ReverseIterator();
        return Const_ReverseIterator(&buckets_[front_[0]][front_[1]]);
    }

    Const_ReverseIterator rcbegin() const {
        if (rear_[0] == -1) return Const_ReverseIterator();
        return Const_ReverseIterator(&buckets_[rear_[0]][rear_[1]]);
    }

    Const_ReverseIterator rcend() const {
        if (front_[0] == -1) return Const_ReverseIterator();
        return Const_ReverseIterator(&buckets_[front_[0]][front_[1]]);
    }*/


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
        try {
            buckets_[i] = new T[kFive]{};
        } catch (...) {
            for (int j = 0; j < i - 1; ++j) {
                delete[]buckets_[j];
            }
            delete[] buckets_;
            throw;
        }
    }
    rear_[0] = number_buckets_ - 1;
    rear_[1] = (count % kFive == 0) ? kFive - 1 : count % kFive - 1;
}

template<typename T>
Deque<T>::Deque(size_t count, const T &value)
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
        try {
//              buckets_[i] = new T[kFive]{value,value,value,value,value};  // это дикий костыль!
            void *rawMemory = operator new[](kFive * sizeof(T));
            buckets_[i] = static_cast<T *>(rawMemory);
            for (int j = 0; j < kFive; ++j) {
                new(&buckets_[i][j])T(value);
            }
        } catch (...) {
            for (int j = 0; j < i - 1; ++j) {
                delete[]buckets_[j];
            }
            delete[] buckets_;
            throw;
        }
    }
    rear_[0] = number_buckets_ - 1;
    rear_[1] = (count % kFive == 0) ? kFive - 1 : count % kFive - 1;


}

template<class T>
Deque<T>::Deque(const Deque &other)
        : size_{other.size_},
          number_buckets_{other.number_buckets_},
          front_{other.front_},
          rear_{other.rear_} {
    if (size_ != 0) {
        try {
            buckets_ = new T *[number_buckets_];
        } catch (...) {
            throw;
        }
        for (int i = 0; i < number_buckets_ - 1; ++i) {
            try {
//                buckets_[i] = new T[kFive]{T{0},T{0},T{0},T{0},T{0}};
                void *rawMemory = operator new[](kFive * sizeof(T));  //
                buckets_[i] = static_cast<T *>(rawMemory);              //
            } catch (...) {
                for (int j = 0; j < i - 1; ++j) {
                    delete[]buckets_[j];
                }
                delete[] buckets_;
                throw;
            }
            for (int j = 0; j < kFive; ++j) {
                try {
                    buckets_[i][j] = other.buckets_[i][j];
                } catch (...) {
                    for (int k = 0; k < i - 1; ++k) {
                        delete[]buckets_[k];
                    }
                    delete[] buckets_;
                    throw;
                }
            }
        }
        try {
//            buckets_[number_buckets_-1] = new T[kFive]{T{0},T{0},T{0},T{0},T{0}};
            void *rawMemory = operator new[](kFive * sizeof(T));                    //
            buckets_[number_buckets_ - 1] = static_cast<T *>(rawMemory);                //
        } catch (...) {
            for (int j = 0; j < number_buckets_ - 1; ++j) {
                delete[]buckets_[j];
            }
            delete[] buckets_;
            throw;
        }
        for (int j = 0; j < other.rear_[1]; ++j) {
            try {
                buckets_[number_buckets_ - 1][j] = other.buckets_[number_buckets_ - 1][j];
            } catch (...) {
                for (int k = 0; k < number_buckets_; ++k) {
                    delete[]buckets_[k];
                }
                delete[] buckets_;
                throw;
            }
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
    try {
        buckets_ = new T *[number_buckets_];
    } catch (...) {
        throw;
    }
    for (int i = 0; i < number_buckets_; ++i) {
        try {
            buckets_[i] = new T[kFive];
        } catch (...) {
            for (int j = 0; j < i - 1; ++j) {
                delete[]buckets_[j];
            }
            delete[] buckets_;
            throw;
        }
        for (int j = 0; j < kFive; ++j) {
            try {
                buckets_[i][j] = other.buckets_[i][j];
            } catch (...) {
                for (int k = 0; k < i - 1; ++k) {
                    delete[]buckets_[k];
                }
                delete[] buckets_;
            }
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
    int N_elem_from_zero = front_[0] * kFive + front_[1] + index;
    int N_bucket = N_elem_from_zero / kFive;
    int N_cell = N_elem_from_zero % kFive;
    return buckets_[N_bucket][N_cell];
}

template<class T>
const T &Deque<T>::operator[](size_t index) const {
    int N_elem_from_zero = front_[0] * kFive + front_[1];
    int N_bucket = N_elem_from_zero / kFive;
    int N_cell = N_elem_from_zero % kFive;
    return buckets_[N_bucket][N_cell];
}


template<class T>
T &Deque<T>::at(size_t
                index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    int N_elem_from_zero = front_[0] * kFive + front_[1] + index;
    int N_bucket = N_elem_from_zero / kFive;
    int N_cell = N_elem_from_zero % kFive;
    return buckets_[N_bucket][N_cell];
}

template<class T>
const T &Deque<T>::at(size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    int N_elem_from_zero = front_[0] * kFive + front_[1] + index;
    int N_bucket = N_elem_from_zero / kFive;
    int N_cell = N_elem_from_zero % kFive;
    return buckets_[N_bucket][N_cell];
}


template<class T>
void Deque<T>::push_back(const T &value) {
    if (!buckets_) {
        try {
            buckets_ = new T *[1];
        } catch (...) {
            throw;
        }
        try {
//                buckets_[0] = new T[kFive]{value, value, value, value, value};
            void *rawMemory = operator new[](kFive * sizeof(T));
            buckets_[0] = static_cast<T *>(rawMemory);
        } catch (...) {
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
                new_buckets[i] = buckets_[i];
            }
            delete[] buckets_;
            buckets_ = new_buckets;
            try {
//                    buckets_[number_buckets_] = new T[kFive]{value, value, value, value, value};
                void *rawMemory = operator new[](kFive * sizeof(T));
                buckets_[number_buckets_] = static_cast<T *>(rawMemory);
            } catch (...) {
                delete[] buckets_[number_buckets_];
                throw;
            }
            try {
                buckets_[number_buckets_][0] = value;
            } catch (...) {
                delete[] buckets_[number_buckets_];
                throw;
            }
            ++number_buckets_;
            rear_[0] = number_buckets_ - 1;
            rear_[1] = 0;
            ++size_;
        } else {
            try {
                T var{value};
                buckets_[rear_[0]][rear_[1] + 1] = value;
            } catch (...) {
                throw;
            }
            ++rear_[1];
            ++size_;
        }
    }
}


template<class T>
void Deque<T>::push_front(const T &value) {
    if (!buckets_) {
        try {
            buckets_ = new T *[1];
        } catch (...) {
            throw;
        }
        try {
//            buckets_[0] = new T[kFive]{value, value, value, value, value};
            void *rawMemory = operator new[](kFive * sizeof(T));
            buckets_[0] = static_cast<T *>(rawMemory);
        } catch (...) {
            throw;
        }
        try {
            buckets_[0][kFive - 1] = value;
        } catch (...) {
            throw;
        }
        ++size_;
        ++number_buckets_;
        front_ = {0, kFive - 1};
        rear_ = {0, kFive - 1};
    } else {
        if (front_[0] == 0 && front_[1] == 0) {
            T **new_buckets = nullptr;
            try {
                new_buckets = new T *[number_buckets_ + 1];
            } catch (...) {
                throw;
            }
            for (int i = 0; i < number_buckets_; ++i) {
                new_buckets[i + 1] = buckets_[i];
            }
            delete[] buckets_;
            buckets_ = new_buckets;

            try {
//                buckets_[0] = new T[kFive]{value, value, value, value, value};
                void *rawMemory = operator new[](kFive * sizeof(T));
                buckets_[0] = static_cast<T *>(rawMemory);
            } catch (...) {
                delete[] buckets_[number_buckets_];
                throw;
            }
            try {
                T var{value};
                buckets_[0][kFive - 1] = value;
            } catch (...) {
                delete[] buckets_[number_buckets_];
                throw;
            }
            front_[0] = 0;
            front_[1] = kFive - 1;
            ++rear_[0];
            ++number_buckets_;
            ++size_;
        } else {
            try {
                T var{value};
                buckets_[front_[0]][front_[1] - 1] = value;
            } catch (...) {
                throw;
            }
            --front_[1];
            ++size_;
        }
    }
}


template<class T>
void Deque<T>::pop_back() {
    if (!buckets_ || size_ == 0 || number_buckets_ == 0) return;
    if (rear_[1] == 0) {
        delete[] buckets_[number_buckets_ - 1];
        if (number_buckets_ > 1) {
            rear_[1] = kFive - 1;
            --rear_[0];
        } else {
            front_[0] = -1;
            front_[1] = 0;
            rear_[0] = -1;
            rear_[1] = 0;
        }
        --size_;
        --number_buckets_;
    } else {
        if ((rear_[0] >= front_[0])) {
            if ((rear_[0] == front_[0]) && (rear_[1] == front_[1])) {
                delete[] buckets_[front_[0]];
                front_ = {-1, 0};
                rear_ = {-1, 0};
                --size_;
                --number_buckets_;
                return;
            }
            --rear_[1];
            --size_;
        }
    }
}

template<class T>
void Deque<T>::pop_front() {
    if (!buckets_ || size_ == 0 || number_buckets_ == 0) return;
    if (front_[1] == kFive - 1) {
        if (number_buckets_ > 1) {
            front_[1] = 0;
            front_[0] = 1;
        } else {
            front_[0] = -1;
            front_[1] = 0;
            rear_[0] = -1;
            rear_[1] = 0;
        }
        --size_;
    } else {
        if ((rear_[0] >= front_[0])) {
            if ((rear_[0] == front_[0]) && (rear_[1] == front_[1])) {
                delete[] buckets_[front_[0]];
                front_ = {-1, 0};
                rear_ = {-1, 0};
                --size_;
                --number_buckets_;
                return;
            }
            ++front_[1];
            --size_;
        }
    }
}
