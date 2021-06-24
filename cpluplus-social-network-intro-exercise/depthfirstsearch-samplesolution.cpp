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
 *          of people we will check to see if they can trust each other.  You can assume
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
 * Extra exercise:
 *  - Working with unordered maps and strings is slow compared to vectors and
 *      integers. So speed up this program by 'encoding' the names of people as
 *      integers (hint: use a struct which converts encodes strings to integers)
 *      and then reimplement the program user vectors (or vectors of vectors) 
 *      instead of unordered maps 
 * - There are a lot of ways this program can be made faster, find them and re-implement them!
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


    void addPerson(std::string name1){
        // Task: add this person's name to the unordered map called adjacency_list
        // Also add this persons name to the listOfPeople
        std::vector<std::string> theirListOfFriends;
        adjacencyList.emplace(name1, theirListOfFriends);
        listOfPeople.push_back(name1);
    }

    void addFriendship(std::string name1, std::string name2){
        // Task: add the friendship to the unordered map-- remember to do this
        // for each person!
        adjacencyList.at(name1).push_back(name2);
        adjacencyList.at(name2).push_back(name1);
    }

    bool areConnected(std::string name1, std::string name2){
        // Task: perform depth first search starting from name1 to see if
        // they are connected in the graph to name2 (i.e. see if name1 is friends with
        // name2 or if they have a series of mutual friends)

        std::unordered_map<std::string, bool> checkedPerson;
        std::vector<std::string> stackOfPeopleToCheck;

        // Set up checkedPerson. Since we haven't traversed the graph yet / checked
        // anyone yet, it is all false. 
        for(auto person : listOfPeople){
            checkedPerson.emplace(person, false);
        }

        // Add the direct friends of name1 to the stack 
        for(auto aFriend : adjacencyList.at(name1)){
            stackOfPeopleToCheck.push_back(aFriend);
        }

        // Check the people in the stack in dfs manner and see if they are name2
        while(!stackOfPeopleToCheck.empty()){

            std::string personBeingChecked = stackOfPeopleToCheck.back();
            stackOfPeopleToCheck.pop_back();

            // check whether the person being checked has already been checked,
            // then continue on to the next person
            if (checkedPerson.at(personBeingChecked)) continue;

            // if the person being checked is name2, then name1 and name2 are connected!
            // so return true to indicate that!
            if (personBeingChecked.compare(name2) == 0) return true;

            // so if they're not the person, add their list of direct friends to the stack
            // and then mark the person as checked
            for(auto aFriend : adjacencyList.at(personBeingChecked)){
                stackOfPeopleToCheck.push_back(aFriend);
            }
            checkedPerson.at(personBeingChecked) = true;

        }

        // in the case that the function has not returned yet, then it means
        // there are no friendships connecting name1 and name2, and so return
        // false (to say they are not connected)
        return false;

    }

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

    // The next lines ask 
    std::string person2;
    while(std::cin >> person){
        std::cin >> person2;
        socialNetwork.addFriendship(person, person2);
    }
    
    // Report whether nameOfInterest1 and nameOfInterest2 can trust each other
    socialNetwork.reportTrust(nameOfInterest1, nameOfInterest2);

}

