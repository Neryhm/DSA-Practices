
#include <iostream>

// Linked List
struct Node {
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
public:
    LinkedList() : head(nullptr) {}
    
    // Thêm vào đầu danh sách
    void pushFront(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }
    
    // Thêm vào cuối danh sách
    void pushBack(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    
    // Xóa nút đầu danh sách
    void popFront() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    
    // Xóa nút có giá trị val (lần xuất hiện đầu tiên)
    void remove(int val) {
        if (!head) return;
        
        // Trường hợp nút đầu chính là val
        if (head->data == val) {
            popFront();
            return;
        }
        
        Node* temp = head;
        while (temp->next && temp->next->data != val) {
            temp = temp->next;
        }
        if (temp->next) {
            Node* nodeToDelete = temp->next;
            temp->next = temp->next->next;
            delete nodeToDelete;
        }
    }
    
    // Duyệt danh sách
    void printList() {
        Node* temp = head;
        while (temp) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};