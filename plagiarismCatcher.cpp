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
// confirm w TA what t

int main()
{

    // need to change this to get a string from the user input
    string dir = string("sm_doc_set");
    vector<string> files = vector<string>();

    int checkLength = 7;

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

   for (unsigned int i = 0;i < files.size();i++) {
            cout << files[i] << endl;
            vector<string> fileText;
            ifstream textFile;
            string path = "sm_doc_set/" + files[i] ;
            textFile.open(path);
            string text;
            
        
            while (!textFile.eof()) {
                textFile >> text;
                text = capitalizeString(text);
               // cout << text;
                fileText.push_back(text);
            }
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

    hashTable.populateCollisions();

    hashTable.showCollisions();

    
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