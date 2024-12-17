#include <iostream>

struct File {
    std::string data;
    std::string addedDate;
    int size;
    int timeToCreate;
};

struct Node {
    File data;
    Node* next;
};

class Folder {
private:
    Node* head;
    Node* tail;
public:
    Folder() : head(nullptr), tail(nullptr) {}

    void addFile(const File& file) {
        Node* newNode = new Node;
        newNode->data = file;
        newNode->next = nullptr;

        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void sortBySize() {
        Node* current = head;
        while (current) {
            Node* minNode = current;
            Node* nextNode = current->next;
            while (nextNode) {
                if (nextNode->data.size < minNode->data.size) {
                    minNode = nextNode;
                }
                nextNode = nextNode->next;
            }
            if (minNode != current) {
                File temp = current->data;
                current->data = minNode->data;
                minNode->data = temp;
            }
            current = current->next;
        }
    }

    void deleteSlowestFile() {
        if (!head) return;
        Node* highestNode = head;
        Node* prev = nullptr;
        Node* prevHighest = nullptr;
        Node* current = head;

        while (current) {
            if (current->data.timeToCreate > highestNode->data.timeToCreate ||
               (current->data.timeToCreate == highestNode->data.timeToCreate && current->data.size < highestNode->data.size)) {
                highestNode = current;
                prevHighest = prev;
            }
            prev = current;
            current = current->next;
        }

        if (highestNode == head) {
            head = head->next;
            if (!head) {
                tail = nullptr;
            }
        } else {
            prevHighest->next = highestNode->next;
            if (highestNode == tail) {
                tail = prevHighest;
            }
        }
        delete highestNode;
    }

    void printFiles() {
        Node* current = head;
        while (current) {
            std::cout << current->data.data << " " << current->data.addedDate << " " << current->data.size << " " << current->data.timeToCreate << std::endl;
            current = current->next;
        }
    }
};

int main() {
    Folder folder;
    folder.addFile({"Music.txt", "2022-12-01", 190, 3687192});
    folder.addFile({"Doc.txt", "2022-12-05", 52, 12037842});
    folder.addFile({"Picture.txt", "2022-11-01", 376, 46234});
    folder.addFile({"Video.txt", "2022-11-20", 150, 2234156});
    folder.addFile({"Program.txt", "2022-12-01", 278, 543523});
    folder.printFiles();
    std::cout << std::endl;

    std::cout << "Sorted By Size: \n";
    folder.sortBySize();
    folder.printFiles();
    std::cout << std::endl;

    std::cout << "Delete Highest saveTime Node 3 times: \n";
    folder.deleteSlowestFile();
    folder.deleteSlowestFile();
    folder.deleteSlowestFile();
    folder.printFiles();
    return 0;
}