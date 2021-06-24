/**
 * Example exercise using opendir,readdir,closedir, and stat. 
 * https://man7.org/linux/man-pages/man2/readdir.2.html
 * https://man7.org/linux/man-pages/man3/opendir.3.html
 * https://man7.org/linux/man-pages/man3/closedir.3.html
 * 
 * 
 * EXERCISE:
 *  - Use opendir, readdir, closedir to open the directory given as a command line argument
 *  - Use stat to get the sizes of files:
 *      - add the pair of <filesize, filename> to the vector sizeAndEntryName
 *      - if the stat failed: increase numberOfFailed by 1
 *  - Print out the filesnames and size ordered by size (least to greatest)
 * 
 *  
 * Extension exercise:
 *  - Change the program so it recursively traverses directories (thus will also include subdirectory files)
 * 
 * **/

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string>
#include <unistd.h>
#include <sys/stat.h>
#include <vector>
#include <utility>
#include <algorithm>

// Use these
std::vector<std::pair<int64_t, std::string>> sizeAndEntryName;
int64_t numberOfFailed;


/**************
*   name: getStats
*   params:
*       - folder : the folder that contains the file
*       - name : the name of directory entry (i.e. the name of the file, subdirectory, etc..)
*   description:
*       - Calls stat and tries to add the filesize and filename to sizeAndEntryName vector
*   returns:
*       - 1 if stat failed
*       - 0 if successfully added filename and filesize to the sizeAndEntryName vector
***************/
bool getStats(std::string folder, std::string name){
    struct stat fileStat;

    // TODO: Make sure this stat call works (should call stat on the directory entry you gave it...)
    // hint: where is stat being called relative to? So what pathname should you give?
    // hint: look at manual for stat, do type is the second arg... a struct..? or something else?
    if(stat((YOU FILL THIS IN) < 0){
        numberOfFailed++;
        return 1;
    }

    // TODO: Add the size and name of the directory entry (not the full path!!) to sizeAndEntryName as a pair
    // i.e. (size, name) are the pairs
    sizeAndEntryName.push_back(std::make_pair(YOU DO THIS));
 
    return 0;
}



/**************
*   name: openReadStatClose
*   params:
*       - directoryName : the folder that should be opened
*   description:
*       - Opens the directory
*           - if this fails, print out error and return 1
*       - Reads directory entries until all have been read
*           - calls getStat on them
*       - Close the directory
*   returns:
*       - 1 if could not open directory
*       - 0 otherwise
***************/
bool openReadStatClose(std::string directoryName){

    // TODO: YOU IMPLEMENT THIS
    // hint: ignore "." and ".." entries

    YOU IMPLEMENT THIS!

}


/**************
*   name: main
*   params:
*       - figure it out
*   description:
*       - figure it out
*   returns:
*       - figure it out
***************/
int main(int argc, char* argv[])
{

    // Check command line args / usage
    if (argc != 2){
        printf("Usage: %s [Directory-to-open]\n", argv[0]);
        printf("\t [Directory-to-open] - For the tutorial exercise, this is one of: Test1, Test2, or Test3\n");
        return 1;
    }

    // Set numberOfFailed variable to 0
    numberOfFailed = 0;

    // Try to open/read/close the directory given in the commandline
    if (openReadStatClose(argv[1]) != 0) return 1;
    
    // TODO: Sort the vector sizeAndEntryName by size (note that this is the first entry in the pairs!!)
    std::sort(YOU DO THIS);

    // Print number of fails
    printf("Number stat fails: %ld\n---------\n", numberOfFailed);


    // TODO: Go through the sorted sizeAndEntryName vector and print out names/sizes
    for(YOU DO THIS){
        printf("File: %s\n\tSize: %ld\n---------\n", ??.second.c_str(), ??.first);
    }

    return 0;

}
