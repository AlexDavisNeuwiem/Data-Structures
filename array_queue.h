// Copyright [2022] <Alex Davis Neuwiem da Silva>
#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
class ArrayQueue {
 public:
    ArrayQueue();
    explicit ArrayQueue(std::size_t max);
    ~ArrayQueue();
    void enqueue(const T& data);
    T dequeue();
    T& back();
    void clear();
    std::size_t size();
    std::size_t max_size();
    bool empty();
    bool full();

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
    int begin_;
    int end_;
    static const auto DEFAULT_SIZE = 10u;
};

}  // namespace structures

#endif

//-----------------------------------------------------------------------------

template<typename T>
structures::ArrayQueue<T>::ArrayQueue() {
    contents = new T[DEFAULT_SIZE];
    max_size_ = DEFAULT_SIZE;
    begin_ = 0;
    end_ = -1;
    size_ = 0;
}

template<typename T>
structures::ArrayQueue<T>::ArrayQueue(std::size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    begin_ = 0;
    end_ = -1;
    size_ = 0;
}

template<typename T>
structures::ArrayQueue<T>::~ArrayQueue() {
    delete [] contents;
}

template<typename T>
void structures::ArrayQueue<T>::enqueue(const T& data) {
    if (full()) {
        throw std::out_of_range("Queue is Full");
    }
    end_ = (end_ + 1) % max_size_;
    size_++;
    contents[end_] = data;
}

template<typename T>
T structures::ArrayQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("Queue is Empty");
    }
    T aux;
    aux = contents[begin_];
    begin_ = (begin_ + 1) % max_size_;
    size_--;
    return aux;
}

template<typename T>
T& structures::ArrayQueue<T>::back() {
    if (empty()) {
        throw std::out_of_range("Queue is Empty");
    }
    return contents[end_];
}

template<typename T>
void structures::ArrayQueue<T>::clear() {
    begin_ = 0;
    end_ = -1;
    size_ = 0;
}

template<typename T>
std::size_t structures::ArrayQueue<T>::size() {
    return size_;
}

template<typename T>
std::size_t structures::ArrayQueue<T>::max_size() {
    return max_size_;
}

template<typename T>
bool structures::ArrayQueue<T>::empty() {
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }
}

template<typename T>
bool structures::ArrayQueue<T>::full() {
    if (size_ == max_size_) {
        return true;
    } else {
        return false;
    }
}
