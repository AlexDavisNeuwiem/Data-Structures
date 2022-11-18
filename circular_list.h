// Copyright [2022] <Alex Davis Neuwiem da Silva>

#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>

namespace structures {

template<typename T>
class CircularList {
 public:
    CircularList();
    ~CircularList();

    void clear();

    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);

    T& at(std::size_t index);
    const T& at(std::size_t index) const;

    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);

    bool empty() const;
    bool contains(const T& data) const;
    std::size_t find(const T& data) const;

    std::size_t size() const;

 private:
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
        }

        Node* next() {
            return next_;
        }

        const Node* next() const {
            return next_;
        }

        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* end() {
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif

//-----------------------------------------------------------------------------

template<typename T>
structures::CircularList<T>::CircularList() {
    head = nullptr;
    size_ = 0;
}

template<typename T>
structures::CircularList<T>::~CircularList() {
    clear();
}

template<typename T>
void structures::CircularList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
    head = nullptr;
    size_ = 0;
}

template<typename T>
void structures::CircularList<T>::push_back(const T& data) {
    Node* pos = head;
    Node* new_node = new Node(data);
    if (new_node == nullptr) {
        throw std::out_of_range("Allocation Error");
    }
    if (size() == 0) {
        return push_front(data);
    }
    for (std::size_t i = 1; i < size(); i++) {
        pos = pos->next();
    }
    new_node->next(head);
    pos->next(new_node);
    size_++;
}

template<typename T>
void structures::CircularList<T>::push_front(const T& data) {
    Node* new_node = new Node(data);
    if (new_node == nullptr) {
        throw std::out_of_range("Allocation Error");
    }
    new_node->next(head);
    head = new_node;
    size_++;
}

template<typename T>
void structures::CircularList<T>::insert(const T& data, std::size_t index) {
    if (index == 0) {
        return push_front(data);
    }
    if (index == size() - 1) {
        return push_back(data);
    }
    if (index >= size() || index < 0) {
        throw std::out_of_range("Index Error");
    }
    Node* pos = head;
    Node* new_node = new Node(data);
    if (new_node == nullptr) {
        throw std::out_of_range("Allocation Error");
    }
    for (std::size_t i = 1; i < index; i++) {
        pos = pos->next();
    }
    new_node->next(pos->next());
    pos->next(new_node);
    size_++;
}

template<typename T>
void structures::CircularList<T>::insert_sorted(const T& data) {
    Node* pos0 = nullptr;
    Node* pos1 = head;
    Node* new_node = new Node(data);
    if (new_node == nullptr) {
        throw std::out_of_range("Allocation Error");
    }
    for (std::size_t i = 0; i < size(); i++) {
        if (pos1->data() > data) {
            break;
        }
        pos0 = pos1;
        pos1 = pos1->next();
    }
    if (!pos0) {
        new_node->next(head);
        head = new_node;
    } else if (pos1 == nullptr) {
        pos0->next(new_node);
        new_node->next(nullptr);
    } else {
        pos0->next(new_node);
        new_node->next(pos1);
    }
    size_++;
}

template<typename T>
T& structures::CircularList<T>::at(std::size_t index) {
    if (index >= size() || index < 0) {
        throw std::out_of_range("Index Error");
    }
    Node* pos = head;
    for (std::size_t i = 0; i < index; i++) {
        pos = pos->next();
    }
    return pos->data();
}

template<typename T>
T structures::CircularList<T>::pop(std::size_t index) {
    if (empty() || index >= size()) {
        throw std::out_of_range("List is Empty");
    }
    if (size() == 1 || index == 0) {
        return pop_front();
    }
    if (index == size() - 1) {
        return pop_back();
    }
    T out;
    Node* pos0;
    Node* pos1 = head;
    for (std::size_t i = 0; i < index; i++) {
        pos0 = pos1;
        pos1 = pos1->next();
    }
    out = pos1->data();
    pos0->next(pos1->next());
    size_--;
    delete pos1;
    return out;
}

template<typename T>
T structures::CircularList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("List is Empty");
    }
    if (size() == 1) {
        return pop_front();
    }
    T out;
    Node* pos0 = nullptr;
    Node* pos1 = head;
    for (std::size_t i = 1; i < size(); i++) {
        pos0 = pos1;
        pos1 = pos1->next();
    }
    out = pos1->data();
    pos0->next(head);
    size_--;
    delete pos1;
    return out;
}

template<typename T>
T structures::CircularList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("List is Empty");
    }
    T out = head->data();
    if (size() == 1) {
        head = nullptr;
    } else {
        head = head->next();
    }
    size_--;
    return out;
}

template<typename T>
void structures::CircularList<T>::remove(const T& data) {
    if (empty()) {
        throw std::out_of_range("List is Empty");
    }
    std::size_t i = find(data);
    if (i != size()) {
        pop(i);
    }
}

template<typename T>
bool structures::CircularList<T>::empty() const {
    if (size() == 0) {
        return true;
    } else {
        return false;
    }
}

template<typename T>
bool structures::CircularList<T>::contains(const T& data) const {
    if (empty()) {
        throw std::out_of_range("List is Empty");
    }
    Node* pos = head;
    for (std::size_t i = 0; i < size(); i++) {
        if (pos->data() == data) {
            return true;
        }
        pos = pos->next();
    }
    return false;
}

template<typename T>
std::size_t structures::CircularList<T>::find(const T& data) const {
    if (empty()) {
        throw std::out_of_range("List is Empty");
    }
    Node* pos = head;
    for (std::size_t i = 0; i < size(); i++) {
        if (pos->data() == data) {
            return i;
        }
        pos = pos->next();
    }
    return size_;
}

template<typename T>
std::size_t structures::CircularList<T>::size() const {
    return size_;
}
