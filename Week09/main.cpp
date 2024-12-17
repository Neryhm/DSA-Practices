#include <iostream>

struct Node {
    double coefficient;
    int exponent;
    Node* next;
};

// Hàm thêm một nút vào danh sách liên kết
void addNode(Node*& head, double coeff, int exp) {
    Node* newNode = new Node;
    newNode->coefficient = coeff;
    newNode->exponent = exp;
    newNode->next = head;
    head = newNode;
}

// Hàm nhập đa thức từ người dùng
Node* inputPolynomial() {
    Node* head = nullptr;
    int n;
    std::cout << "Nhap so luong hang tu cua da thuc: ";
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        double coeff;
        int exp;
        std::cout << "Nhap he so va so mu cua hang tu thu " << i + 1 << ": ";
        std::cin >> coeff >> exp;
        addNode(head, coeff, exp);
    }
    return head;
}

// Hàm in đa thức
void printPolynomial(Node* head, const std::string& name) {
    std::cout << name << "(x) = ";
    while (head) {
        if (head->coefficient != 0) {
            if (head->exponent == 0) {
                std::cout << head->coefficient;
            } else {
                std::cout << head->coefficient << "x^" << head->exponent;
            }
            if (head->next && head->next->coefficient > 0) {
                std::cout << " + ";
            } else if (head->next) {
                std::cout << " ";
            }
        }
        head = head->next;
    }
    std::cout << std::endl;
}

// Hàm cộng hai đa thức
Node* addPolynomials(Node* poly1, Node* poly2) {
    Node* result = nullptr;
    while (poly1 && poly2) {
        if (poly1->exponent > poly2->exponent) {
            addNode(result, poly1->coefficient, poly1->exponent);
            poly1 = poly1->next;
        } else if (poly1->exponent < poly2->exponent) {
            addNode(result, poly2->coefficient, poly2->exponent);
            poly2 = poly2->next;
        } else {
            double sum = poly1->coefficient + poly2->coefficient;
            if (sum != 0) {
                addNode(result, sum, poly1->exponent);
            }
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }
    while (poly1) {
        addNode(result, poly1->coefficient, poly1->exponent);
        poly1 = poly1->next;
    }
    while (poly2) {
        addNode(result, poly2->coefficient, poly2->exponent);
        poly2 = poly2->next;
    }
    return result;
}

// Hàm giải phóng bộ nhớ của danh sách liên kết
void freeList(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Node* poly1 = inputPolynomial();
    Node* poly2 = inputPolynomial();

    printPolynomial(poly1, "f");
    printPolynomial(poly2, "g");

    Node* polySum = addPolynomials(poly1, poly2);
    printPolynomial(polySum, "h");

    // Giải phóng bộ nhớ
    freeList(poly1);
    freeList(poly2);
    freeList(polySum);

    return 0;
}