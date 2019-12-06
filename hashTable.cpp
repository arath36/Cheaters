#include <string>
#include <iostream>
#include "hashTable.h"
#define Hash_Table_Size 1000003

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

    for (int i = 0; i < Hash_Table_Size; i++) {
        hashTable[i] = new vector<int>;
    }


    
}

HashTable::~HashTable() {
    
    for (int i = 0; i < numberOfDocs; i++) {
        delete hashMap[i];
    }

    for (int i = 0; i < Hash_Table_Size; i++) {
        delete hashTable[i];
    }




    delete hashMap;
    
}

void HashTable::hashVector(int docNumber, int wordCount, vector<string> &collisions) {
    for (int i = 0; i < collisions.size() - wordCount; i++) {
        string totalString = "";

        for (int j = 0; j < wordCount; j++) {
            totalString = totalString + collisions[i + j];

        }

        int index = hash(totalString);
        hashTable[index] ->push_back(docNumber);

    }

}

void HashTable::hashToTable(int docNumber, string text) {
    int index = hash(text);
    hashTable[index]->push_back(docNumber);


}

int HashTable::hash(string text) {
    
    int length = text.size();
    int sum = 0;

    for (int i = 0; i < (length -1); i++) {
        sum = sum + (text[length - 1 - i] * 37^i);
        sum = sum%Hash_Table_Size;
    }

    

    return (sum);

    

}


void HashTable::showCollisions() {
    /* 
    for (int i = 0; i < numberOfDocs; i++) {
        for (int j=0; j < numberOfDocs; j++) {
            cout << hashMap[i][j] << " ";
        }
        cout << endl;

    }
    */

   for (int i = 0; i<numberOfDocs; i++) {
       for (int j=0; j<numberOfDocs; j++) {
           int collisions = hashMap[i][j];
           if (collisions > 350) {
               cout << collisions << ": Index " << i << " " << j << endl;
           }
       }
   }


}

void HashTable::populateCollisions() {
    for (int i = 0; i < Hash_Table_Size; i++) {
        vector <int> collisions = *hashTable[i];

        if (collisions.empty()) {
            continue;
        }

            for (int j = 0; j < collisions.size(); j++) {
                for (int k = j+1; k < collisions.size(); k++) {
                        if (j == k) {
                            continue;
                        }
                        int x = collisions[j];
                        int y = collisions[k];
                        if (x == y) {
                            continue;
                        }
                        hashMap[x][y] = hashMap[x][y] + 1;

                    }
            }




    }

}

