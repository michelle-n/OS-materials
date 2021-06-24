#include <iostream>
#include <cstring>

int main(int argc, char* argv[]){

    if (argc != 2){
        std::cout << "Usage: " << argv[0] << " [pin number]\n";
        return 1;
    }

    if (strcmp(argv[1],"9906") == 0){
        std::cout << "Congrats! The youtube video is https://www.youtube.com/watch?v=vSK3maq8Cyk \n";
    } else {
        std::cout << "Wrong pin.\n";
    }

    return 0;

}
