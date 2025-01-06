#include <iostream>

struct Node {
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {}
};

class Stack {
private:
    Node* topNode;  // Con trỏ tới node đỉnh của stack
    
public:
    Stack() : topNode(nullptr) {}

    // Kiểm tra stack rỗng
    bool isEmpty() {
        return (topNode == nullptr);
    }

    // Thêm phần tử vào đỉnh stack
    void push(int val) {
        Node* newNode = new Node(val);
        newNode->next = topNode; // trỏ next của node mới về node đỉnh cũ
        topNode = newNode;       // cập nhật đỉnh stack
    }

    // Xóa phần tử đỉnh
    void pop() {
        if (isEmpty()) {
            std::cout << "Stack underflow\n";
            return;
        }
        Node* temp = topNode;
        topNode = topNode->next; // dời đỉnh sang node kế tiếp
        delete temp;
    }

    // Lấy giá trị phần tử đỉnh
    int top() {
        if (isEmpty()) {
            std::cout << "Stack is empty\n";
            return -1; // hoặc throw exception
        }
        return topNode->data;
    }

    // Hàm hủy để giải phóng bộ nhớ còn lại (nếu có)
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
};