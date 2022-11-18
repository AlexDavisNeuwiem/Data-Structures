// Copyright [2022] <Alex Davis Neuwiem da Silva>

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
class LinkedList {
 public:
    LinkedList();
    ~LinkedList();
    void clear();
    void push_back(const T& data);
    void push_front(const T& data); 
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);
    T& at(std::size_t index);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool empty() const;
    bool contains(const T& data) const;
    std::size_t find(const T& data) const;
    std::size_t size() const;
    void invert();
    LinkedList<T> clone();
    LinkedList<T> slicing(int start, int stop, int step);
    void append(structures::LinkedList<T> &list_add);
    LinkedList< LinkedList<T> * > halve();

 private:
    class Node {
     public:
        explicit Node(const T& data):
        data_{data}
        {}

        explicit Node(const T& data, Node* next):
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

    Node* before_index(std::size_t index) {
        auto it = head;
        for (auto i = 1u; i < index; ++i) {
            it = it->next();
        }
        return it;
    }

    void insert(const T& data, Node* before);

    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures


//*******************************************************************

template<typename T>
void structures::LinkedList<T>::invert() {
    LinkedList<T> list_aux;
    Node* pos = head;
    for (std::size_t i = 0; i < size(); i++) {
        std::size_t j = size() - 1 - i;
        list_aux.insert(at(j), i);
    }
    for (std::size_t i = 0; i < size(); i++) {
        pos->data() = list_aux.at(i);
        pos = pos->next();
    }
}

template<typename T>
structures::LinkedList<T> structures::LinkedList<T>::clone() {  // OK
    LinkedList<T> list_clone;
    Node* pos = head;
    for (std::size_t i = 0; i < size(); i++) {
        list_clone.push_back(pos->data());
        pos = pos->next();
    }
    return list_clone;
}

template<typename T>
structures::LinkedList<T> structures::LinkedList<T>::slicing(int start,
                                                             int stop,
                                                             int step) {
    LinkedList<T> list_slice;
    Node*pos = head;
    for (int i = 0; i < start; i++) {
        pos = pos->next();
    }
    for (int i = start; i <= stop; ) {
        list_slice.push_back(pos->data());
        for (int j = 0; j < step; j++) {
            pos = pos->next();
        }
        i = i + step;
    }
    return list_slice;
}

template<typename T>
void structures::LinkedList<T>::append(structures::LinkedList<T> &list_add) {
    Node* pos = head;
    for (std::size_t i = 0; i < list_add.size(); i++) {
        push_back(list_add.at(i));
        pos = pos->next();
    }
}

template<typename T>
structures::LinkedList< structures::LinkedList<T> * >
                                           structures::LinkedList<T>::halve() {
    LinkedList< LinkedList<T> * > list_halve;
    Node* pos = head;
    LinkedList<T>* list_even = new LinkedList<T>;
    LinkedList<T>* list_odd = new LinkedList<T>;
    for (std::size_t i = 0; i < size(); i++) {
        if (i % 2 == 0) {
            list_even->push_back(pos->data());
        } else {
            list_odd->push_back(pos->data());
        }
        pos = pos->next();
    }
    list_halve.push_back(list_even);
    list_halve.push_back(list_odd);
    return list_halve;
}

//*******************************************************************


template<typename T>
structures::LinkedList<T>::LinkedList() {}

template<typename T>
structures::LinkedList<T>::~LinkedList() {
    clear();
}

template<typename T>
void structures::LinkedList<T>::clear() {
    while (!empty())
        pop_front();
}

template<typename T>
void structures::LinkedList<T>::push_back(const T& data) {
    insert(data, size_);
}

template<typename T>
void structures::LinkedList<T>::push_front(const T& data) {
    Node* new_node = new Node(data);
    if (new_node == nullptr)
        throw std::out_of_range("Full list!");

    new_node->next(head);
    head = new_node;
    size_++;
}

template<typename T>
void structures::LinkedList<T>::insert(const T& data, std::size_t index) {
    if (index > size_)
        throw std::out_of_range("Invalid index!");

    if (index == 0) {
        push_front(data);
    } else {
        Node* new_node = new Node(data);
        if (new_node == nullptr)
            throw std::out_of_range("Full list!");

        Node* before = before_index(index);
        Node* next = before->next();
        new_node->next(next);
        before->next(new_node);
        size_++;
    }
}

template<typename T>
void structures::LinkedList<T>::insert(const T& data, Node* before) {
    Node* new_node = new Node(data);
    if (new_node == nullptr)
        throw std::out_of_range("Full list!");

    new_node->next(before->next());
    before->next(new_node);
    size_++;
}

template<typename T>
void structures::LinkedList<T>::insert_sorted(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        Node* current = head;
        Node* before = head;
        std::size_t position = size();
        for (auto i = 0u; i < size(); ++i) {
            if (!(data > current->data())) {
                position = i;
                break;
            }
            before = current;
            current = current->next();
        }
        position == 0? push_front(data) : insert(data, before);
    }
}

template<typename T>
T& structures::LinkedList<T>::at(std::size_t index) {
    if (index >= size())
        throw std::out_of_range("Invalid index or empty list!");

    Node* current = index == 0? head : before_index(index)->next();
    return current->data();
}

template<typename T>
T structures::LinkedList<T>::pop(std::size_t index) {
    if (empty())
        throw std::out_of_range("Empty list");
    if (index >= size())
        throw std::out_of_range("Invalid index!");

    if (index == 0)
        return pop_front();

    Node* before_out = before_index(index);
    Node* out = before_out->next();
    T data = out->data();
    before_out->next(out->next());
    size_--;
    delete out;
    return data;
}

template<typename T>
T structures::LinkedList<T>::pop_back() {
    return pop(size_ - 1u);
}

template<typename T>
T structures::LinkedList<T>::pop_front() {
    if (empty())
        throw std::out_of_range("Empty list!");

    auto out = head;
    T data = out->data();
    head = out->next();
    size_--;
    delete out;
    return data;
}

template<typename T>
void structures::LinkedList<T>::remove(const T& data) {
    pop(find(data));
}

template<typename T>
bool structures::LinkedList<T>::empty() const {
    return size() == 0u;
}

template<typename T>
bool structures::LinkedList<T>::contains(const T& data) const {
    return find(data) != size();
}

template<typename T>
std::size_t structures::LinkedList<T>::find(const T& data) const {
    std::size_t index = 0u;
    Node* current = head;
    while (index < size()) {
        if (current->data() == data)
            break;
        current = current->next();
        index++;
    }
    return index;
}

template<typename T>
std::size_t structures::LinkedList<T>::size() const {
    return size_;
}
