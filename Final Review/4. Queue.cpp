#include <iostream>

struct QNode {
    int data;
    QNode* next;
    
    QNode(int val) : data(val), next(nullptr) {}
};

class Queue {
private:
    QNode* frontNode;  // con trỏ tới phần tử đầu
    QNode* rearNode;   // con trỏ tới phần tử cuối

public:
    Queue() : frontNode(nullptr), rearNode(nullptr) {}

    // Kiểm tra queue rỗng
    bool isEmpty() {
        return (frontNode == nullptr);
    }

    // Thêm phần tử vào cuối queue
    void enqueue(int val) {
        QNode* newNode = new QNode(val);
        if (isEmpty()) {
            frontNode = rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
    }

    // Xóa phần tử đầu queue
    void dequeue() {
        if (isEmpty()) {
            std::cout << "Queue underflow\n";
            return;
        }
        QNode* temp = frontNode;
        frontNode = frontNode->next;
        // Nếu queue trở nên rỗng, cập nhật rearNode
        if (frontNode == nullptr) {
            rearNode = nullptr;
        }
        delete temp;
    }

    // Lấy giá trị phần tử đầu
    int front() {
        if (isEmpty()) {
            std::cout << "Queue is empty\n";
            return -1; // hoặc throw exception
        }
        return frontNode->data;
    }

    // Hàm hủy để giải phóng bộ nhớ còn lại (nếu có)
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};
