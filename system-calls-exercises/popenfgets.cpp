
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

#define PATH_MAX 255

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

    std::string command = "ls -l " + foldername;
    fp = popen(command.c_str(), "r");


    while (fgets(path, PATH_MAX, fp) != NULL){
        auto result = split(path);
        // probably don't it like this
        if (result[0].compare("total") != 0){
            sizeAndEntryName.push_back(std::make_pair(std::stol(result[4]),result[8]));
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
    

    // Sort the vector sizeAndEntryName by size (note that this is the first entry in the pairs!!)
    std::sort(sizeAndEntryName.begin(), sizeAndEntryName.end());


    // Go through the sorted sizeAndEntryName vector and print out names/sizes
    for(auto myPair : sizeAndEntryName){
        printf("File: %s\n\tSize: %ld\n---------\n", myPair.second.c_str(), myPair.first);
    }

    return 0;
}
