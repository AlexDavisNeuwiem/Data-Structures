// Copyright [2022] <Alex Davis Neuwiem da Silva>
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>

namespace structures {

template<typename T>
class ArrayList {
 public:
    ArrayList();
    explicit ArrayList(std::size_t max_size);
    ~ArrayList();

    void clear();
    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool full() const;
    bool empty() const;
    bool contains(const T& data) const;
    std::size_t find(const T& data) const;
    std::size_t size() const;
    std::size_t max_size() const;
    T& at(std::size_t index);
    T& operator[](std::size_t index);
    const T& at(std::size_t index) const;
    const T& operator[](std::size_t index) const;
    // descricao do 'operator []' na FAQ da disciplina

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};

}  // namespace structures

#endif

//-----------------------------------------------------------------------------

template<typename T>
structures::ArrayList<T>::ArrayList() {
    size_ = 0;
    max_size_ = DEFAULT_MAX;
    contents = new T[DEFAULT_MAX];
}

template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size) {
    size_ = 0;
    max_size_ = max_size;
    contents = new T[max_size_];
}

template<typename T>
structures::ArrayList<T>::~ArrayList() {
    delete [] contents;
}

template<typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    if (full()) {
        throw std::out_of_range("List is Full");
    }
    size_ = size_ + 1;
    contents[size_ - 1] = data;
}

template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    if (full()) {
        throw std::out_of_range("List is Full");
    }
    for (int i = size_; i >=  1; i--) {
        contents[i] = contents[i - 1];
    }
    size_ = size_ + 1;
    contents[0] = data;
}

template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (full()) {
        throw std::out_of_range("List is Full");
    } else if (index >= size_ || index < 0) {
        throw std::out_of_range("Index Error");
    }
    for (std::size_t i = size_; i >= index + 1 ; i--) {
        contents[i] = contents[i - 1];
    }
    size_ = size_ + 1;
    contents[index] = data;
}

template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    if (full()) {
        throw std::out_of_range("List is Full");
    }
    std::size_t i = 0;
    while (i < size_ && contents[i] < data) {
        i++;
    }
    if (i == size_) {
        contents[size_] = data;
    } else {
        for (std::size_t j = size_; j >= i + 1; j --) {
            contents[j] = contents[j - 1];
        }
        contents[i] = data;
    }
    size_ = size_ + 1;
}

template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("List is Empty");
    } else if (index >= size_ || index < 0) {
        throw std::out_of_range("Index Error");
    }
    T temp;
    for (std::size_t i = index; i < size_ - 1 ; i++) {
        if (i == index) {
            temp = contents[index];
        }
        contents[i] = contents[i + 1];
    }
    size_ = size_ - 1;
    return temp;
}

template<typename T>
T structures::ArrayList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("List is Empty");
    }
    size_ = size_ - 1;
    return contents[size_];
}

template<typename T>
T structures::ArrayList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("List is Empty");
    }
    T temp = contents[0];
    for (std::size_t i = 0; i < size_ - 1; i++) {
        contents[i] = contents[i + 1];
    }
    size_ = size_ - 1;
    return temp;
}

template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
    for (std::size_t i = 0; i < size_; i++) {
        if (contents[i] == data) {
            pop(i);
            break;
        }
    }
}

template<typename T>
bool structures:: ArrayList<T>::full() const {
    if (size_ == max_size_) {
        return true;
    } else {
        return false;
    }
}

template<typename T>
bool structures:: ArrayList<T>::empty() const {
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }
}

template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    for (std::size_t i = 0 ; i < size_; i++) {
        if (contents[i] == data) {
            return true;
        }
    }
    return false;
}

template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    for (std::size_t i = 0; i < size_; i++) {
        if (contents[i] == data) {
            return i;
        }
    }
    return size_;
}

template<typename T>
std::size_t structures::ArrayList<T>::size() const {
    return size_;
}

template<typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}

template<typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
    if (index >= size_ || index < 0) {
        throw std::out_of_range("Index Error");
    }
    return contents[index];
}

template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
    if (index >= size || index < 0) {
        throw std::out_of_range("Index Error");
    }
    return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
    return contents[index];
}
