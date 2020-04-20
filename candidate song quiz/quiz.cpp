/* -------------------------------------------------------- 
  Class: Program #2 for CS 141, Fall 2019
  Lab: Tues 10am
  TA Aditi
  System: Codio
  Author: Paola Reyes

  prog2RallySongs.cpp
  Read political candidate's favorite song lyrics from a file.
  Choose random lines and see if the reader can identify the candidate.

  This was inspired by the New York Times article:
    https://www.nytimes.com/interactive/2019/08/19/us/politics/presidential-campaign-songs-playlists.html
    which describes the different songs played at political rallies for
    different 2020 presidential candidates.
 ----------------------------------------------------------*/

#include <iostream>
#include <cctype>       // For the letter checking functions
#include <fstream>      // For file input
#include <iomanip>      // For setw
#include <ctime>        // For random numbers
#include <cstdlib>      // For exit and abs
using namespace std;


//----------------------------------------------------------------------------------------------
// Determine if a line has lyrics, meaning it doesn't start with '#', a number, or a blank
bool isValidLyric( string line ) {
    return ( (line[0] != '#') && (line != "") && (!isdigit(line[0])) );
}


//----------------------------------------------------------------------------------------------
// Retrive one random valid line from a given candidate's file 
void getRandomLine( string candidateName ) {  
    ifstream inputFileStream;        // Declare the input file stream
    
    // Open input file and verify that file was found
    inputFileStream.open( candidateName.c_str() );
    if( !inputFileStream.is_open()) {
        cout << "Could not find input file " << candidateName << "  Exiting..." << endl;
        exit( -1);
    }
    
    // Read the number on the first line of the input file, which indicates how many subsequent
    // lines there are in the file.
    int numberOfLinesInFile = 0;
    inputFileStream >> numberOfLinesInFile;   
    int lineNumber = rand()%numberOfLinesInFile;
    
    // Read one line at a time, repeating until we get to the designated line.  If the designated
    // line is blank or is a comment line starting with '#', then skip it and go on to the next.
    string line;
    int currentLine = 1;
    while( getline(inputFileStream, line) ) {
        if( currentLine == lineNumber ) {
            if ( isValidLyric(line) ) {       
                cout << line << endl;
            }
            else {
                lineNumber ++;
            }
        }

        currentLine ++;
    } //end while( getLine...
    
    inputFileStream.close();    // Close the input file.
}


//----------------------------------------------------------------------------------------------
// Gets a new random line some number of times based on the user's numLinesToDisplay input 
void getMultipleLines( string candidateName, int numLinesToDisplay ) {    
    for (int i = 0; i < numLinesToDisplay; i++) {
        getRandomLine(candidateName);
    }
}


//----------------------------------------------------------------------------------------------
// Calculate percent score. If the totalAttempts is 0, return 0 so as not to divide by zero
int percentage(double numCorrect, double totalAttempts) {
    if ( totalAttempts != 0 ) {
        return (int) ( (numCorrect / totalAttempts) * 100 );
    }
    else {
        return 0;
    }
}


//----------------------------------------------------------------------------------------------
int main() {   
    srand(1);     // set up for rand()
    
    // Count total number of times user opened the quiz in Option #4. Also tracks the number of
    // examples the user guessed correctly
    double numCorrect = 0;
    double totalAttempts = 0;
    
    int numLinesToDisplay = 3;  // How many lines of lyrics program should display. Initially 3 but user can change value
    int userChoice;    // User main menu option input 
    int userGuess;     // User answer input for the quiz problems in Option #4

	// Display which program this is and display menu options to select program output to be displayed
    cout << endl
		 << "----  Program 2: Rally Songs  ----\n"
		 << "Select from the following:\n"
		 << "   1. Set number of lines to display\n"
		 << "   2. Get random lines from Trump.txt\n"
		 << "   3. Get random lines from Warren.txt\n"
		 << "   4. Rally song quiz\n"
		 << "   5. Exit the program\n"
		 << "Your choice --> ";
    cin >> userChoice;
    cout << endl;

    // Go through main() until the user input is 5, which closes the program
    while (userChoice != 5) {
        switch(userChoice) {
            // User input of 1 changes value of numLinesToDisplay
            case 1:
                cout << "Enter the number of lines you want to display -> ";
                cin >> numLinesToDisplay;
                break;
            // User input of 2 displays some number lyrics lines from "Trump.txt" 
            case 2:
                getMultipleLines("Trump.txt", numLinesToDisplay);
                break;
            // User input of 3 displays some number lyrics lines from "Warren.txt" 
            case 3:
                getMultipleLines("Warren.txt", numLinesToDisplay);
                break;
            // User input of 4 chooses a random candidate and displays some number of lyric lines. 
            // The user will be asked to guess which candidate that song
            case 4:
                totalAttempts += 1;                // update totalAttempts everytime Option #4 is run
                int randomCandidate = rand() % 2;  // choose a random number 0 (Trump) or 1 (Warren) for a random candidate
                string correctAnswer;
            
                // Based on the random candidate, display some number of lines from their file
                // The chosen candidate's name is the correct answer for the quiz problem
                if (randomCandidate == 0) {
                    getMultipleLines("Trump.txt", numLinesToDisplay);
                    correctAnswer = "Trump";
                }
                else if (randomCandidate == 1) {
                    getMultipleLines("Warren.txt", numLinesToDisplay);
                    correctAnswer = "Warren";
                }
                
                // Display guess options and ask for user's guess input
                cout << endl << "Enter 1 for Trump, 2 for Warren: ";
                cin >> userGuess;
                
                // Check if user's guess is correct and display a "Correct!" statement with their updated score
                if ( (userGuess == 1 && correctAnswer == "Trump") || (userGuess == 2 && correctAnswer == "Warren") ) {
                    numCorrect += 1;
                    cout << endl 
                         <<"Correct! You got " << numCorrect << " out of " << totalAttempts 
                         << ", which is " << percentage(numCorrect, totalAttempts) << "%" 
                         << endl;
                }
                // If user's guess is wrong and display a "Wrong!" statement and their updated score
                else {
                    cout << endl 
                         <<"Wrong! You got " << numCorrect << " out of " << totalAttempts 
                         << ", which is " << percentage(numCorrect, totalAttempts) << "%" 
                         << endl;
                }  
                break;
        } //end of switch statement

        // Display option menu again and ask for user input.
        // Display which program this is and display menu options to select program output to be displayed
        cout << endl
             << "----  Program 2: Rally Songs  ----\n"
             << "Select from the following:\n"
             << "   1. Set number of lines to display\n"
             << "   2. Get random lines from Trump.txt\n"
             << "   3. Get random lines from Warren.txt\n"
             << "   4. Rally song quiz\n"
             << "   5. Exit the program\n"
             << "Your choice --> ";
        cin >> userChoice;
        cout << endl;
    } // end of while loop
        
    // User input of 5 prints out final score and ends program
    if (userChoice == 5) {
        cout << "You got " << numCorrect << " out of " << totalAttempts 
             << ", which is " << percentage(numCorrect, totalAttempts) << "%" 
             << endl;
        exit(-1);
    }

    return 0;
}//end main()
