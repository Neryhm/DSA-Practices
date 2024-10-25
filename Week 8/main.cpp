#include<iostream>
#include"Student.hpp"

void inputStudent(Student& s){
    std::cout << "Enter ID: ";
    // std::cin.getline(s.ID, 8);
    std::cin>>s.id;
    fflush(stdin);

    std::cout << "Enter name: ";
    std::cin.getline(s.name, 50);
    fflush(stdin);

    std::cout << "Enter sex (0 for female, 1 for male, 2 for robot): ";
    std::cin >> s.sex;
    fflush(stdin);

    std::cout << "Enter date of birth (DD/MM/YYYY): ";
    std::cin >> s.date.day >> s.date.month >> s.date.year;
    fflush(stdin);

    std::cout << "Enter address: ";
    std::cin.getline(s.address, 100);
    fflush(stdin);

    std::cout << "Enter major: ";
    std::cin.getline(s.major, 12);
    fflush(stdin);

    std::cout << "Enter enrollment year (YYYY): ";
    std::cin.getline(s.enrollYear, 7);
    fflush(stdin);
}

void createList(List& list) {
    list.first = list.last = nullptr;

    char choice;
    Student s;
    inputStudent(s);

    Node* newNode = new Node;
    newNode->data = s;
    newNode->link = nullptr;

    if (list.first == nullptr) {
        list.first = list.last = newNode;
    } else {
        list.last->link = newNode;
        list.last = newNode;
    }
}

void swap(Student *a, Student *b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}

void printList(List list) {
    Node* current = list.first;

    while (current != nullptr) {
        std::cout << "ID: " << current->data.id << std::endl;
        std::cout << "Name: " << current->data.name << std::endl;
        std::cout << "Sex: " << (current->data.sex == 1 ? "Male" : "Female") << std::endl;
        std::cout << "Date of Birth: " << current->data.date.day << "/" << current->data.date.month << "/" << current->data.date.year << std::endl;
        std::cout << "Address: " << current->data.address << std::endl;
        std::cout << "Major: " << current->data.major << std::endl;
        std::cout << "Enroll Year: " << current->data.enrollYear << std::endl;
        std::cout << std::endl;

        current = current->link;
    }
}

int main(){
    List listStudent;
    createList(listStudent);
    printList(listStudent);
}