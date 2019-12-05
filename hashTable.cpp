#include <string>
#include <iostream>
#include "hashTable.h"
#define Hash_Table_Size 10

using namespace std;


HashTable::HashTable(int numberOfDocs) {
    int** arrayOfPointers = new int* [numberOfDocs];
    hashMap = arrayOfPointers;
    this->numberOfDocs = numberOfDocs;
    for (int i = 0; i < numberOfDocs; i++) {
        hashMap[i] = new int [numberOfDocs];
    }

     for (int i = 0; i < numberOfDocs; i++) {
        for (int j=0; j < numberOfDocs; j++) {
            hashMap[i][j] = 0;
        }

    }


    
}

HashTable::~HashTable() {
    
    for (int i = 0; i < numberOfDocs; i++) {
        delete hashMap[i];
    }

    for (int i = 0; i < Hash_Table_Size; i++) {
        if (hashTable[i] == NULL) {
            cout << "THIS hash is initialized to NULL" << endl;
        }
    }

    delete hashMap;
    
}

void HashTable::hashToTable(int docNumber, string text) {
    int index = hash(text);
    hashTable[index]->push_back(docNumber);


}

int HashTable::hash(string text) {
    int length = text.size();
    int sum = 0;

    for (int i = 0; i < (length -1); i++) {
        sum = sum + (text[length - 1 - i] * 7^i);
    }

    return (sum%Hash_Table_Size);

}


void HashTable::showCollisions() {
    for (int i = 0; i < numberOfDocs; i++) {
        for (int j=0; j < numberOfDocs; j++) {
            cout << hashMap[i][j];
        }
        cout << endl;

    }


}

