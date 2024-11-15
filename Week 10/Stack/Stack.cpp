#include <iostream>

// Using basic sequential structure
template <typename T>
class Stack {
    T* data;
    int top;
    int capacity;

public:
    Stack(int capacity) : capacity(capacity) {
        data = new T[capacity];
        top = -1;
    }

    ~Stack() {
        delete[] data;
    }

    bool isEmpty() const {
        return top == -1;
    }

    bool isFull() const {
        return top == capacity - 1;
    }

    void push(const T& element) {
        if (isFull()) {
            std::cerr << "Stack is full!" << std::endl;
            return;
        }
        data[++top] = element;
    }

    T pop() {
        if (isEmpty()) {
            std::cerr << "Stack is empty!" << std::endl;
            return T();
        }
        return data[top--];
    }
};

// Using linked list
template <typename T>
class Stack_Linkedlist {
    struct Node {
        T data;
        Node* next;

        Node(const T& d) : data(d), next(nullptr) {}
    };

    Node* topNode;

public:
    Stack_Linkedlist() : topNode(nullptr) {}

    ~Stack_Linkedlist() {
        while (topNode) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }

    void push(const T& element) {
        Node* newNode = new Node(element);
        newNode->next = topNode;
        topNode = newNode;
    }

    T pop() {
        if (isEmpty()) {
            std::cerr << "Stack is empty!" << std::endl;
            return T();
        }
        Node* temp = topNode;
        T data = temp->data;
        topNode = topNode->next;
        delete temp;
        return data;
    }
};
