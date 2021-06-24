
/**
 * 
 * Example exercise using popen and fgets. 
 * 
 * 
 *  EXERCISE:
 *  - Use popen to run the command (cd foldername; ls -l)
 *  - Use fgets to get lines from the resulting stream
 *  - Split the lines
 * 
 * 
 * NOTE: IN THIS EXERCISE, YOU CAN ASSUME THAT THE DIRECTORY ENTRIES (i.e. files, subdirectories, etc.) DO *NOT* CONTAIN
 *          SPACES IN THEIR NAMES!!!!!!!!!!!!
 *      DO *NOT* MAKE THIS ASSUMPTION ON ASSIGNMENTS UNLESS THE ASSIGNMENT SPECIFICALLY TELLS YOU THAT YOU CAN DO SO. 
 * 
 * **/


#include <stdio.h>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

#define PATH_MAX 255 // TODO: You may or may not have to increase this

// Use these
std::vector<std::pair<int64_t, std::string>> sizeAndEntryName;


/**
 * Taken from slow-pali.cpp
 * 
 * Source: slow-pali.cpp
 * Author: Dr. Pavol Federl
 * Accessed: Oct 14, 2020
 * URL: https://gitlab.com/cpsc457/public/a1/-/blob/master/slow-pali.cpp
 * 
 * **/
//split string p_line into a vector of strings (words)
// the delimiters are 1 or more whitespaces
std::vector<std::string>
split( const std::string & p_line)
{
  auto line = p_line + " ";
  std::vector<std::string> res;
  bool in_str = false;
  std::string curr_word = "";
  for( auto c : line) {
    if( isspace(c)) {
      if( in_str)
        res.push_back(curr_word);
      in_str = false;
      curr_word = "";
    }
    else {
      curr_word.push_back(c);
      in_str = true;
    }
  }
  return res;
}


/**
*   name: popenLsl
*   params:
*       - foldername : the folder that you want to call 'ls -l' on/in
*   description:
*       - Uses popen to get stream of 'cd foldername; ls -l' where foldername is provided by the param
*           - Get lines using fgets, then split the lines using split method (above)
*           - Add the size and entry names from the ls -l output to sizeAndEntryName 
*   returns:
*       - none
 * **/
void popenLsl(std::string foldername){
    FILE *fp;
    char path[PATH_MAX];

    std::string command = "ls -l " + foldername; // don't touch this

    // TODO: Use popen to run command ... Do you want to use read or write mode?
    fp = popen(YOU DO THIS);


    // TODO: use fgets to read from stream (...yes... from popen, that pointer to that open stream mhmm hmm) and store result in 'path'
    while (fgets(YOU DO THIS) != NULL){

        auto result = split(path);
        // TODO: skip the first line of ls -l since that gives 'total somenumber'
        if (??? YOU DO THIS){
            // use 'result' and get the size and name of the entry/file/directory
            // Put that as a pair into the vector sizeAndEntryName
            // i.e. (size, name) are the pairs that should be put into sizeAndEntryName
            sizeAndEntryName.push_back(std::make_pair(YOU DO THIS: it should be the size, name-of-the-entry/files/directory);
        }

    }

    pclose(fp);
}

int main(int argc, char* argv[]) {
  

    // Check command line args / usage
    if (argc != 2){
        printf("Usage: %s [Directory-to-open]\n", argv[0]);
        printf("\t [Directory-to-open] - For the tutorial exercise, this is one of: Test1, Test2, or Test3\n");
        return 1;
    }

    // Call popen and ls -l at the folder location
    popenLsl(argv[1]);
    

    // TODO: Sort the vector sizeAndEntryName by size (note that this is the first entry in the pairs!!)
    std::sort(YOU DO THIS);


    // TODO: Go through the sorted sizeAndEntryName vector and print out names/sizes
    for(YOU DO THIS){
        printf("File: %s\n\tSize: %ld\n---------\n", ??.second.c_str(), ??.first);
    }

    return 0;
}
