/**********************************************
 * Last Name:   <your last name>
 * First Name:  <your first name>
 * Student ID:  <your student ID number>
 * Course:      CPSC 457
 * Tutorial:    <T03 or T04>
 * Assignment:  --- not applicable ---
 *
 * File name: depthfirstsearch.cpp
 * 
 * ===== The Social Network =====
 * With Covid and well, just about everything happening in 2020--- it's hard 
 * to know who you can trust. Perhaps if people are friends, or have mutual friends,
 * or a series of friends between them then they can trust each other. 
 * (Psst. Don't take this too seriously, it's just a tutorial exercise-- don't take
 *  this as life advice) 
 * 
 * In this problem/tutorial exercise, you will develop a program that 
 * 'constructs' a social network from given input, and then when given two 
 * names of peoples, finds out whether they can trust each other (in other words,
 * whether they are friends or have [a series] of friends between them). 
 * 
 * 
 * Input (to be read from standard input):
 *      - two integers N and M
 *              > the integer N such that 2<=N<=100, indicates the number of people in the
 *                 social network
 *              > the integer M such that 0<=M<=4950, indicates the number of friendships 
 *                 in the social network
 *      - on the next line will be N names separated by spaces. These are the names
 *          of people in the social network
 *      - on the next line will be 2 names separated by spaces, these are the names
 *          of people we will check to see if they can trust each other. You can assume
 *          these are distinct names/not the same person! 
 *      - the next M line(s) will each consist of two names, for example:
 *              Alice Bob
 *        which indicates Alice and Bob are friends
 * 
 * Output (to be printed to command line):
 *      - 'yes' to indicate that the two people asked about can trust each other
 *      - 'no' otherwise
 * 
 * Examples:
 * 
 *      - Example input:
 *              3 2
 *              Michael Jim Dwight
 *              Jim Michael
 *              Michael Dwight
 *              Michael Jim
 * 
 *      - Correct output:
 *              yes
 *        
 *        In the above example input, there are 3 people in the social network and
 *        there are 2 friendships in the social network. 
 *        From the second line we are told they are Michael, Jim, and Dwight. 
 *        On the third line, we are asked whether Jim and Michael have a series
 *        of friends between them. We are then told in the next line that
 *        Michael and Dwight are friends. We are then told in the next line that
 *        Michael and Jim are friends-- great! So Jim and Michael are friends meaning
 *        the output should be 'yes'. 
 * 
 *       =================================
 * 
 *     - Another example input:
 *              4 4
 *              Michael Jim Dwight Pam
 *              Michael Pam
 *              Michael Dwight
 *              Michael Jim
 *              Pam Jim
 *              Pam Dwight
 * 
 *      - Correct output:
 *              yes
 *        
 *        In the above example input, there are 3 people in the social network:
 *        Michael, Jim, Dwight, and Pam. We are asked whether Michael and Pam
 *        have a series of friends between them. Because we are told 
 *        Michael and Jim are friends and Pam and Jim are friends, then this means
 *        the output here should be 'yes'. 
 *
 *        =================================
 * 
 *      - Yet another example input:
 *              2 0
 *              Michael Toby
 *              Toby Michael
 * 
 *      - Correct output:
 *              no
 * 
 *        In the above example, there are 2 people in the social network, on the
 *        second line we are told they are Michael and Toby. On the third line, 
 *        we are told to search for whether Toby and Michael can trust each
 *        other/if they have a series of mutual friends between them. In this case
 *        there are no further lines, so the answer will be 'no'. 
 *         
 * 
 * Other notes:
 *  - Names do not contain spaces in them
 *  - The same friendship will not be twice (i.e if 'name1 name2' appears as a
 *      friendship in the input, then neither 'name1 name2' nor 'name2 name1' 
 *      will appear as a friendship in the rest of the input)
 *  - Names are only used once (i.e. if 'Mike' is given, then I won't give 
 *      you 'MIKE', 'mIke', 'MIke', etc.)
 * 
 * 
 * Further instructions:
 *  - I've already set up some code for you, fill 
 *  - The general outline is that you will model the social network as a graph:
 *      where the people/name are the vertices and the friendships are edges
 *  - This graph will be modelled in the struct called 'SocialGraph'
 *  - You will then perform depth first search on the graph to see whether
 *      the two people given have a path that connects them (i.e. they are either
 *      friends or have a series of mutual friends connecting them)
 * 
 * 
 * Extra exercises:
 *  - Working with unordered maps and strings is slow compared to vectors and
 *      integers. So speed up this program by 'encoding' the names of people as
 *      integers (hint: use a struct which converts encodes strings to integers)
 *      and then reimplement the program user vectors (or vectors of vectors) 
 *      instead of unordered maps 
 * - There are a lot of ways this program can be made faster, find them and 
 *      re-implement them!
 * - Why not also add some error checking for the input! Or perhaps edit the code
 *      so that it can handle if someone's name is spelt with either uppercase/lowercase.
 * 
 * 
 * Problem by created Michelle N for CPSC 457
 *      Goals:
 *      - Practice C/C++
 *          - structs, functions, strings, vectors, etc.
 *          - how to use a reference (cplusplus.com) (we have never talked about std::unordered_map before)
 * Any typos/corrections/etc, email: michelle.nguyen3@ucalgary.ca
 * 
 *********************************************/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>


struct SocialGraph{

    // for the adjacency list, it is an unordered map from a string to a vector of strings,
    // the string should be a person's name and the vector of strings is the people
    // that the person is (directly) friends with
    // http://www.cplusplus.com/reference/unordered_map/unordered_map/
    std::unordered_map<std::string, std::vector<std::string>> adjacencyList; 

    std::vector<std::string> listOfPeople;

    int64_t numberOfPeople; // i.e. number of vertices
    int64_t numberOfFriendships; // i.e. number of edges


    /**
     * name: addPerson
     * description: adds a person (vertice) to the graph
     * params: name1 - the person being added
     * return: void
     * */
    void addPerson(std::string name1){
        // TODO: (Your Task) add this person's name to the unordered map called adjacency_list
        // Also add this persons name to the listOfPeople
    }

    /**
     * name: addFriendship
     * description: adds a friendship (edge) to the graph
     * params: name1 name2 - the people (vertices) that the friendship (edge) connects, 
     *                  the edge between them is being added to the graph
     * return: void
     * */
    void addFriendship(std::string name1, std::string name2){
        // TODO: (Your Task) add the friendship to the unordered map-- remember to do this
        // for each person!
    }

    /**
     * name: areConnected
     * description: checks whether two people (vertices) in the graph are connected 
     *                  (i.e. they are connected by some amount of friendships/edges)
     * params: name1 name 2 - the people being checked if connected
     * return: bool, true if they are connected, false otherwise
     * */
    bool areConnected(std::string name1, std::string name2){
        // (Your Task) In this function, you will perform depth first 
        // search starting from name1 to see if they are connected in the graph 
        // to name2 (i.e. see if name1 is friends with
        // name2 or if they have a series of mutual friends)

        std::unordered_map<std::string, bool> checkedPerson;
        std::vector<std::string> stackOfPeopleToCheck;

        // TODO: (Your Task) Set up checkedPerson. That is, add the list of all people in 
        // the social network as a key in the unordered_map checkedPerson. 
        // Since we haven't traversed the graph yet / checked anyone yet, each 
        // bool should be set to false.


        // TODO: (Your Task) Add the direct friends of name1 to the stackOfPeopleToCheck
        // Hint: use the adjacency list! 


        // Traverse the graph / social network in a dfs manner!
        while(!stackOfPeopleToCheck.empty()){

            std::string personBeingChecked = stackOfPeopleToCheck.back();
            stackOfPeopleToCheck.pop_back();

            // TODO: (Your Task) check whether personBeingChecked has already been checked,
            // if they have continue (i.e. the vertice has already been visited)

            // TODO: (Your Task) if personBeingChecked is name2, 
            // then name1 and name2 are connected!
            // So return true to indicate that!

            // TODO: (Your Task) Otherwise, if this code is reached, 
            // add personBeingChecked's list of direct friends to the stack
            // and then mark personBeingChecked as checked in the unordered map
            // called checkedPerson


        }

        // In the case that the function has not returned yet, then it means
        // there are no friendships connecting name1 and name2, and so return
        // false (to say they are not connected)
        return false;

    }

    /**
     * name: reportTrust
     * description: reports to command line whether the people given can trust each other
     * params: name1 name 2 - the people being checked if can trust each other
     * return: void
     * */
    void reportTrust(std::string name1, std::string name2){
        if (areConnected(name1, name2)){
            std::cout << "yes" << std::endl;
        } else {
            std::cout << "no" << std::endl;
        }

    }

};


int main(){

    SocialGraph socialNetwork;

    // The first line tells us the number of people in the network
    std::cin >> socialNetwork.numberOfPeople;
    std::cin >> socialNetwork.numberOfFriendships;
    
    // The next line tells us the names of all the people in the network
    std::string person;
    for(int i=0; i < socialNetwork.numberOfPeople ; i++){
        std::cin >> person;
        socialNetwork.addPerson(person);
    }

    // The next line tells us the two people of interest / who we are checking
    // if they can trust each other
    std::string nameOfInterest1;
    std::string nameOfInterest2;

    std::cin >> nameOfInterest1;
    std::cin >> nameOfInterest2;

    // The next lines ask for the relationships
    std::string person2;
    while(std::cin >> person){
        std::cin >> person2;
        socialNetwork.addFriendship(person, person2);
    }
    
    // Report whether nameOfInterest1 and nameOfInterest2 can trust each other
    socialNetwork.reportTrust(nameOfInterest1, nameOfInterest2);

}

