#include <iostream>

struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;

    // Hàm đệ quy thêm node
    BSTNode* insertNode(BSTNode* node, int val) {
        if (!node) return new BSTNode(val);
        if (val < node->data) {
            node->left = insertNode(node->left, val);
        } else if (val > node->data) {
            node->right = insertNode(node->right, val);
        }
        // Nếu val == node->data thì có thể bỏ qua hoặc xử lý theo ý muốn
        return node;
    }
    
    // Hàm đệ quy xóa node
    BSTNode* removeNode(BSTNode* node, int val) {
        if (!node) return nullptr;
        
        if (val < node->data) {
            node->left = removeNode(node->left, val);
        } else if (val > node->data) {
            node->right = removeNode(node->right, val);
        } else {
            // Tìm thấy node cần xóa
            if (!node->left) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            } else {
                // Node có hai con
                // Tìm node nhỏ nhất bên phải
                BSTNode* temp = findMin(node->right);
                node->data = temp->data;
                node->right = removeNode(node->right, temp->data);
            }
        }
        return node;
    }
    
    BSTNode* findMin(BSTNode* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    void inOrder(BSTNode* node) {
        if (!node) return;
        inOrder(node->left);
        std::cout << node->data << " ";
        inOrder(node->right);
    }

public:
    BST() : root(nullptr) {}
    
    void insert(int val) {
        root = insertNode(root, val);
    }
    
    void remove(int val) {
        root = removeNode(root, val);
    }
    
    void inOrderTraversal() {
        inOrder(root);
        std::cout << std::endl;
    }
};
