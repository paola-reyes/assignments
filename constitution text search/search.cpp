/* ----------------------------------------------------------- 
  Program 4: Two Codes
  
  Class: CS 141, Spring 2020.  Tues 1pm lab
  System: Zybooks
  Author: Paola Reyes
-----------------------------------------------------------*/
#include <iostream>   // For input and output
#include <fstream>    // For file input and output
#include <vector>     // For vector string arrays
#include <cstring>    // For C string arrays
using namespace std;

//------------------------------------------------------------------------------------------------------
// Change all letters in a string to lower case
void lowerCase( string &input) {
  int length = input.size();    // Length of string

  for ( int i = 0; i < length; i++) {  // Iterate through string and change each char
    input[i] = tolower(input[i]);  
  }
} // end lowerCase()


//------------------------------------------------------------------------------------------------------
// Open the file and add the contents to a string vector
void readFile( vector<string> &text) {
  ifstream inStream;                                  // Declare input stream
  inStream.open("ConstitutionAndBillOfRights.txt");   // Open constitution file to read it

  // Print out error message and end program if the file is not found
  if ( !inStream.is_open()) {
    cout << "Could not find ConstitutionAndBillOfRights.txt.  Exiting..." << endl;
    exit(-1);   // Close program
  }

  string line;                            // Stores a line read from the text
  while ( getline( inStream, line)) {     // Reads text from the file line by line 
    if ( line.length() > 1) {             // Ignore blank lines with length < 1
      text.push_back( line);              // Adds each line to text vector
    }
  }

  inStream.close();  // Close file after it is read
} // end readFile()


//------------------------------------------------------------------------------------------------------
// Display the line where the user's chosen phrase appears. This function covers both 'W' and 'A' from 
// the menu options
void findPhrase(const vector<string> &text,    // String array with text
                int &lineNumber,               // Line number that will be updated 
                string phrase,                 // Phrase function will search for
                bool allOccurrences) {         // Whether or not to print all occurrences of phrase
  
  string line;  // Stores a line from the vector  
  int length = text.size();  // Length of vector
  
  for (int i = 0; i < length; i++) {  // Loop through each string in vector
    line = text.at(i);      // Holds temporary version of each line 
    lowerCase( line);       // Convert each element to all lower case for comparison
 
    // find() doesn't return string::npos only when the phrase is found in the string
    if ( line.find( phrase) != string::npos) {
      cout << "Line " << i << ":" << endl    // Print out line number and line text
           << text.at(i) << endl;

      lineNumber = i;       // Update lineNumber to the index of that line
      cout << endl;

      // If the user didn't choose all occurrences, end the loop here. Otherwise, continue looking 
      // for more occurrences of the phrase
      if ( !allOccurrences) {
        break;   
      } 

    } // end outer if-statement
  } // end for loop 
} // end findPhrase


//------------------------------------------------------------------------------------------------------
// Print out line that preceeds the line that was recently used
void previousLine( const vector<string> &text, int &lineNumber) {
  
  // If the line has nothing before it, print out a message
  if ( lineNumber == 0) {
    cout << "There is no previous file contents." << endl;
  }
  else {
    cout << "Line " << lineNumber - 1 << ":" << endl   // Print out line number and line text
      << text.at( lineNumber - 1) << endl;
    lineNumber = lineNumber - 1;    // Update lineNumber
  }

} // end previousLine()


//------------------------------------------------------------------------------------------------------
// Print out line that comes after the line that was recently used
void followingLine( const vector<string> &text, int &lineNumber) {
  int lastLine = text.size() - 1;   // Index of the last line in the vector

  // If the line has nothing after it, print out a message
  if ( lineNumber == lastLine) {
    cout << "There is no following file contents." << endl; 
  }
  else {
    cout << "Line " << lineNumber + 1 << ":" << endl   // Print out line number and line text
      << text.at( lineNumber + 1) << endl;
    lineNumber = lineNumber + 1;   // Update lineNumber
  }
} // end previousLine()


//------------------------------------------------------------------------------------------------------
// Print out the second menu that has more options and take in user's new input
void extendedMenu( char &menuOption) {
  cout << endl 
       << "Select from the following choices: " << endl
       << " W  Enter word or phrase to find, and display enclosing text" << endl
       << " P  Display previous text " << endl
       << " F  Display following text" << endl
       << " A  Display all occurrences of found word or phrase" << endl
       << " X  Exit program " << endl
       << "Your choice: ";
  cin >> menuOption;
} // end extendedMenu()


//------------------------------------------------------------------------------------------------------
int main() {
  char menuOption;                  // Stores user's input
  vector<string> text;              // Vector holds text lines
  string phrase;                    // Phrase that program will search for
  char returnChar;                  // Holds extra newline from user input
  int lineNumber = 0;               // Index of each phrase
  bool allOccurrences = false;      // Whether or not to print all occurrences of phrase

  // Display initial set of instructions and prompt user input
  cout << "Select from the following choices: " << endl
       << " W  Enter word or phrase to find, and display enclosing text" << endl
       << " X  Exit program " << endl
       << "Your choice: ";
  cin >> menuOption;

  menuOption = tolower(menuOption);  // Convert user input to lowercase
  readFile(text);                    // Open file and transfer contents to the text vector

  while (true) {      // Continue loop until the user's 'X' input breaks it
    switch (menuOption) {
    case 'w':   // Search for word and provide expanded menu options
      cout << "Enter word or phrase: ";     // Prompt user for input
      returnChar = cin.get();               // Terminate extra \n from input
      getline(cin, phrase);                 // Take string and stores it in phrase vector
      lowerCase( phrase);                   // Change input to have all lower case letters 
      cout << endl;

      findPhrase( text, lineNumber, phrase, allOccurrences);
      extendedMenu( menuOption);
      continue;    // Go back to the beginning of the loop

    case 'p':
      previousLine( text, lineNumber);
      extendedMenu( menuOption);
      continue;   // Go back to the beginning of the loop
    
    case 'f':
      followingLine( text, lineNumber);
      extendedMenu( menuOption);
      continue;   // Go back to the beginning of the loop
    
    case 'a':
      allOccurrences = true;
      findPhrase( text, lineNumber, phrase, allOccurrences);

      allOccurrences = false;    // Set all occurrences back to false for the next run
      extendedMenu( menuOption);
      continue;   // Go back to the beginning of the loop

    case 'x':  // Exit program
      cout << "Exiting program." << endl;
      exit(1);
      break;

    default:
      extendedMenu( menuOption);
      continue;
    }
  }

  return 0;
} // end main()
