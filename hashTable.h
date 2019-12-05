#ifndef HASHTABLE_H
#define HASHTABLE_H
#define Hash_Table_Size 10

#include <string>
#include <array>
#include <vector>

using namespace std;

class HashTable {
      
  private:
  int** hashMap;
  int numberOfDocs;
  vector <int>* hashTable[Hash_Table_Size];

   

 
  public:
    // should zero out all hash map & allocate the hash table;
   HashTable(int numberOfDocs);
   ~HashTable();    

   // this could cause seg faults, so beware
   void hashToTable(int docNumber, string text);
   int hash(string text);
   void showCollisions();



   

};



#endif