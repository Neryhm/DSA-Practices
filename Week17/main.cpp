#include <iostream>
#include <iomanip>
#include <queue>
using namespace std;

// Cấu trúc node cho cây AVL
struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
};

// Hàm tạo node mới
Node* newNode(int data) {
    Node* node = new Node();
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Hàm lấy chiều cao của node
int getHeight(Node* node) {
    if (node == NULL) return 0;
    return node->height;
}

// Hàm lấy hệ số cân bằng của node
int getBalance(Node* node) {
    if (node == NULL) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Hàm cập nhật chiều cao của node
void updateHeight(Node* node) {
    if (node == NULL) return;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}

// Hàm xoay phải (Right Rotation)
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Thực hiện xoay
    x->right = y;
    y->left = T2;

    // Cập nhật chiều cao
    updateHeight(y);
    updateHeight(x);

    return x;
}

// Hàm xoay trái (Left Rotation)
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Thực hiện xoay
    y->left = x;
    x->right = T2;

    // Cập nhật chiều cao
    updateHeight(x);
    updateHeight(y);

    return y;
}

// Hàm thêm node mới vào cây AVL
Node* insert(Node* node, int data) {
    // 1. Thực hiện thêm node như BST thông thường
    if (node == NULL)
        return newNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else // Không cho phép giá trị trùng lặp
        return node;

    // 2. Cập nhật chiều cao của node cha
    updateHeight(node);

    // 3. Kiểm tra hệ số cân bằng và cân bằng lại cây nếu cần
    int balance = getBalance(node);

    // Trường hợp Left Left
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // Trường hợp Right Right
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    // Trường hợp Left Right
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Trường hợp Right Left
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Hàm in cây theo thứ tự inorder
void inorderPrint(Node* root, string prefix = "") {
    if (root != NULL) {
        cout << prefix << "Giá trị: " << root->data 
             << ", Chiều cao: " << root->height 
             << ", Hệ số cân bằng: " << getBalance(root) << endl;
        
        inorderPrint(root->left, prefix + "    L: ");
        inorderPrint(root->right, prefix + "    R: ");
    }
}

// Hàm vẽ cây
void printTree(Node* root) {
    if (root == NULL) return;

    queue<pair<Node*, int>> q;
    q.push({root, 0});
    int level = 0;
    int maxLevel = getHeight(root);
    
    vector<vector<string>> levels(maxLevel * 2);
    int width = 4;  // Khoảng cách giữa các node
    int totalWidth = width * (1 << maxLevel);
    
    while (!q.empty() && level < maxLevel) {
        int levelSize = q.size();
        levels[level * 2].resize(totalWidth, " ");
        
        if (level < maxLevel - 1) {
            levels[level * 2 + 1].resize(totalWidth, " ");
        }
        
        int offset = width * (1 << (maxLevel - 1 - level));
        
        for (int i = 0; i < levelSize; i++) {
            auto [node, pos] = q.front();
            q.pop();
            
            if (node) {
                // In số
                string nodeStr = to_string(node->data);
                int position = pos * (width * (1 << (maxLevel - level))) + offset;
                levels[level * 2][position] = nodeStr;
                
                // In đường nối
                if (level < maxLevel - 1) {
                    if (node->left) {
                        levels[level * 2 + 1][position - offset/2] = "/";
                        q.push({node->left, pos * 2});
                    }
                    if (node->right) {
                        levels[level * 2 + 1][position + offset/2] = "\\";
                        q.push({node->right, pos * 2 + 1});
                    }
                }
            }
        }
        level++;
    }
    
    // In cây
    for (const auto& level : levels) {
        for (const string& s : level) {
            cout << s;
        }
        cout << endl;
    }
    
    cout << "\nThông tin chi tiết:" << endl;
    inorderPrint(root);
    cout << "--------------------------------" << endl;
}

int main() {
    Node* root = NULL;
    int arr[] = {240, 73, 101, 21, 13, 25, 11, 37, 89, 30, 15, 51};
    int n = sizeof(arr)/sizeof(arr[0]);

    cout << "Quá trình thêm các phần tử vào cây AVL:" << endl;
    
    // Thêm từng phần tử và in ra trạng thái cây sau mỗi lần thêm
    for(int i = 0; i < n; i++) {
        cout << "\nThêm phần tử " << arr[i] << ":" << endl;
        root = insert(root, arr[i]);
        printTree(root);
    }

    return 0;
}