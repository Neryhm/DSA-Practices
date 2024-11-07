#include <iostream>
#include "Student.cpp"

int main(){
    List listStudent;
    createList(listStudent);
    Student additionStudent = {
        "20224432",             // ID
        "Do Thanh Dat",         // Name
        1,                      // Sex (0 for female)
        {14, 10, 2004},         // Date of Birth (DD/MM/YYYY)
        "HaNoi",                // Address
        "IoT",                  // Major
        "K67"                   // Enrollment Year
    };
    addNode(listStudent, additionStudent);
    Student additionStudent2 = {
        "20224411",             // ID
        "Frank",                // Name
        1,                      // Sex (0 for female)
        {14, 10, 2004},         // Date of Birth (DD/MM/YYYY)
        "USA",                  // Address
        "CS",                   // Major
        "K67"                   // Enrollment Year
    };
    addNode(listStudent, additionStudent2);

    sortListByID(listStudent);
    printList(listStudent);
    
    std::cout<<"Do you want to remove students with the same Date?(y/n)";
    char choice;
    std::cin>>choice;
    if(choice = 'y'){
        removeStudentsWithSameDate(listStudent);
        printList(listStudent);
    }
}