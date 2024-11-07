#include "Student.hpp"

void inputStudent(Student& s){
    std::cout << "Enter ID: ";
    std::cin>>s.id;
    std::cin.ignore();

    std::cout << "Enter name: ";
    std::cin.getline(s.name, 50);

    std::cout << "Enter sex (0 for female, 1 for male): ";
    std::cin >> s.sex;
    std::cin.ignore();

    std::cout << "Enter date of birth (DD/MM/YYYY): ";
    std::cin >> s.date.day >> s.date.month >> s.date.year;
    std::cin.ignore();

    std::cout << "Enter address: ";
    std::cin.getline(s.address, 100);

    std::cout << "Enter major: ";
    std::cin.getline(s.major, 12);

    std::cout << "Enter enrollment year (YYYY): ";
    std::cin.getline(s.gen, 7);
    // fflush(stdin);
}

void addNode(List& list, const Student& s){
    Node* newNode = new Node;
    newNode->data = s;
    newNode->link = nullptr;

    if (!list.first) {
        list.first = list.last = newNode;
    } else {
        list.last->link = newNode;
        list.last = newNode;
    }
}

void createList(List& list) {
    list.first = list.last = nullptr;

    Student s;
    inputStudent(s);
    addNode(list, s);
}

void swapNode(Node*& a, Node*& b) {
    Student temp = a->data;
    a->data = b->data;
    b->data = temp;
}

void sortListByID(List& list){
    if (!list.first) return; // Empty list

    bool swapped;
    Node* current;
    Node* last = nullptr;

    do {
        swapped = false;
        current = list.first;

        while (current->link != last) {
            if (current->data.id > current->link->data.id) {
                swapNode(current, current->link);
                swapped = true;
            }
            current = current->link;
        }
        last = current;
    } while (swapped);
}

void printList(const List& list) {
    Node* current = list.first;

    while (current != nullptr) {
        std::cout << "ID: " << current->data.id << std::endl;
        std::cout << "Name: " << current->data.name << std::endl;
        std::cout << "Sex: " << (current->data.sex == 1 ? "Male" : "Female") << std::endl;
        std::cout << "Date of Birth: " << current->data.date.day << "/" << current->data.date.month << "/" << current->data.date.year << std::endl;
        std::cout << "Address: " << current->data.address << std::endl;
        std::cout << "Major: " << current->data.major << std::endl;
        std::cout << "Enroll Year: " << current->data.gen << std::endl;
        std::cout << std::endl;

        current = current->link;
    }
}

void removeStudentsWithSameDate(List& list){
    if (!list.first) return; // Empty list

    Node* current = list.first;
    Node* previous = nullptr;

    while (current) {
        bool foundDuplicate = false;
        Node* runner = list.first;

        while (runner != current) {
            if (runner->data.date.day == current->data.date.day &&
                runner->data.date.month == current->data.date.month &&
                runner->data.date.year == current->data.date.year) {
                foundDuplicate = true;
                break;
                }
            runner = runner->link;
        }

        if (foundDuplicate) {
            // Remove the current node
            if (previous) {
                previous->link = current->link;
            } else {
                list.first = current->link;
            }

            if (current == list.last) {
                list.last = previous;
            }

            current = current->link;
        } else {
            previous = current;
            current = current->link;
        }
    }
}