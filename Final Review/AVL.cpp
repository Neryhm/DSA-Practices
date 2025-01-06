#include <iostream>

struct AVLNode {
    int data;
    AVLNode* left;
    AVLNode* right;
    int height;
    
    AVLNode(int val)
        : data(val), left(nullptr), right(nullptr), height(1) {}
};

class AVL {
private:
    AVLNode* root;
    
    int getHeight(AVLNode* node) {
        return node ? node->height : 0;
    }
    
    int getBalance(AVLNode* node) {
        if (!node) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }
    
    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        
        // Thực hiện quay phải
        x->right = y;
        y->left = T2;
        
        // Cập nhật chiều cao
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        
        // x trở thành gốc của subtree sau khi quay
        return x;
    }
    
    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        
        // Thực hiện quay trái
        y->left = x;
        x->right = T2;
        
        // Cập nhật chiều cao
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        
        // y trở thành gốc của subtree sau khi quay
        return y;
    }
    
    AVLNode* insertNode(AVLNode* node, int val) {
        // Thêm nút tương tự BST
        if (!node) return new AVLNode(val);
        if (val < node->data) {
            node->left = insertNode(node->left, val);
        } else if (val > node->data) {
            node->right = insertNode(node->right, val);
        } else {
            // Nếu trùng giá trị thì ta tùy chính sách
            return node; 
        }
        
        // Cập nhật chiều cao
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        
        // Kiểm tra cân bằng
        int balance = getBalance(node);
        
        // TH1: Left Left
        if (balance > 1 && val < node->left->data) {
            return rightRotate(node);
        }
        // TH2: Right Right
        if (balance < -1 && val > node->right->data) {
            return leftRotate(node);
        }
        // TH3: Left Right
        if (balance > 1 && val > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // TH4: Right Left
        if (balance < -1 && val < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        
        return node;
    }
    
    void inOrder(AVLNode* node) {
        if (!node) return;
        inOrder(node->left);
        std::cout << node->data << " ";
        inOrder(node->right);
    }

public:
    AVL() : root(nullptr) {}
    
    void insert(int val) {
        root = insertNode(root, val);
    }
    
    // Hàm remove trong AVL phức tạp hơn, cũng cần cân bằng lại, 
    // skeleton sau chỉ minh họa.
    // Tùy yêu cầu, bạn có thể tham khảo logic xóa của BST, sau đó thêm bước cân bằng.
    
    void inOrderTraversal() {
        inOrder(root);
        std::cout << std::endl;
    }
};
