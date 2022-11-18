// Copyright [2022] <Alex Davis Neuwiem da Silva>

namespace structures {

template<typename T>
class DoublyCircularList {
 public:
    DoublyCircularList();
    ~DoublyCircularList();

    void clear();

    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);

    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);

    bool empty() const;
    bool contains(const T& data) const;

    T& at(std::size_t index);
    const T& at(std::size_t index) const;

    std::size_t find(const T& data) const;
    std::size_t size() const;

 private:
    class Node {
     public:
        explicit Node(const T& data) {
            data_ = data;
        }
        Node(const T& data, Node* next) {
            data_ = data;
            next_ = next;
        }
        Node(const T& data, Node* prev, Node* next) {
            data_ = data;
            prev_ = prev;
            next_ = next;
        }
        T& data() {
            return data_;
        }
        const T& data() const {
            return data_;
        }
        Node* prev() {
            return prev_;
        }
        const Node* prev() const {
            return prev_;
        }
        void prev(Node* node) {
            prev_ = node;
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
        Node* prev_{nullptr};
        Node* next_{nullptr};
    };

    Node* head{nullptr};
    Node* tail{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

//-----------------------------------------------------------------------------

template<typename T>
structures::DoublyCircularList<T>::DoublyCircularList() {
    head = nullptr;
    tail = nullptr;
    size_ = 0;
}

template<typename T>
structures::DoublyCircularList<T>::~DoublyCircularList() {
    clear();
}

template<typename T>
void structures::DoublyCircularList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
    size_ = 0;
}

template<typename T>
void structures::DoublyCircularList<T>::push_back(const T& data) {
    if (empty()) {
        return push_front(data);
    }
    Node* new_node = new Node(data);
    if (new_node == nullptr) {
        throw std::out_of_range("Allocation Error");
    }
    new_node->prev(tail);
    new_node->next(head);
    tail->next(new_node);
    tail = new_node;
    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::push_front(const T& data) {
    Node* new_node;
    new_node = new Node(data);
    if (new_node == nullptr) {
        throw std::out_of_range("Allocation Error");
    }
    new_node->prev(tail);
    new_node->next(head);
    if (empty()) {
        tail = new_node;
    } else {
        head->prev(new_node);
    }
    head = new_node;
    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::
insert(const T& data, std::size_t index) {
    if (index == 0) {
        return push_front(data);
    }
    if (index == size() - 1) {
        return push_back(data);
    }
    if (index >= size()) {
        throw std::out_of_range("Index Error");
    }
    Node* pos;
    Node* new_node = new Node(data);
    if (new_node == nullptr) {
        throw std::out_of_range("Allocation Error");
    }
    if (index < size()/2) {
        pos = head;
        for (std::size_t i = 1; i < index; i++) {
            pos = pos->next();
        }
    } else {
        pos = tail;
        for (std::size_t i = size(); i > index; i--) {
            pos = pos->prev();
        }
    }
    new_node->next(pos->next());
    new_node->prev(pos);
    new_node->next()->prev(new_node);
    pos->next(new_node);
    size_++;
}
template<typename T>
void structures::DoublyCircularList<T>::insert_sorted(const T& data) {
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
        new_node->prev(tail);
        head = new_node;
    } else if (pos1 == head) {
        pos0->next(new_node);
        new_node->next(head);
    } else {
        pos0->next(new_node);
        new_node->next(pos1);
    }
    size_++;
}

template<typename T>
T structures::DoublyCircularList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("List is Empty");
    }
    if (size() == 1 || index == 0) {
        return pop_front();
    }
    if (index == size() - 1) {
        return pop_back();
    }
    if (index >= size()) {
        throw std::out_of_range("Index Error");
    }
    Node* pos;
    if (index < size()/2) {
        pos = head;
        for (std::size_t i = 1; i < index; i++) {
            pos = pos->next();
        }
    } else {
        pos = tail;
        for (std::size_t i = size(); i > index; i--) {
            pos = pos->prev();
        }
    }
    Node* aux = pos->next();
    pos->next(aux->next());
    pos->next()->prev(pos);
    T out = aux->data();
    delete aux;
    size_--;
    return out;
}

template<typename T>
T structures::DoublyCircularList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("List is Empty");
    }
    if (size() == 1) {
        return pop_front();
    }
    Node* aux = tail;
    T out = aux->data();
    tail = aux->prev();
    tail->next(head);
    delete aux;
    size_--;
    return out;
}

template<typename T>
T structures::DoublyCircularList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("List is Empty");
    }
    T out;
    Node* aux;
    out = head->data();
    aux = head;
    if (size() == 1) {
        head = nullptr;
        tail = nullptr;
    } else {
        aux->next()->prev(tail);
        head = aux->next();
    }
    size_--;
    delete aux;
    return out;
}

template<typename T>
void structures::DoublyCircularList<T>::remove(const T& data) {
    if (empty()) {
        throw std::out_of_range("List is Empty");
    }
    std::size_t i = find(data);
    if (i != size()) {
        pop(i);
    }
}

template<typename T>
bool structures::DoublyCircularList<T>::empty() const {
    if (size() == 0) {
        return true;
    } else {
        return false;
    }
}

template<typename T>
bool structures::DoublyCircularList<T>::contains(const T& data) const {
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
T& structures::DoublyCircularList<T>::at(std::size_t index) {
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
const T& structures::DoublyCircularList<T>::at(std::size_t index) const {
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
std::size_t structures::DoublyCircularList<T>::find(const T& data) const {
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
std::size_t structures::DoublyCircularList<T>::size() const {
    return size_;
}
