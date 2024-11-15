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

    Node* getHead() {
        return head;
    }

    void printList() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    LinkedList list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    list.printList();

    list.deleteHead(); std:: cout << "Delete Head: ";
    list.printList();

    list.deleteTail(); std:: cout << "Delete Tail: ";
    list.printList();

    Node* node = list.getHead();
    while (node->next) {
        node = node->next;
    }
    list.deleteNode(node); std:: cout << "Delete Node After Second Node: ";
    list.printList();

    return 0;
}

