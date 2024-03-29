#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include "hashTable.h"


using namespace std;

int getdir (string dir, vector<string> &files);
string capitalizeString (string input);

// make sure the names of the files don't include the . && ..

int main(int argc, char *argv[]) {

    // get user input
    string dir = argv[1];
    // vector for all the filenames
    vector<string> files = vector<string>();

    int checkLength = atoi(argv[2]);
    int collisionBound = atoi(argv[3]);

    int result = getdir(dir,files);

    
    //hashTable.showCollisions();

    if (result != 0) {
        // checks to see if the pathname worked to get the file names
        cout << "Pathname doesn't exist" << endl;
        return errno;
    }
    // were good, the filenames are in the vector

    // we start at 2 to skip the "." & ".." files that are indexed in the vector

    HashTable hashTable(files.size());

    // loops & hashes all the text files

   for (unsigned int i = 0;i < files.size();i++) {
        
            vector<string> fileText;
            ifstream textFile;
            string path = dir + "/" + files[i] ;
            textFile.open(path);
            string text;
            
            // puts all the words capitalized into a vector
            while (!textFile.eof()) {
                textFile >> text;
                text = capitalizeString(text);
               // cout << text;
                fileText.push_back(text);
            }

            // hashes the vector
            hashTable.hashVector(i, checkLength, fileText );
            // the file is in a string vector

            /* 
            for (int j = 0; j < fileText.size() - checkLength; j++) {
                string hashString = "";
                for (int k = 0; k < checkLength; k++) {
                    hashString = hashString + fileText[j+k];
                }
                
                hashTable.hashToTable(i, hashString);
            }
            */
            

        
            

        

            
            
            
            textFile.close();
            
    }
    // takes the hashed vectors and calculates the collisions
    hashTable.populateCollisions();

    // gets and prints out the collisions
    vector<HashTable::Collision> collisions = hashTable.showCollisions(collisionBound);
    int switches = 1;

    while (switches != 0) {
        switches = 0;
        for (int k = 0; k < collisions.size()-1; k++) {

              if (collisions[k].numCollisions < collisions[k+1].numCollisions) {
            // we swap them 
                HashTable::Collision temp = collisions [k+1];
                collisions[k+1] = collisions[k];
                collisions[k] = temp;

                switches++;

            }
        
        }
    }
    

    for (int k = 0; k < collisions.size(); k++) {
        cout << collisions[k].numCollisions << ": " << files[collisions[k].index1] << ", " << files[collisions[k].index2] << endl;
    }

    
    return 0;
}


/*function... might want it in some class?*/
int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        if (string(dirp->d_name) == "." || string(dirp->d_name) == "..") {
            continue;
        }

        files.push_back(string(dirp->d_name));
    }

    closedir(dp);
    return 0;
}

string capitalizeString (string input) {
    for(int i = 0; i < input.length(); i++){
          input[i] = toupper(input[i]);
    }
    return input;
}