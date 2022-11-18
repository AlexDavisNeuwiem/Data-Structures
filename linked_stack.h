// Copyright [2022] <Alex Davis Neuwiem da Silva>

namespace structures {

template<typename T>
class LinkedStack {
 public:
    LinkedStack();

    ~LinkedStack();

    void clear();

    void push(const T& data);

    T pop();

    T& top() const;

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
        void next(Node* next) {
            next_ = next;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* top_;
    std::size_t size_;
};

}  // namespace structures

//-----------------------------------------------------------------------------

template<typename T>
structures::LinkedStack<T>::LinkedStack() {
    top_ = nullptr;
    size_ = 0;
}

template<typename T>
structures::LinkedStack<T>::~LinkedStack() {
    clear();
}

template<typename T>
void structures::LinkedStack<T>::clear() {
    while (!empty()) {
        pop();
    }
    top_ = nullptr;
    size_ = 0;
}

template<typename T>
void structures::LinkedStack<T>::push(const T& data) {
    Node* new_node = new Node(data);
    if (new_node == nullptr) {
        throw std::out_of_range("Allocation Error");
    }
    new_node->next(top_);
    top_ = new_node;
    size_++;
}

template<typename T>
T structures::LinkedStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("Stack is Empty");
    }
    T out = top_->data();
    if (size() == 1) {
        top_ = nullptr;
    } else {
        top_ = top_->next();
    }
    size_--;
    return out;
}

template<typename T>
T& structures::LinkedStack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("Stack is Empty");
    }
    return top_->data();
}

template<typename T>
bool structures::LinkedStack<T>::empty() const {
    if (size() == 0) {
        return true;
    } else {
        return false;
    }
}

template<typename T>
std::size_t structures::LinkedStack<T>::size() const {
    return size_;
}
