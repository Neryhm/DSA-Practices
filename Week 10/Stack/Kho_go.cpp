#include <iostream>

struct Log {
    std::string type;
    int size;
    int age;
};

struct Stack {
    Log* data;
    int top;
    int capacity;
    Stack(int capacity) : capacity(capacity) {
        data = new Log[capacity];
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
    void push(const Log& log) {
        if (isFull()) {
            std::cerr << "Stack is full!" << std::endl;
            return;
        }
        data[++top] = log;
    }
    Log pop() {
        if (isEmpty()) {
            std::cerr << "Stack is empty!" << std::endl;
            return Log();
        }
        return data[top--];
    }
    void countByAge() {
        int ages[100] = {0};
        for (int i = 0; i <= top; ++i) {
            ++ages[data[i].age];
        }
        for (int i = 0; i < 100; ++i) {
            if (ages[i] > 0) {
                std::cout << i << " years: " << ages[i] << " logs" << std::endl;
            }
        }
    }
};

int main() {
    Stack stack(10);
    stack.push({"Oak", 10, 7});
    stack.push({"Spruce", 40, 12});
    stack.push({"Birch", 20, 5});
    stack.push({"Acacia", 70, 9});
    stack.push({"Cedar", 50, 5});
    stack.push({"Ebony", 50, 5});
    stack.push({"Birch", 50, 12});
    stack.push({"Rosewood", 50, 3});

    stack.countByAge();

    return 0;
}


