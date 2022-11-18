// Copyright [2022] <Alex Davis Neuwiem da Silva>

namespace structures {


template<typename T>
class LinkedQueue {
 public:
    LinkedQueue();

    ~LinkedQueue();

    void clear();

    void enqueue(const T& data);

    T dequeue();

    T& front() const;

    T& back() const;

    bool empty() const;

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
structures::LinkedQueue<T>::LinkedQueue() {
    head = nullptr;
    tail = nullptr;
    size_ = 0;
}

template<typename T>
structures::LinkedQueue<T>::~LinkedQueue() {
    clear();
}

template<typename T>
void structures::LinkedQueue<T>::clear() {
    while (!empty()) {
        dequeue();
    }
    size_ = 0;
}

template<typename T>
void structures::LinkedQueue<T>::enqueue(const T& data) {
    Node* new_node = new Node(data);
    if (!empty()) {
        tail -> next(new_node);
    } else {
        head = new_node;
    }
    tail = new_node;
    size_++;
}

template<typename T>
T structures::LinkedQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("Queue is Empty");
    }
    T out;
    Node* aux;
    out = head->data();
    aux = head;
    if (size() == 1) {
        head = nullptr;
        tail = nullptr;
    } else {
        aux->next()->prev(nullptr);
        head = aux->next();
    }
    size_--;
    delete aux;
    return out;
}

template<typename T>
T& structures::LinkedQueue<T>::front() const {
    if (empty()) {
        throw std::out_of_range("Queue is Empty");
    }
    return head->data();
}

template<typename T>
T& structures::LinkedQueue<T>::back() const {
    if (empty()) {
        throw std::out_of_range("Queue is Empty");
    }
    return tail->data();
}

template<typename T>
bool structures::LinkedQueue<T>::empty() const {
    if (size() == 0) {
        return true;
    } else {
        return false;
    }
}

template<typename T>
std::size_t structures::LinkedQueue<T>::size() const {
    return size_;
}
