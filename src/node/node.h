#pragma once

#include <iostream>

template<class T>
class Node {
private:
    T data;
    Node<T>* left;
    Node<T>* right;

public:
    Node(const T& data, Node<T>* left = nullptr, Node<T>* right = nullptr);
    ~Node();

    T getData() const;
    void setData(const T& data);

    Node<T>* getLeft() const;
    Node<T>* getRight() const;
    Node<T>* getChild(int child) const;

    void setLeft(Node<T>* left);
    void setRight(Node<T>* right);

    void print() const;
};

template<class T>
Node<T>::Node(const T& data, Node<T>* left, Node<T>* right)
    : data(data), left(left), right(right) {
}

template<class T>
Node<T>::~Node() {
    left = nullptr;
    right = nullptr;
}

template<class T>
T Node<T>::getData() const {
    return data;
}

template<class T>
void Node<T>::setData(const T& newData) {
    data = newData;
}

template<class T>
Node<T>* Node<T>::getLeft() const {
    return left;
}

template<class T>
Node<T>* Node<T>::getRight() const {
    return right;
}

template<class T>
Node<T>* Node<T>::getChild(int child) const {
    return child == 0 ? left : right;
}

template<class T>
void Node<T>::setLeft(Node<T>* newLeft) {
    left = newLeft;
}

template<class T>
void Node<T>::setRight(Node<T>* newRight) {
    right = newRight;
}

template<class T>
void Node<T>::print() const {
    std::cout << "Data: " << data << std::endl;
    std::cout << "Left: " << left << std::endl;
    std::cout << "Right: " << right << std::endl;
}