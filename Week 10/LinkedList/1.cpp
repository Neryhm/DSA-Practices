#include <iostream>

struct Node {
    int data;
    Node* next;
};

class LinkedList {
private:
    Node* head;
    Node* tail;
public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    void push_back(int data) {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->next = nullptr;

        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void deleteHead() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    void deleteTail() {
        if (!head) return;
        if (head == tail) {
            delete head;
            head = tail = nullptr;
            return;
        }

        Node* temp = head;
        while (temp->next != tail) {
            temp = temp->next;
        }

        delete tail;
        tail = temp;
        tail->next = nullptr;
    }

    void deleteNode(Node* node) {
        if (!head || !node) return;

        if (node == head) {
            deleteHead();
            return;
        }

        if (node == tail) {
            deleteTail();
            return;
        }

        Node* temp = head;
        while (temp->next != node) {
            temp = temp->next;
        }

        Node* next = node->next;
        delete node;
        temp->next = next;
    }
};
