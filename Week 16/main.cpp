#include <iostream>

// Đề mục
enum NodeType {
    BOOK,
    CHAPTER,
    SECTION,
    SUBSECTION,
    SUBSUBSECTION
};

// Khai báo Node
class Node {
public:
    // Giới hạn độ dài tiêu đề
    static const int MAX_TITLE_LENGTH = 100;
    
    char title[MAX_TITLE_LENGTH];
    NodeType type;
    int start_page;
    int total_pages;
    Node* children[10];  // Giới hạn 10 node con
    int child_count;
    Node* parent;

    // Hàm so sánh chuỗi
    bool compareTitle(const char* other_title) {
        int i = 0;
        while (title[i] != '\0' && other_title[i] != '\0') {
            if (title[i] != other_title[i]) return false;
            i++;
        }
        return title[i] == '\0' && other_title[i] == '\0';
    }

    // Copy tiêu đề
    void copyTitle(const char* new_title) {
        int i = 0;
        while (new_title[i] != '\0' && i < MAX_TITLE_LENGTH - 1) {
            title[i] = new_title[i];
            i++;
        }
        title[i] = '\0';
    }

    // Constructor
    Node(const char* new_title, NodeType node_type, int start = 0, int pages = 0) {
        copyTitle(new_title);
        type = node_type;
        start_page = start;
        total_pages = pages;
        child_count = 0;
        parent = nullptr;
    }

    // Thêm node con
    void addChild(Node* child) {
        if (child_count < 10) {
            children[child_count++] = child;
            child->parent = this;
        }
    }

    // Xoá node con
    void removeChild(const char* child_title) {
        for (int i = 0; i < child_count; i++) {
            if (children[i]->compareTitle(child_title)) {
                // Dịch các node phía sau lên
                delete children[i];
                for (int j = i; j < child_count - 1; j++) {
                    children[j] = children[j + 1];
                }
                child_count--;
                break;
            }
        }
    }
};

// Lớp quản lý cấu trúc sách
class BookStructure {
private:
    Node* root;

    // Tìm node theo title
    Node* findNode(Node* current, const char* title) {
        if (current == nullptr) return nullptr;

        // Kiểm tra node hiện tại
        if (current->compareTitle(title)) return current;

        // Tìm kiếm ở các node con
        for (int i = 0; i < current->child_count; i++) {
            Node* found = findNode(current->children[i], title);
            if (found) return found;
        }

        return nullptr;
    }

    // Tìm chương dài nhất
    void findLongestChapter(Node* node, Node*& longest_chapter, int& max_pages) {
        if (node == nullptr) return;

        // Nếu là chương và có số trang lớn hơn
        if (node->type == CHAPTER && node->total_pages > max_pages) {
            longest_chapter = node;
            max_pages = node->total_pages;
        }

        // Duyệt các node con
        for (int i = 0; i < node->child_count; i++) {
            findLongestChapter(node->children[i], longest_chapter, max_pages);
        }
    }

    void printHierarchyRecursive(Node* node, int depth = 0) {
        if (node == nullptr) return;

        // In ra dấu gạch ngang theo độ sâu
        for (int i = 0; i < depth; i++) {
            std::cout << "_";
        }

        // In tiêu đề node
        std::cout << " " << node->title 
                  << " (Trang " << node->start_page 
                  << "-" << (node->start_page + node->total_pages - 1) 
                  << ")" << std::endl;

        // Đệ quy in các node con
        for (int i = 0; i < node->child_count; i++) {
            printHierarchyRecursive(node->children[i], depth + 1);
        }
    }

public:
    // Constructor
    BookStructure(const char* book_title) {
        root = new Node(book_title, BOOK);
    }

    // Thêm node vào root
    void addToRoot(Node* node) {
        root->addChild(node);
    }

    // Lấy số chương
    int getChapterCount() {
        int count = 0;
        for (int i = 0; i < root->child_count; i++) {
            if (root->children[i]->type == CHAPTER) {
                count++;
            }
        }
        return count;
    }

    // Tìm chương dài nhất
    Node* getLongestChapter() {
        Node* longest_chapter = nullptr;
        int max_pages = 0;
        findLongestChapter(root, longest_chapter, max_pages);
        return longest_chapter;
    }

    // Xoá một mục
    void removeSection(const char* section_title) {
        Node* node_to_remove = findNode(root, section_title);
        if (node_to_remove && node_to_remove->parent) {
            node_to_remove->parent->removeChild(section_title);
        }
    }

    // In cấu trúc sách
    void printBookHierarchy() {
        std::cout << "Cấu trúc sách:" << std::endl;
        printHierarchyRecursive(root);
    }

    // In ra thông tin về chương dài nhất
    void printLongestChapter() {
        Node* longest = getLongestChapter();
        if (longest) {
            std::cout << "Chương dài nhất: " << longest->title 
                      << " || Số trang: " << longest->total_pages << std::endl;
        }
    }

    // Destructor
    ~BookStructure() {
        // Giải phóng bộ nhớ (implement đơn giản)
        delete root;
    }
};

int main() {
    BookStructure book("Cấu Trúc Dữ Liệu & Giải Thuật");
    
    // Tạo các chương
    Node* chapter1 = new Node("Sắp xếp & Tìm kiếm", CHAPTER, 1, 50);
    Node* chapter2 = new Node("Liên kết đơn, Ngăn xếp, Hàng đợi", CHAPTER, 51, 75);
    
    // Tạo các section
    Node* section1_1 = new Node("Sắp xếp", SECTION, 1, 20);
    Node* section1_2 = new Node("Tìm kiếm", SECTION, 21, 30);

    // Tạo các subsection
    Node* subsection1_1_1 = new Node("BubbleSort", SUBSECTION, 5, 10);
    Node* subsection1_1_2 = new Node("InsertionSort", SUBSECTION, 15, 10);
    
    // Xây dựng cấu trúc
    book.addToRoot(chapter1);
    book.addToRoot(chapter2);
    
    chapter1->addChild(section1_1);
    chapter1->addChild(section1_2);

    section1_1->addChild(subsection1_1_1);
    section1_1->addChild(subsection1_1_2);

    // In số chương
    std::cout << "Số chương: " << book.getChapterCount() << std::endl;

    // In chương dài nhất
    book.printLongestChapter();
    
    // In cấu trúc sách
    book.printBookHierarchy();

    // Xoá một section
    book.removeSection("BubbleSort");

    return 0;
}
