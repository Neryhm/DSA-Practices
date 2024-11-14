#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <vector>

struct Node {
    string word;
    Node* next;
    
    Node(string w) : word(w), next(nullptr) {}
};

void addNode(Node*& first, const string& word) {
    Node* newNode = new Node(word);
    if (first == nullptr) {
        first = newNode;
    } else {
        Node* temp = first;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

string findMostFrequentWord(Node* first) {
    unordered_map<string, int> wordCount;
    Node* temp = first;
    
    while (temp != nullptr) {
        wordCount[temp->word]++;
        temp = temp->next;
    }
    
    string mostFrequentWord;
    int maxCount = 0;
    
    for (const auto& pair : wordCount) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            mostFrequentWord = pair.first;
        }
    }
    
    return mostFrequentWord;
}

void delDupWords(Node*& first) {
    Node* current = first;
    Node* prev = nullptr;
    
    while (current != nullptr && current->next != nullptr) {
        if (current->word == current->next->word) {
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
        } else {
            current = current->next;
        }
    }
}

int countWords(Node* first) {
    unordered_map<string, bool> uniqueWords;
    Node* temp = first;
    
    while (temp != nullptr) {
        uniqueWords[temp->word] = true;
        temp = temp->next;
    }
    
    return uniqueWords.size();
}

void processSentence(Node*& first, const string& sentence) {
    stringstream ss(sentence);
    string word;
    
    while (ss >> word) {
        addNode(first, word);
    }
}

int main() {
    string sentence;
    cout << "Nhập câu: ";
    getline(cin, sentence);
    Node* first = nullptr;

    processSentence(first, sentence);

    string mostFrequent = findMostFrequentWord(first);
    cout << "Most appear word: " << mostFrequent << endl;
    delDupWords(first);
    
    int wordCount = countWords(first);
    cout << "Number of words: " << wordCount << endl;
    
    return 0;
}