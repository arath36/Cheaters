#ifndef HASHTABLE_H
#define HASHTABLE_H
#define Hash_Table_Size 1000003

#include <string>
#include <array>
#include <vector>

using namespace std;

class HashTable {
      
  private:
  // 2D array to keep track of collision count
  int** hashMap;
  int numberOfDocs;
  // hash table
  vector <int>* hashTable[Hash_Table_Size];

  
  

   

 
  public:
    // should zero out all hash map & allocate the hash table;
    // struct to keep track of collisions
    struct Collision {
        int index1;
        int index2;
        int numCollisions;
      
  };

    // constructor & destructor
   HashTable(int numberOfDocs);
   ~HashTable();   

   //takes a vector of strings and hashes all the n length strings
   void hashVector(int docNumber, int wordCount, vector<string> &collisions);
   // I don't even think I used this
   void hashToTable(int docNumber, string text);
   // actual hash function that turns a string into an integer
   int hash(string text);

   // matches the indexes of the hashtable to the actual file names
   vector<Collision> showCollisions(int lowerBound);

   // populates the hashmap from the hashTable
   void populateCollisions();



   

};



#endif