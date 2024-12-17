#include<iostream>

struct Date{
    int day,month,year;
};

struct Student{
    char id[9];
    char name[50];
    int sex;
    Date date;
    char address[100];
    char major[17];
    char gen[7];
};

struct Node{
    Student data;
    Node *link;
};

struct List{
    Node *first;
    Node *last;
};