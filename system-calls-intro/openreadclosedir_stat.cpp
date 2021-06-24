/**
 * Example of opendir,readdir,closedir, and stat. 
 * https://man7.org/linux/man-pages/man2/readdir.2.html
 * https://man7.org/linux/man-pages/man3/opendir.3.html
 * https://man7.org/linux/man-pages/man3/closedir.3.html
 * https://man7.org/linux/man-pages/man2/stat.2.html
 * 
 * **/

#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

// Prints stats for a given path
static void direntry_stat(const std::string &path){
    
    struct stat pathStat;

    // Get stats of path
    if( stat(path.c_str(), &pathStat) != 0 ){
        // Exit with error if stat fails
        std::cout << "Error: stat failed" << std::endl;
        return;
    }

    // Print stats for path
    std::cout << "Stats for " << path << std::endl;

    // Print whether or not it is a directory
    if( S_ISDIR(pathStat.st_mode) ){
        std::cout << "Directory? Yes. \n";
    } else {
        std::cout << "Directory? No. \n";
    }


    // Print out size
    std::cout << "Size? " << pathStat.st_size << std::endl;

    std::cout << "-----\n";

}


int main(int argc, char* argv[])
{

    // Check # of command line arguments. 
    if (argc != 2){
        std::cout << "Usage: " << argv[0] << " [directory]" << std::endl;
        return 1;
    }

    // Open directory
    DIR *dir = opendir(argv[1]);


    // Check if directory was opened successfully
    if(dir){

        // Read from the directory
        struct dirent *de = readdir(dir);

        // Get stats on directory entries. Keep reading/getting stats until all of directory is read. 
        while(de){

            std::string direntry_name = "/";
            direntry_name += de->d_name;
            direntry_stat(argv[1] + direntry_name);
            de = readdir(dir);

        }

        // Close the directory
        closedir(dir);

        return 0;

    } else {
        // If the directory did not open successfully, quit with error message
        std::cout << "Error: could not open directory." << std::endl;
        return 1;
    }

}
