// Copyright [2022] <Alex Davis Neuwiem da Silva>
#ifndef STRUCTURES_BINARY_TREE_H
#define STRUCTURES_BINARY_TREE_H

#include "array_list.h"

namespace structures {

template<typename T>
class BinaryTree {
public:
    ~BinaryTree();

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    ArrayList<T> pre_order() const;

    ArrayList<T> in_order() const;

    ArrayList<T> post_order() const;

private:
    struct Node {
        explicit Node(const T& data) :
            data{data}
        {}

        ~Node() {
            delete left;
            delete right;
        }

        T data;
        Node* left{nullptr};
        Node* right{nullptr};

        T& min() {
            if (left == nullptr) {
                return data;
            } else {
                return left->min();
            }
        }

        void insert(const T& data_) {
            if (data_ < data) {
                if (left == nullptr) {
                    left = new Node(data_);
                    if (left == nullptr) {
                        throw std::out_of_range("Error");
                    }
                } else {
                    left->insert(data_);
                }
            } else if (data_ > data) {
                if (right == nullptr) {
                    right = new Node(data_);
                    if (right == nullptr) {
                        throw std::out_of_range("Error");
                    }
                } else {
                    right->insert(data_);
                }
            }
        }

        Node* remove(const T& data_, Node* tree) {
            if (tree == nullptr) {
                return tree;
            }
            if (data_ < tree->data) {
                tree->left = remove(data_, tree->left);
                return tree;
            }
            if (data_ > tree->data) {
                tree->right = remove(data_, tree->right);
                return tree;
            }
            if (tree->left != nullptr && tree->right != nullptr) {
                T tmp = tree->right->min();
                data = tmp;
                tree->right = remove(tmp, tree->right);
                return tree;
            }
            Node* tmp = nullptr;
            if (tree->left != nullptr) {
                tmp = tree->left;
            }
            if (tree->right != nullptr) {
                tmp = tree->right;
            }
            tree->left = nullptr;
            tree->right = nullptr;
            delete tree;
            return tmp;
        }

        bool contains(const T& data_) const;

        void pre_order(ArrayList<T>& v) const;

        void in_order(ArrayList<T>& v) const;

        void post_order(ArrayList<T>& v) const;
    };

    Node* root;
    std::size_t size_;
};

}  // namespace structures

#endif

//-----------------------------------------------------------------------------

template<typename T>
structures::BinaryTree<T>::~BinaryTree() {
    delete root;
}

template<typename T>
void structures::BinaryTree<T>::insert(const T& data) {
    if (empty()) {
        root = new Node(data);
        if (root == nullptr) {
            throw std::out_of_range("Error");
        }
    } else {
        root->insert(data);
    }
    size_++;
}

template<typename T>
void structures::BinaryTree<T>::remove(const T& data) {
    if (empty()) {
        throw std::out_of_range("Error");
    }
    if (size() > 1) {
        root->remove(data, root);
        size_--;
    } else {
        delete root;
        size_--;
    }
}

template<typename T>
bool structures::BinaryTree<T>::contains(const T& data) const {
    if (data == root->data) {
        return true;
    } else if (data < root->data) {
        return root->left->contains(data);
    } else if (data > root->data) {
        return root->right->contains(data);
    }
    return false;
}

template<typename T>
bool structures::BinaryTree<T>::empty() const {
    if (size_ == 0) {
        return true;
    }
    return false;
}

template<typename T>
std::size_t structures::BinaryTree<T>::size() const {
    return size_;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::pre_order() const {
    ArrayList<T> v{size()};
    if (!empty()) {
        root->pre_order(v);
    }
    return v;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::in_order() const {
    ArrayList<T> v{size()};
    if (!empty()) {
        root->in_order(v);
    }
    return v;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::post_order() const {
    ArrayList<T> v{size()};
    if (!empty()) {
        root->post_order(v);
    }
    return v;
}

template<typename T>
bool structures::BinaryTree<T>::Node::contains(const T& data_) const {
    if (data_ == data) {
        return true;
    } else if (data_ < data) {
        if (left == nullptr) {
            return false;
        }
        return left->contains(data_);
    } else if (data_ > data) {
        if (right == nullptr) {
            return false;
        }
        return right->contains(data_);
    }
    return false;
}

template<typename T>
void structures::BinaryTree<T>::Node::pre_order(ArrayList<T>& v) const {
    v.push_back(data);
    if (left != nullptr) {
        left->pre_order(v);
    }
    if (right != nullptr) {
        right->pre_order(v);
    }
}

template<typename T>
void structures::BinaryTree<T>::Node::in_order(ArrayList<T>& v) const {
    if (left != nullptr) {
        left->in_order(v);
    }
    v.push_back(data);
    if (right != nullptr) {
        right->in_order(v);
    }
}

template<typename T>
void structures::BinaryTree<T>::Node::post_order(ArrayList<T>& v) const {
    if (left != nullptr) {
        left->post_order(v);
    }
    if (right != nullptr) {
        right->post_order(v);
    }
    v.push_back(data);
}
