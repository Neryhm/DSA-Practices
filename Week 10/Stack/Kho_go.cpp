#include <iostream>

struct Log {
    int size;
    int age;
};

struct Stack {
    std::string type;
    Log* data;
    int top;
    int capacity;
    Stack(std::string type, int capacity) : type(type), capacity(capacity) {
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
    void countByAge() const {
        int ages[100] = {0};
        for (int i = 0; i <= top; ++i) {
            ++ages[data[i].age];
        }
        std::cout << type << ": \n";
        for (int i = 0; i < 100; ++i) {
            if (ages[i] > 0) {
                std::cout << i << " years: " << ages[i] << std::endl;
            }
        }
        std::cout << std::endl;
    }
};

int main() {
    Stack oakStack("Oak", 10);
    oakStack.push({10, 7});
    oakStack.push({20, 12});
    oakStack.push({30, 5});

    Stack spruceStack("Spruce", 10);
    spruceStack.push({40, 12});
    spruceStack.push({37, 5});
    spruceStack.push({14, 7});
    spruceStack.push({25, 7});
    spruceStack.push({56, 5});

    oakStack.countByAge();
    spruceStack.countByAge();

    return 0;
}