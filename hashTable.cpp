#include <string>
#include <iostream>
#include "hashTable.h"
#define Hash_Table_Size 1000003

using namespace std;



HashTable::HashTable(int numberOfDocs) {
    int** arrayOfPointers = new int* [numberOfDocs];
    hashMap = arrayOfPointers;
    this->numberOfDocs = numberOfDocs;

    // allocates memeory for all the hashmap
    for (int i = 0; i < numberOfDocs; i++) {
        hashMap[i] = new int [numberOfDocs];
    }

    //zeros it out 

     for (int i = 0; i < numberOfDocs; i++) {
        for (int j=0; j < numberOfDocs; j++) {
            hashMap[i][j] = 0;
        }

    }

    // allocates memory for the hash table
    for (int i = 0; i < Hash_Table_Size; i++) {
        hashTable[i] = new vector<int>;
    }


    
}

HashTable::~HashTable() {

    // deletes all the allocated memory
    for (int i = 0; i < numberOfDocs; i++) {
        delete hashMap[i];
    }

    for (int i = 0; i < Hash_Table_Size; i++) {
        delete hashTable[i];
    }




    delete hashMap;
    
}

void HashTable::hashVector(int docNumber, int wordCount, vector<string> &collisions) {
    // hashes & stores every n word combination from a vector
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
    // useless function
    int index = hash(text);
    hashTable[index]->push_back(docNumber);


}

int HashTable::hash(string text) {
    // converts a string into a number between 1 & 1000003
    // function from Dr.Priebes slides
    
    int length = text.size();
    int sum = 0;

    for (int i = 0; i < (length -1); i++) {
        sum = sum + (text[length - 1 - i] * 37^i);
        sum = sum%Hash_Table_Size;
    }

    

    return (sum);

    

}


 vector<HashTable::Collision> HashTable::showCollisions(int lowerBound) {
    

    // creates & returns a vector of all the collisions higher than the bound given
   vector<Collision> collisionsVector;

   for (int i = 0; i<numberOfDocs; i++) {
       for (int j=0; j<numberOfDocs; j++) {
           int collisions = hashMap[i][j];
           if (collisions > lowerBound) {
               // 
               Collision c = Collision();
               c.index1 = i;
               c.index2 = j;
               c.numCollisions = collisions;
               collisionsVector.push_back(c);
           }
       }
   }

   return collisionsVector;




}

void HashTable::populateCollisions() {
    // loop through hash table
    for (int i = 0; i < Hash_Table_Size; i++) {
        vector <int> collisions = *hashTable[i];

        if (collisions.empty()) {
            continue;
        }
                
            for (int j = 0; j < collisions.size(); j++) {
                // we use j+1 so we don't double count
                for (int k = j+1; k < collisions.size(); k++) {
                        if (j == k) {
                            continue;
                        }
                        // we increment every collision that aren't the same index
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

