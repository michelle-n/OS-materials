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
    if(stat((folder+"/"+name).c_str(),&fileStat) < 0){
        numberOfFailed++;
        return 1;
    }

    sizeAndEntryName.push_back(std::make_pair(fileStat.st_size, name));
 
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
    DIR *dir = opendir(directoryName.c_str());

    if (dir){

        struct dirent *de = readdir(dir);

        while(de){

            std::string name = de->d_name;
            if (name.compare(".") == 0 || name.compare("..") == 0) {
                de = readdir(dir);
                continue;
            }

            getStats(directoryName, name);

            de = readdir(dir);
        }
        closedir(dir);
        return 0; 
    }
    else {
        printf("error: could not open directory\n");
        return 1;
    }
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
    
    // Sort the vector sizeAndEntryName by size (note that this is the first entry in the pairs!!)
    std::sort(sizeAndEntryName.begin(), sizeAndEntryName.end());

    // Print number of fails
    printf("Number stat fails: %ld\n---------\n", numberOfFailed);


    // Go through the sorted sizeAndEntryName vector and print out names/sizes
    for(auto myPair : sizeAndEntryName){
        printf("File: %s\n\tSize: %ld\n---------\n", myPair.second.c_str(), myPair.first);
    }

    return 0;

}
