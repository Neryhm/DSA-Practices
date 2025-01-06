#include <iostream>

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    TreeNode* root;
    
public:
    BinaryTree() : root(nullptr) {}
    
    // Tạo cây theo cách đơn giản: gán node gốc nếu chưa có
    void setRoot(int val) {
        if (!root) {
            root = new TreeNode(val);
        }
    }
    
    // Ví dụ hàm chèn node vào trái của một node tạm 
    // (ở ngoài thực tế có thể cần logic khác)
    void insertLeft(TreeNode* parent, int val) {
        if (!parent->left) {
            parent->left = new TreeNode(val);
        }
    }
    
    // Tương tự chèn node vào phải
    void insertRight(TreeNode* parent, int val) {
        if (!parent->right) {
            parent->right = new TreeNode(val);
        }
    }
    
    // Duyệt cây In-order
    void inOrderTraversal(TreeNode* node) {
        if (!node) return;
        inOrderTraversal(node->left);
        std::cout << node->data << " ";
        inOrderTraversal(node->right);
    }
    
    TreeNode* getRoot() {
        return root;
    }
};
