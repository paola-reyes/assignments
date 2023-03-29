//  Project 1 Starter Code - DNA Profiling
//  TODO:  Put your header info here.  Update line above.

#include <iostream>
#include <map>          // For maps
#include <fstream>      // For ifstream
#include <sstream>      // For getline(string)
#include <string.h>     // For getline(file) & stoi()
#include "ourvector.h"
using namespace std;


struct patient {
    ourvector<char> name;
    ourvector<ourvector<char>> dna;
};

ourvector<patient> patientsList;


void printVector(ourvector<char> list) {
    for (char letter : list) {
        cout << letter;
    }
    cout << endl;
}


// We cannot push a string to ourvector<>, so we push_back() letter by letter
void pushString(ourvector<char> &patientData, string data) {
    for (char letter : data) {
        patientData.push_back(letter);
    }
}


// Adds a number of STR's to the DNA sequence
void numToDNA(ourvector<char> &dna, int num, ourvector<char> str) {
    for (int i = 0; i < num; i++) {
        for (char unit : str) {
            dna.push_back(unit);
        }
    }
} // end of numToDNA()


// Read a file and evaluate the patient and their DNA sequence
void load_db(string fileName) {
    // Make a stream to read the given file + make a buffer for the file data
    ifstream inFS;
    inFS.open(fileName);
    string fileInput = "\0";

    // Print an error if the file cannot be opened, then exit the program
    if (!inFS.is_open()) {
        cout << "Error: unable to open '" << fileName << "'" <<  endl;
        exit(0);
    }

    // Make a stream to read the individual lines + make a buffer for the patient's data
    stringstream inSS(fileInput);
    string lineInput = "\0";
    bool firstLine = true;          // The first line details what the file data means + the order it should be in
    bool readingName = true;        // If we're reading the very first word in the line, which is the patient's name
    int i = 0;                      // Counter that keeps track of which STR we need next

    // Read in the file line by line
    while (getline(inFS, fileInput)) {
        struct patient thisPatient;

        // Read in each line word by word. The words are separated by apostrophes
        while (getline(inSS, lineInput, ',')) {
            // Patient's name is stored in its own ourvector<>
            if (readingName) {          
                pushString(thisPatient.name, lineInput);
                printVector(thisPatient.name);
                // readingName = false;        // We are now moving on to the STR data, which fileName stores as numbers
            }
            // // The remaining words of first line are the STR sequence. We don't neet to convert from an int
            // else if (firstLine && !readingName) {   
            //     pushString(thisPatient.dna.at(1), lineInput);   // Pushed into an ourvector of ourvector<char>'s. Similar to an ourvector<string>
            //     printVector(thisPatient.dna.at(1));
            // }
            // // The rest of the lines (name exlcuded) have a list of numbers. This is how many copies of each STR the patient has. Each number has it's corresponding STR
            // else if (!firstLine && !readingName) {
            //     printVector(thisPatient.dna.at(i));
            //     numToDNA(thisPatient.dna.at(i), stoi(lineInput), patientsList.at(i).dna.at(i));
            // }
        }

        patientsList.push_back(thisPatient);    // Add this patient to the ourvector<> list of patient structs
        readingName = true;                     // Will start the next line by reading a name
    }

    inFS.close();      // Close file stream
}

// (㇏(•̀ᵥᵥ•́)ノ)
int main() {
    load_db("small.txt");
    
    return 0;
}
