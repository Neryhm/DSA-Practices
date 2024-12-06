#include <iostream>

struct Node {
    //không biết phải dùng char để biểu diễn 0.5 như thế nào nên e dùng string
    std::string value;
    Node* left;
    Node* right;
    
    Node(std::string val) : value(val), left(nullptr), right(nullptr) {}
};

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

Node* buildTree(std::string expr) {
    std::string newExpr;
    for (char c : expr) {
        if (c != ' ') {
            newExpr += c;
        }
    }
    expr = newExpr;
    // Dùng Stack
    Node* operandStack[100];
    char operatorStack[100];
    int operandTop = -1;
    int operatorTop = -1;

    for (int i = 0; i < expr.length(); i++) {
        // số thập phân thì lấy full
        if ((expr[i] >= '0' && expr[i] <= '9') || expr[i] == '.') {
            std::string number;
            bool hasDecimal = false;
            
            while (i < expr.length() && 
                   ((expr[i] >= '0' && expr[i] <= '9') || expr[i] == '.')) {
                if (expr[i] == '.') {
                    if (hasDecimal) break;
                    hasDecimal = true;
                }
                number += expr[i];
                i++;
            }
            i--;
            
            operandStack[++operandTop] = new Node(number);
        }
        else if ((expr[i] >= 'a' && expr[i] <= 'z')) {
            std::string operand;
            while (i < expr.length() && 
                   (expr[i] >= 'a' && expr[i] <= 'z')) {
                operand += expr[i];
                i++;
            }
            i--;
            
            operandStack[++operandTop] = new Node(operand);
        }
        else if (expr[i] == '(') {
            operatorStack[++operatorTop] = expr[i];
        }
        else if (expr[i] == ')') {
            while (operatorTop >= 0 && operatorStack[operatorTop] != '(') {
                char op = operatorStack[operatorTop--];
                
                Node* right = operandStack[operandTop--];
                Node* left = operandStack[operandTop--];
                
                Node* newNode = new Node(std::string(1, op));
                newNode->left = left;
                newNode->right = right;
                
                operandStack[++operandTop] = newNode;
            }
            if (operatorTop >= 0 && operatorStack[operatorTop] == '(')
                operatorTop--;
        }
        else if (expr[i] == '+' || expr[i] == '-' || 
                 expr[i] == '*' || expr[i] == '/' || expr[i] == '^') {
            while (operatorTop >= 0 && 
                   operatorStack[operatorTop] != '(' && 
                   precedence(operatorStack[operatorTop]) >= precedence(expr[i])) {
                char op = operatorStack[operatorTop--];
                
                Node* right = operandStack[operandTop--];
                Node* left = operandStack[operandTop--];
                
                Node* newNode = new Node(std::string(1, op));
                newNode->left = left;
                newNode->right = right;
                
                operandStack[++operandTop] = newNode;
            }
            
            operatorStack[++operatorTop] = expr[i];
        }
    }
    
    while (operatorTop >= 0) {
        char op = operatorStack[operatorTop--];
        
        Node* right = operandStack[operandTop--];
        Node* left = operandStack[operandTop--];
        
        Node* newNode = new Node(std::string(1, op));
        newNode->left = left;
        newNode->right = right;
        
        operandStack[++operandTop] = newNode;
    }
    
    return operandStack[0];
}

void preOrder(Node* root) {
    if (root == nullptr) return;
    
    std::cout << root->value << " ";
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(Node* root) {
    if (root == nullptr) return;
    
    inOrder(root->left);
    std::cout << root->value << " ";
    inOrder(root->right);
}

void postOrder(Node* root) {
    if (root == nullptr) return;
    
    postOrder(root->left);
    postOrder(root->right);
    std::cout << root->value << " ";
}

void deleteTree(Node* root) {
    if (root == nullptr) return;
    
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    std::string expression = "a + 5 * b / c - c ^ 8 + d * e ^ 0.5";
    
    Node* root = buildTree(expression);
    
    std::cout << "PreOrder : ";
    preOrder(root);
    std::cout << "\nInOrder  : ";
    inOrder(root);
    std::cout << "\nPostOrder: ";
    postOrder(root);
    std::cout << std::endl;
    
    deleteTree(root);
    
    return 0;
}