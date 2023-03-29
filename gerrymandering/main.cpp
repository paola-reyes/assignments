/*--------------------------
    Paola Reyes
    1/30/23
    UIC CS 251, Wed 4pm Lab
    Prof. Adam Koehler
----------------------------    
Project 1 - Gerrymandering
  
Gerrymandering is when political parties restructure a state's voting districts in a way that will physically favor their party.
A common sign of gerrymandering is a voting district with an odd shape and is overwhelmingly sided towards one party.

In this project, we examine the mathematical definition of gerrymandering, which involves calculated a district's "wasted" votes.
A wasted vote is the total votes that were not required to reach the majority in a voting district. 
For example, if Illinois District 1 received 10 Democratic votes and 6 Republican votes, the wasted votes would be calculated like this:
Total votes = 10 + 6 = 16
Majority = 16 / 2 + 1 = 9
Democrats won using 9 votes = 10 - 9 = 1 wasted vote
Republicans lost = 6 wasted votes

Next, you calculate the efficiency factor. This is the positive difference between the two parties' total wasted votes across the state's districts 
divided by the total votes the state received, then written as a percentage. If the efficiency factor is >= 7%, the state is gerrymandered. 
Note: We cannot calcualte gerrymandering for state's with less than 3 voting districts, like Montana, North Dakota, Rhode Island, etc.
For example, if Illinois had a total of 500 cast votes, 50 wasted Democratic votes and 100 wasted Republican votes, we would calculate the efficiency factor as:

| 50 - 100 | / 500 * 100 = 10%
10% > 7% --> Illinois is gerrymandered

load():
This program reads in state voting data from 2 .txt files the user inputs using the load() function. There are two types of files we are dealing with: 
1) district_votes.txt, which is structured as State, District, Dem Votes, Rep Votes (example: Illinois,1,162268,59749,2,160337,43799)
2) eligible_voters.txt, which is structured as State, # of Voters (example: Illinois,162268)
Each file has roughly 50 lines, one for each US state. We store the data in a container called ourvector, which is an implementation of
a standard vector. We are using ourvector because we are on the class containers/abstract data types unit in class.

search():
Once we store the data, the user has the option to choose a state from the data we stored using search(). 
Once they select a state, they can print out statistics like:
stats(): Prints out if a state is gerrymandered, who lost, the wasted votes of each party, and number of eligible voters.
plot(): Prints out a diagram of each district's election results 
exit(): Close the program

A typical run will look like this:

Welcome to the Gerrymandering App!

Data loaded? No
State: N/A

Enter command: load districts_short_version.txt eligible_voters_short_version.txt

-----------------------------

Reading: districts_short.txt
...Montana...1 districts total
...California...53 districts total
...Connecticut...5 districts total
...Illinois...18 districts total
...Iowa...4 districts total
...Nebraska...3 districts total
...Rhode Island...2 districts total
...New Mexico...3 districts total
...Minnesota...8 districts total
...Colorado...7 districts total

Reading: eligible_voters_short.txt
...California...25278803 eligible voters
...Colorado...3978892 eligible voters
...Connecticut...2572337 eligible voters
...Illinois...8983758 eligible voters
...Iowa...2297129 eligible voters
...Minnesota...3972330 eligible voters
...Montana...803833 eligible voters
...Nebraska...1353558 eligible voters
...New Mexico...1459901 eligible voters
...Rhode Island...786111 eligible voters

Data loaded? Yes
State: N/A

Enter command: search illinois

-----------------------------

Data loaded? Yes
State: Illinois

Enter command: stats

-----------------------------

Gerrymandered: No
Wasted Democratic votes: 921521
Wasted Republican votes: 850785
Eligible voters: 8983758

Data loaded? Yes
State: Illinois

Enter command: plot

-----------------------------

District: 1
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDRRRRRRRRRRRRRRRRRRRRRRRRRRR
District: 2
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDRRRRRRRRRRRRRRRRRRRRRR
District: 3
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
District: 4
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDRRRRRRRRRRRRRRRRRRRRRR
District: 5
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
District: 6
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
District: 7
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDRRRRRRRRRRRRRRR
District: 8
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
District: 9
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
District: 10
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
District: 11
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
District: 12
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
District: 13
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
District: 14
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
District: 15
DDDDDDDDDDDDDDDDDDDDDDDDDRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
District: 16
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
District: 17
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
District: 18
DDDDDDDDDDDDDDDDDDDDDDDDDRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR

Data loaded? Yes
State: Illinois

Enter command: exit

-----------------------------
*/

#include <iostream>
#include "ourvector.h"      // vector-compatible implementation of vector<T>
#include <fstream>          // for file reading
#include <string>
#include <sstream>          // for traversing data in a string that's divided with commas
#include <cmath>            // for abs(), floor, and ceil()
using namespace std;


// A struct to combine the district votes (2D ourvector) and eligible Voters of each state. 
// This helps us store data by state considering the district/elegibility files are divided differently
struct State {
    string name = "\0";
    ourvector<ourvector<int>> districtVotes;
    int eligibleVoters = 0;
    int totalVotes = 0;
    int wastedDemVotes = 0;
    int wastedRepVotes = 0;
    string loser = "\0";
    double efficiencyFactor = 0;
    bool gerrymandered = false;      
};


// Helper function to readUserInput() and search(). Convert a string into all lower case letters so the user input isn't case senstitive
string lowerCase(string word) {    
    for (long unsigned int i = 0; i < word.size(); i++) {
        word.at(i) = tolower(word.at(i));
    }

    return word;
}


// Looks for a state object within the list of states (already alphabetized) using binary search. 
bool search(string userInput, ourvector<State> &statesList) {   
    userInput = lowerCase(userInput);
    string nameCopy = "\0";   // We're making a copy so we don't alter the value of thisState.name

    for (auto state : statesList) {
        nameCopy = lowerCase(state.name);
        if (userInput == nameCopy) {
            return true;
        }
    }
    
    return false;   // If the function hasn't stopped by now, the state wasn't found
} // end of search()


// Goes through the statesList and returns the object we are looking for. 
// Similar to search(). This function assumes the state already exists in the vector, which we will check beforehand using search()
State* getState(string userInput, ourvector<State> &statesList) {   
    userInput = lowerCase(userInput);
    string nameCopy = "\0";   // We're making a copy so we don't alter the value of thisState.name

    for (int i = 0; i < statesList.size(); i++) {
        nameCopy = lowerCase(statesList.at(i).name);
        if (userInput == nameCopy) {
            return &statesList.at(i);
        }
    }

    return 0;
} // end of getState()


// Finds the winning party of and calculates the wasted votes of all the state's districts
void wastedVotes(State &thisState) {
    int majority = 0;

    // Iterate through the list of districts
    for (auto &district : thisState.districtVotes) {
        majority = (district.at(0) + district.at(1)) / 2 + 1;   // Half + 1       

        // Wasted votes = all losing party votes + winning party votes not needed for majority
        // Democrat votes = district.at(0) and Republican votes = district.at(1)
        if (district.at(0) >= majority) {     // Democrats won
            thisState.wastedDemVotes += (district.at(0) - majority);
            thisState.wastedRepVotes += district.at(1);    
            thisState.loser = "Republicans";             
        }  

        if (district.at(1) >= majority) {     // Republicans won  
            thisState.wastedRepVotes += (district.at(1) - majority);
            thisState.wastedDemVotes += district.at(0);
            thisState.loser = "Democrats";
        }
    }
} // end of wastedVotes()


// Determines if a state is gerrymandered by calculating efficiency factor. 
// The efficiency factor is the percent difference between a state's wasted Democratic and wasted Republican votes divided by the total votes received
// If the difference is greater than 7%, the state is considered gerrymandered.
void gerrymandered(State &thisState) {
    // States with < 3 districts cannot be gerrymandered
    if (thisState.districtVotes.size() >= 3) {
        double efficiencyFactor = abs(thisState.wastedDemVotes - thisState.wastedRepVotes) / (double) thisState.totalVotes * 100;
        thisState.efficiencyFactor = efficiencyFactor;

        if (efficiencyFactor >= 7) {
            thisState.gerrymandered = true;
        }
        else {
            thisState.gerrymandered = false;
        }
    }
} // end of gerrymandered()


// Prints out a state's gerrymander status, wasted party votes, and number of eligible voters
void stats(State &thisState) {
    // Load the wasted votes and gerrymander calculators. thisState updates withing those functions
    wastedVotes(thisState);
    gerrymandered(thisState);

    if (thisState.gerrymandered) {
        cout << "Gerrymandered: Yes" << endl
             << "Gerrymandered against: " << thisState.loser << endl
             << "Efficiency Factor: " << thisState.efficiencyFactor << "%" << endl;
    }
    else {  // If it's not gerrymandered, we print less stats
        cout << "Gerrymandered: No" << endl;
    }

    cout << "Wasted Democratic votes: " << thisState.wastedDemVotes << endl
         << "Wasted Republican votes: " << thisState.wastedRepVotes << endl
         << "Eligible voters: " << thisState.eligibleVoters << endl << endl;
} // end of stats()


// This function prints out a visual of % Democrat and % Republican votes in total for an individual district
// It will print out 100 characters, where D is Democrats and R is republicans
// For example: %50 Dem & %50 Rep will look like this:
// DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
void plot(State &thisState) {
    int demPercent = 0;      
    int repPercent = 0;
    int districtNum = 1;

    for (auto &district : thisState.districtVotes) {
        // Calculate each party's percent of the total votes for that district
        // We will round our answers to make sure we they add up to 100/for ease of this assignment's test checks
        demPercent = floor(district.at(0) / (double) (district.at(0) + district.at(1)) * 100);  // round up
        repPercent = ceil(district.at(1) / (double) (district.at(0) + district.at(1)) * 100);   // round down

        cout << "District: " << districtNum++ << endl;

        for (int i = 0; i < demPercent; i++) {
            cout << "D";
        }
        
        for (int i = 0; i < repPercent; i++) {
            cout << "R";
        }

        cout << endl;
    }
    cout << endl;
} // end of plot()


// Helper function to load(). Reads and stores data from the first file
void loadDistrictsFile(ourvector<bool> &dataLoaded, const string districtsFile, ourvector<State> &statesList) {
    ifstream inFS(districtsFile);     // Open stream for the first file
    
    // If the file is unopenable, print an error message and end the function early
    if (!inFS.is_open()) {
        cout << "Invalid first file, try again." << endl << endl;
        dataLoaded.at(0) = false;   // dataLoaded.at(0) stores whether the 1st file was read successfully
        return ;                    // End function here
    }

    // We'll use 2 delimiters: 1) get each line separated by \n 2) get data that's divided by a comma
    // The data is organized State, District, Dem Votes, Rep Votes (for example: Illinois,1,162268,59749,2,160337,43799)
    string line = "\0";           // Data ending in a \n is buffered here  
    string district = "\0";       // These need to be buffered into strings for getline() to work but we'll be using them as ints   
    string demVotes = "\0";
    string repVotes = "\0";
    
    cout << "Reading: " << districtsFile << endl;

    while (getline(inFS, line, '\n')) {   // Take in each line of text
        // If the data is not workable, stop reading the file
        if (inFS.fail()) {
            dataLoaded.at(0) = false;
            return ;  //End function here
        }

        // Otherwise, make a new State object
        State newState;
        stringstream inSS(line);    // Will further read through each string that is full of commas
        string bin = "\0";            // If there's a duplicate state, we'll read the rest of the line here to skip that line

        string stateName = "\0";
        getline(inSS, stateName, ',');      // The first word of each line is a string and the rest are numbers

        // There should be no duplicate state entries
        if (search(stateName, statesList)) {
            getline(inFS, bin, '\n');   // We read in until \n to reach the next line
        }
        else { // Unique state
            // Read through the rest of the line. Data from here on is in groups of 3: District, Democratic Votes, and Republican Votes 
            // Note: the districtVotes ourvector starts off empty and needs to be push_backed into
            while (!inSS.eof()) {                       // Check if we've reached the end of the string
                newState.name = stateName;
                getline(inSS, district, ',');           
                getline(inSS, demVotes, ',');
                getline(inSS, repVotes, ',');

                ourvector<int> temp;                    // Create a new ourvector that will be push_backed as an element in newState's ourvector<ourvector<int>>
                temp.push_back(stoi(demVotes));         // Convert strings to integers using stoi() and push them into the temp
                temp.push_back(stoi(repVotes));
                newState.totalVotes += stoi(demVotes) + stoi(repVotes); // Update total votes received for that state
                newState.districtVotes.push_back(temp); // Push temp into newState's ourvector<ourvector<int>>
            }

            statesList.push_back(newState);             // Add this state to the list of states
            cout << "..." << newState.name << "..." << newState.districtVotes.size() << " districts total" << endl;
        }
    }

    cout << endl;
    dataLoaded.at(0) = true;
    inFS.close();     // We're done reading
} // end of loadDistrictsFile()


// Helper function to load(). Reads and stores data from the second file
void loadEligibileVotersFile(ourvector<bool> &dataLoaded, const string eligibleVotersFile, ourvector<State> &statesList) {
    ifstream inFS(eligibleVotersFile);
    
    // If the file is unopenable, print an error message and end the function early. 
    if (!inFS.is_open()) {
        cout << "Invalid second file, try again." << endl << endl;
        dataLoaded.at(1) = false;       // dataLoaded.at(1) stores whether the 2nd file was read successfully
        return ;                        // End function here
    }

    // We'll use 2 delimiters: 1) get each line separated by \n 2) get data that's divided by a comma
    // The data is organized as State, # of Voters (example: Illinois,162268)
    string data = "\0";           // Data ending in a \n is buffered here  
    string stateName = "\0";
    string numVoters = "\0";      // Needs to be buffered into string for getline() to work but it'll be an int
    State *tempState;

    cout << "Reading: " << eligibleVotersFile << endl;

    while (getline(inFS, data, '\n')) {   // Take in each line of text
        // If the data is not workable, stop reading the file
        if (inFS.fail()) {
            dataLoaded.at(1) = false;
            return ;    // End function here
        }

        stringstream inSS(data);    // Will further read through each string that is full of commas

        // Read through the rest of the line. Data from here on is in groups of 2: State and Eligible Votes 
        while (!inSS.eof()) {                       // Check if we've reached the end of the string
            ourvector<int> votes;                   // Create a new ourvector that will be push_backed as an item into the newState ourvector<ourvector<int>>
            getline(inSS, stateName, ',');          
            getline(inSS, numVoters, ',');   
            
            // We'll add this data to the states objects we made with the districts file
            if (search(stateName, statesList)) {
                tempState = getState(stateName, statesList);
                (*tempState).eligibleVoters = stoi(numVoters);    // Change voters to an int and add it to the thisState's data member
                cout << "..." << (*tempState).name << "..." << (*tempState).eligibleVoters << " eligible voters" << endl;
            }
        }
    }

    cout << endl;
    dataLoaded.at(1) = true;
    inFS.close();    
} // end of loadEligibleVotersFile()



// This calls the helper functions that read the 2 files and prints error messages.
void load(ourvector<bool> &dataLoaded, ourvector<State> &statesList) {
    // You can only read in 1 set of files per program run
    // dataLoaded.at(0) stores whether the 1st file was read successfully and dataLoaded.at(1) is for the 2nd file
    if (dataLoaded.at(0) && dataLoaded.at(1)) {     // If both files were read successfully
        // Takes in the rest of the input to leave the buffer empty          
        string bin = "\0";        
        getline(cin, bin);  
        cout << "Already read data in, exit and start over." << endl << endl;
    }
    else {
        // Read in two strings: districts file and eligible_voters file
        string districtsFile = "\0";
        string eligibleVotersFile = "\0";

        cin >> districtsFile >> eligibleVotersFile;
        loadDistrictsFile(dataLoaded, districtsFile, statesList);

        // We can only read the second file if the first file was read successfully
        if (dataLoaded.at(0)) {
            loadEligibileVotersFile(dataLoaded, eligibleVotersFile, statesList);
        }
    }
} // end of load()


// Reads in the user's input and carrys out the commands: load(), search(), stats(), plot(), and exit()
void readUserInput(ourvector<bool> &dataLoaded, bool &stateFound, string &stateName, State &thisState, ourvector<State> &statesList, bool &endProgram) {
    string command = "\0";
    cin >> command;
    command = lowerCase(command);     // Make user input lowercase so it isn't case sentitive

    cout << endl << "-----------------------------" << endl << endl;

    if (command == "exit") {    // Close the program
        endProgram = true;
    }
    else if (command == "load") {   // Read two .txt files and store the data in ourvector/State object
        load(dataLoaded, statesList);
    }
    // You can only call search() if the first file was read successfully
    // We don't have to check the 2nd file because as long as we have read the 1st file successfully we can work partially with that
    else if (!dataLoaded.at(0) && command == "search") {
        string bin = "\0";
        getline(cin, bin, '\n');
        cout << "No data loaded, please load data first." << endl << endl;  // Cannot make a command if we don't have data. 
    }
    // You can't call stats() or plot() without reading the 2nd file because we need the eligible voters data
    else if (!dataLoaded.at(1) && (command == "stats" || command == "plot")) {
        // Cannot make a command if we don't have data. 
        cout << "No data loaded, please load data first." << endl << endl;
    }
    // Checks if a certain state has been read from the files
    else if (command == "search") {
        string input = "\0";
        getline(cin, input);          // Use getline() for states with multiple words, like New York
        input.erase(0, 1);            // There is an extra space in the buffer, so remove it
        stateFound = search(input, statesList);

        if (stateFound) {
            thisState = *getState(input, statesList);   
            stateName = thisState.name;  
        }
        else {
            cout << "State does not exist, search again." << endl; 
        }
    }
    // You cannot look for state data if you have not chosen a state
    else if (!stateFound && (command == "stats" || command == "plot")) {
        // User has to choose a state before printing data
        cout << "No state indicated, please search for state first." << endl << endl;
    }
    // Prints a state's gerrymander status, wasted party votes, and number of eligible voters
    else if (command == "stats") {
        stats(thisState);
    }
    // Prints out a diagram of the state's vote results
    else if (command == "plot") {
        plot(thisState);
    }
    else {
        cout << "Invalid input, please try again. = " << command << "." << endl << endl;   
    }
}


int main() {
    State thisState;
    ourvector<State> statesList;
    string stateName = "\0";
    bool stateFound = false;
    bool endProgram = false;    // The condition for our while loop

    ourvector<bool> dataLoaded;     // Keeps track of whether each individual file was read successfully
    dataLoaded.push_back(false);    // Represents districts.txt
    dataLoaded.push_back(false);    // Represents eligible_voters.txt

    cout << "Welcome to the Gerrymandering App!" << endl << endl;

    // Repeat forever or until user exits program
    while (!endProgram) {
        // Data is considered "loaded" if both the files were read successfully
        // We're checking index [1] because the 2nd file is only read if the 1st file was read successfully
        if (dataLoaded[1]) {   
            cout << "Data loaded? Yes" << endl;
        }
        else {
            cout << "Data loaded? No" << endl;
        }
        
        if (stateFound) {
            cout << "State: " << stateName << endl << endl;
        }
        else {
            cout << "State: N/A" << endl << endl;
        }

        cout << "Enter command: ";
        readUserInput(dataLoaded, stateFound, stateName, thisState, statesList, endProgram);
    }

    return 0;
}