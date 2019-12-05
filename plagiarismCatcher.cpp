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

int main()
{

    // need to change this to get a string from the user input
    string dir = string("sm_doc_set");
    vector<string> files = vector<string>();

    int result = getdir(dir,files);

    HashTable hashTable(25);
    //hashTable.showCollisions();

    if (result != 0) {
        // checks to see if the pathname worked to get the file names
        cout << "Pathname doesn't exist" << endl;
        return errno;
    }
    // were good, the filenames are in the vector

   for (unsigned int i = 0;i < 3;i++) {
            ifstream textFile;
            string path = "sm_doc_set/" + files[i] ;
            textFile.open(path);
            string text;
            string totalString;
            
            while (!textFile.eof()) {
                textFile >> text;
                text = capitalizeString(text);
                cout << text;



            }
            
            textFile.close();
            
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