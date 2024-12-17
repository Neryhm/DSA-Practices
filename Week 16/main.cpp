#include <iostream>

bool compareStrings(const char* str1, const char* str2) {
    // Iterate through both strings
    for (int i = 0; i < 100; ++i) {
        // If both chars are null, we've reached the end and strings match
        if (str1[i] == '\0' && str2[i] == '\0') {
            return true;
        }
        
        // If chars differ, strings don't match
        if (str1[i] != str2[i]) {
            return false;
        }
    }
    
    // Should never reach here, but return false as safeguard
    return false;
}
class ContentNode {
public:
    char title[100];  // Fixed-size array for title
    int numPages;     // Number of pages for this node

    // Fixed-size array of child pointers
    ContentNode* children[10];  
    int childCount;

    // Constructor with clean initialization
    ContentNode(const char* nodeTitle, int pages = 0) : 
        numPages(pages), childCount(0) {
        // Fully zero out the title
        for (int i = 0; i < 100; ++i) {
            title[i] = '\0';
        }

        // Safely copy title
        for(int i = 0; i < 99 && nodeTitle[i] != '\0'; ++i) {
            title[i] = nodeTitle[i];
        }

        // Ensure zero-initialization of children pointers
        for (int i = 0; i < 10; ++i) {
            children[i] = nullptr;
        }
    }

    void addChild(ContentNode* child) {
        if (childCount < 10) {  // Prevent overflow
            children[childCount++] = child;
            // Recalculate pages for parent nodes after adding a child
            updatePageCount();
        }
    }

    // Recursive method to calculate total pages
    int calculateTotalPages() {
        // If no children, return the node's own page count
        if (childCount == 0) {
            return numPages;
        }

        // Sum pages of all children
        int totalChildPages = 0;
        for (int i = 0; i < childCount; ++i) {
            totalChildPages += children[i]->calculateTotalPages();
        }

        // Update total pages, using max of direct pages or child pages
        numPages = totalChildPages;
        return numPages;
    }

    // Update page count up the hierarchy
    void updatePageCount() {
        calculateTotalPages();
    }

    void print(int depth = 0) const {
        // Create depth indicator using '-'
        for (int i = 0; i < depth; ++i) {
            std::cout << "-";
        }
        
        // Print node information with page count
        std::cout << " " << title 
                  << " (Pages: " << numPages << ")" << std::endl;
        
        // Recursively print children
        for (int i = 0; i < childCount; ++i) {
            children[i]->print(depth + 1);
        }
    }

    // Recursive method to count chapters (direct children of root)
    int countChapters() const {
        return childCount;
    }

    // Recursive method to find the longest chapter
    ContentNode* findLongestChapter() {
        ContentNode* longestChapter = nullptr;
        int maxPages = 0;

        for (int i = 0; i < childCount; ++i) {
            if (children[i]->numPages > maxPages) {
                maxPages = children[i]->numPages;
                longestChapter = children[i];
            }
        }

        return longestChapter;
    }

    // Recursive method to search and delete a node by title
    bool deleteNodeByTitle(const char* searchTitle) {
        for (int i = 0; i < childCount; ++i) {
            // If child matches title, remove and shift
            if (compareStrings(children[i]->title, searchTitle)) {
                // Delete the found node
                delete children[i];
                
                // Shift remaining children
                for (int j = i; j < childCount - 1; ++j) {
                    children[j] = children[j+1];
                }
                
                // Reduce child count
                childCount--;
                
                // Recalculate page count
                updatePageCount();
                
                return true;
            }

            // Recursively search in children
            if (children[i]->deleteNodeByTitle(searchTitle)) {
                return true;
            }
        }

        return false;
    }
};

class BookContents {
private:
    ContentNode* root;

public:
    BookContents(const char* bookTitle) {
        root = new ContentNode(bookTitle);
    }

    ~BookContents() {
        // Simple destructor to prevent memory leaks
        deleteNode(root);
    }

    void deleteNode(ContentNode* node) {
        if (node == nullptr) return;

        for (int i = 0; i < node->childCount; ++i) {
            deleteNode(node->children[i]);
        }
        delete node;
    }

    ContentNode* getRoot() { return root; }

    void printTableOfContents() {
        root->calculateTotalPages();  // Ensure page counts are up to date
        std::cout << "Table of Contents:" << std::endl;
        root->print();
    }

    // Wrapper methods for new functionality
    int getChapterCount() {
        return root->countChapters();
    }

    void findAndPrintLongestChapter() {
        ContentNode* longestChapter = root->findLongestChapter();
        if (longestChapter) {
            std::cout << "Longest Chapter: " 
                      << longestChapter->title 
                      << " (Pages: " << longestChapter->numPages << ")" << std::endl;
        }
    }

    bool deleteChapter(const char* chapterTitle) {
        return root->deleteNodeByTitle(chapterTitle);
    }
};

int main() {
    // Create book
    BookContents book("Advanced Programming Techniques");
    
    // Create chapters with initial page estimates
    ContentNode* chapter1 = new ContentNode("Fundamentals", 50);
    ContentNode* chapter2 = new ContentNode("Advanced Concepts", 75);

    // Create sections with page estimates
    ContentNode* section1_1 = new ContentNode("Basic Principles", 20);
    ContentNode* section1_2 = new ContentNode("Data Structures", 30);

    // Create subsections with page estimates
    ContentNode* subsection1_1_1 = new ContentNode("Memory Management", 10);
    ContentNode* subsection1_1_2 = new ContentNode("Algorithm Complexity", 15);

    // Build hierarchy
    section1_1->addChild(subsection1_1_1);
    section1_1->addChild(subsection1_1_2);
    
    chapter1->addChild(section1_1);
    chapter1->addChild(section1_2);

    book.getRoot()->addChild(chapter1);
    book.getRoot()->addChild(chapter2);

    // Print initial table of contents
    std::cout << "Initial Table of Contents:" << std::endl;
    book.printTableOfContents();

    // Demonstrate new functionality
    std::cout << "\nNumber of Chapters: " << book.getChapterCount() << std::endl;
    
    book.findAndPrintLongestChapter();

    // Attempt to delete a chapter
    std::cout << "\nDeleting 'Memory Management' subsection:" << std::endl;
    if (book.deleteChapter("Memory Management")) {
        std::cout << "Chapter deleted successfully." << std::endl;
    } else {
        std::cout << "Chapter not found." << std::endl;
    }

    // Print updated table of contents
    std::cout << "\nUpdated Table of Contents:" << std::endl;
    book.printTableOfContents();

    return 0;
}