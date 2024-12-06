#include <iostream>

struct Node {
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

Node* buildExpressionTree(std::string expr) {
    // Remove spaces from expression
    std::string newExpr;
    for (char c : expr) {
        if (c != ' ') {
            newExpr += c;
        }
    }
    expr = newExpr;
    // Stacks for operators and operands
    Node* operandStack[100];
    char operatorStack[100];
    int operandTop = -1;
    int operatorTop = -1;

    for (int i = 0; i < expr.length(); i++) {
        // If digit or decimal point, parse the full number
        if ((expr[i] >= '0' && expr[i] <= '9') || expr[i] == '.') {
            std::string number;
            bool hasDecimal = false;
            
            while (i < expr.length() && 
                   ((expr[i] >= '0' && expr[i] <= '9') || expr[i] == '.')) {
                if (expr[i] == '.') {
                    if (hasDecimal) break; // Second decimal point is invalid
                    hasDecimal = true;
                }
                number += expr[i];
                i++;
            }
            i--; // Compensate for extra increment
            
            operandStack[++operandTop] = new Node(number);
        }
        // If operand (letter), push to operand stack
        else if ((expr[i] >= 'a' && expr[i] <= 'z')) {
            std::string operand;
            while (i < expr.length() && 
                   (expr[i] >= 'a' && expr[i] <= 'z')) {
                operand += expr[i];
                i++;
            }
            i--; // Compensate for extra increment
            
            operandStack[++operandTop] = new Node(operand);
        }
        // If opening parenthesis, push to operator stack
        else if (expr[i] == '(') {
            operatorStack[++operatorTop] = expr[i];
        }
        // If closing parenthesis, process until opening parenthesis
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
            // Remove opening parenthesis
            if (operatorTop >= 0 && operatorStack[operatorTop] == '(')
                operatorTop--;
        }
        // If operator
        else if (expr[i] == '+' || expr[i] == '-' || 
                 expr[i] == '*' || expr[i] == '/' || expr[i] == '^') {
            // Process operators with higher or equal precedence
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
            
            // Push current operator
            operatorStack[++operatorTop] = expr[i];
        }
    }
    
    // Process remaining operators
    while (operatorTop >= 0) {
        char op = operatorStack[operatorTop--];
        
        Node* right = operandStack[operandTop--];
        Node* left = operandStack[operandTop--];
        
        Node* newNode = new Node(std::string(1, op));
        newNode->left = left;
        newNode->right = right;
        
        operandStack[++operandTop] = newNode;
    }
    
    return operandStack[0]; // Root of the expression tree
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
    
    Node* root = buildExpressionTree(expression);
    
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