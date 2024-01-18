/* Prog3Vigenere.cpp
  Class: CS 141, Spring 2020. Tues 1pm lab
  System: Zybooks
  Author: Adelina Carr & Paola Reyes

  Encode/Decode phrases using Vigenere cipher. 
*/
//-------------------------------------------------------------------------------------
#include <iostream>   // For Input and Output
#include <fstream>    // For file input and output
#include <cctype>     // Allows using the tolower() function
#include <cstring>    // For C string character arrays
using namespace std;

// Global constants
const int DICTIONARY_SIZE = 21876;   // Set the dictionary size to a number large enough to cover the entire dictionary
const int WORD_SIZE = 81;            // Set the word size to a number large enough to store even the largest word 


//-------------------------------------------------------------------------------------
// Opens the dicionary file and stores the words in the dicionary array found in main
void readDictionary( char dictionary[DICTIONARY_SIZE][WORD_SIZE])
{
  // Open a file for reading
  ifstream inStream;         // Declare an input stream 
  inStream.open("dictionary.txt");    // Open the dictionary file to read it

  // Print out error message and end program if the file is not found
  if ( !inStream.is_open()) {
    cout << "Could not find dictionary.txt.  Exiting..." << endl;
    exit(-1);   // Close program
  }

  char theWord[WORD_SIZE];       // Declare input space to be clearly larger than largest word
  int i = 0;
  // Continously take out a word from the dictionary
  while (inStream >> theWord) {

    // Add word to global dictionary array
    for (int j = 0; j < WORD_SIZE; ++j) {
      // Make every letter of the current dictionary word lowercase & add it to the dictionary array
      dictionary[i][j] = tolower( theWord[j]); 
    }

    i++;
  } // end while loop
  
  inStream.close();   // Close the file once it has been completely read
} // end readDictionary()


//-------------------------------------------------------------------------------------
// Checks if a word the user gives is in the dictionary and thus an English word
bool isInDictionary(char theWord[WORD_SIZE], char dictionary[DICTIONARY_SIZE][WORD_SIZE]) {  // Open the dictionary for populating the array

  // Set binary search variables
  int high = DICTIONARY_SIZE - 1;   // Current highest index 
  int low = 0;                      // Current lowest index
  int mid = (low + high) / 2;       // Current middle index
  int found = 0;                    // Stores strcpm() value

  while (low <= high)
  {
    mid = (high + low) / 2;
    found = strcmp(theWord, dictionary[mid]);   // Update found for the next word

    //Check if the words match.
    if (found == 0)// strcmp() makes found = 0 if they are equal
    {
      return true;        // Return true and end function word was found
    }
    else if (found > 0)   // strcmp() makes found a non-zero int if they are not equal
    {
      low = mid + 1;
    }
    else
    {
      high = mid - 1;
    }
  }

  return false;
} // end isInDictionary()


//-------------------------------------------------------------------------------------
// Converts all the letters in the user's text phrase to lowercase. This prepares it for encoding
// or decoding later on
void cleanInput( char *userText)
{
  //Convert the input word to all lowercase.
  for (int i = 0; i < WORD_SIZE; ++i)
  {
    if ( userText[i] == ' ') // Is the element a space?
    { 
      continue;        // Skip this iteration.
    }
    else if ( userText[i] == '\n')   //Is the element a new line character?
    {
      userText[i] = '\0';  // Set the newline character to the null character.
      break;    // We are done at this point, this SHOULD be the end of the phrase.
    }
    else if (userText[i] == '\0')  // Is the element a null character?
    {
      break;  // We are done at this point, this is the end of the phrase.
    }
    else {  // All other conditions, then just convert to lower case.
      userText[i] = tolower( userText[i]);
    }
  } // end for loop
} // end cleanInput()


//-------------------------------------------------------------------------------------
// Finds the number of words in decoded text that are in the dictionary file
int numDictionaryWords( char text[], char inputKey[], char dictionary[DICTIONARY_SIZE][WORD_SIZE]) {
  int numWordsFound = 0;   // Number of words in decoded phrase that are also in the dictionary
  char word[WORD_SIZE] = {0};     // A word from the plainText. Will be checked later on to see if
                                // it is in the dictionary file

  int wordIndex = 0;       // Current index of a char in word

  // Go through the entire array including the null character. Convert strlen calculation to 
  // an int so the compiler can compare int i to an int instead of a size_t
  for ( int i = 0; i < int( strlen(text) + 1); i++) {

    // The end of a word is marked by a space or, in the case of the very last word, a null char
    if ( text[i] == ' ' || text[i] == '\0') {

      // Check if the complete word is in the dictionary and if it has at least 3 chars
      if ( isInDictionary( word, dictionary) && strlen( word) >= 3) {      
        numWordsFound++;   // Increment numWordsFound
      }
  
      wordIndex = 0;       // Set the index to 0 to prepare for the next word

      // Empty the entire word array to prepare for the next word
      for ( int j = 0; word[j] != '\0'; j++) {
        word[j] = '\0';    // Set each current item to null
      }
    }
    else {       // For all the intermediate letters between spaces/ before the null
      word[wordIndex] = text[i];    // Add the current text letter to the word array
      wordIndex++;        // Increment for the next index of word
    }
  } // end for loop

  return numWordsFound;
} // end numDictionaryWords()


//-------------------------------------------------------------------------------------
// Shifts the letter of each word in the user's chosen text to encode it using a key word
void encodeText( char *inputText, char *inputKey) {
  int offset = 0;      // The amount we will shift each letter by when its encoded
  int keyIndex = 0;    // Index for the each letter in inputKey

  // Create an array for the final encoded word and inputKey cycle. Initializing the array to zero
  // prevents unwanted outputs.
  char cypherText[WORD_SIZE] = {0};      // Encoded version of the user's chosen text
  char keyCycle[WORD_SIZE] = {0};        // Shows how the key word cycles throughout the length of inputWord

  // Loop through the array until you hit null 
  for ( int i = 0; inputText[i] != '\0'; ++i) {    

    // If the inputKey element is a null, then reset the keyIndex to go back to the beginning.
    if ( inputKey[ keyIndex] == '\0') {  
      keyIndex = 0;     // Reset the key index back to the first element     
    }

    offset = inputKey[ keyIndex] - 'a';   // Update the offset. It is the number of letters between
                                            // the current letter of inputKey and 'a'
    keyCycle[i] = inputKey[ keyIndex];    // Add the current inputKey letter to keyCycle
    ++keyIndex;     // Increment the key index for the next letter in inputKey.

    if ( !isalpha(inputText[i])) {   // If element is a space, add a space to the encoded phrase
      cypherText[i] = inputText[i];       
    }     
    else { 
      
      // If shifting the inputText letter brings it out of alphabet bounds, or greater than ASCII
      // 'z', then loop it back to 'a'
      if ( inputText[i] + offset > 'z') { 
        // Subtract the encoded letter by 26 to make it a valid alphabet letter
        cypherText[i] = inputText[i] + offset - 26;   // Add encoded letter to cypherText
      }
      else {
        cypherText[i] = inputText[i] + offset;    // Add encoded letter to cypherText
      } //end inner if-else statement
    } // end outer if-else statement
  } // end for loop

  // Print out the keyCycle, inputText, and cypherText char arrays
  cout << keyCycle << endl;
  cout << inputText << endl;
  cout << cypherText << endl;
} // end encodeWord()


//-------------------------------------------------------------------------------------
// Shifts the letter of each word in the user's chosen text to decode it using a key word. 
void decodeText(char* encodedText, char* inputKey, char* plainText)
{
  int keyIndex = 0;             // Index for the each letter in inputKey
  int offset = 0;               // The amount we will shift each letter by when its encoded
   
  // Loop rhrough the array until you hit null 
  for (int i = 0; encodedText[i] != '\0'; ++i) 
  {

    // If the key element is a null, then reset the index back to the beginning.
    if (inputKey[ keyIndex] == '\0') { 
      keyIndex = 0;   // Reset the key index back to the beginning.
    }

    offset = inputKey[ keyIndex] - 'a';    // Update the offset. It is the number of letters between the    
                                           // current letter of inputKey and 'a'
    ++keyIndex;       // Increment the key index for the next letter in inputKey.

    if ( !isalpha( encodedText[i])) {   // If element is a space, add a space to the plain text array
      plainText[i] = encodedText[i];
    }
    else {

      // If shifting the inputText letter brings it out of alphabet bounds, or less than ASCII
      // 'a', then loop it back to 'z'
      if ( encodedText[i] - offset < 'a') {
        // Add 26 to the decoded letter to make it a valid alphabet letter
        plainText[i] = encodedText[i] - offset + 26;   // Add encoded letter to plainText
      }
      // If element is a non-alpha char, like punctuation, leave it in the decoded phrase
      else if ( !isalpha( encodedText[i])) {
         plainText[i] = encodedText[i];
         continue;
      }
      else {
        plainText[i] = encodedText[i] - offset;   // Add encoded letter to plainText
      } // end inner if-else statement
    } // end outer if-else statement
  } // end for loop
} // end decodeText()


//-------------------------------------------------------------------------------------
// Test every word from the story file as a possible key word to decode the phrase. Print out the most successful test words
void findKeyword( char *inputText, char dictionary[DICTIONARY_SIZE][WORD_SIZE]) {
  char testKey[81] = { 0 };          // Current key word taken from file
  char plainText[81] = { 0 };        // Decoded form of each phrase
  int currentBest = 0;               // Highest number of dictionary words found so far
  char ignore[] = "squibsand";       // Ignore the word squibsand because it was originally "squibs-and". Test words that 
                                          // are not in the dictionary are still valid, so we pointed out this specific word

  ifstream inStream;    // Declare an input stream 
  inStream.open("TheSecretAgentByJosephConrad.txt");   // Open the file to read it

  // Print out error message and end program if the file is not found
  if (!inStream.is_open()) {
      cout << "Could not find TheSecretAgentByJosephConrad.txt.  Exiting..." << endl;
      exit(-1);
  }

  // Continously take in words from the file
  while (inStream >> testKey)
  {
   cleanInput(testKey);      // Convert each word to all lower case

   // Check if the test key is the ignored word
   if ( strcmp( testKey, ignore) == 0 ) {
      continue;      // Skip this word and move on to the beginning of the while loop for the next word
   }
   else {
      decodeText( inputText, testKey, plainText);   // Decode using current test key and store decoded phrase to plainText 
    
      // Print out plain text if the number of dictionary words found using the inputKey is greater than
      // the current best number. 
      if (  numDictionaryWords( plainText, testKey, dictionary) > currentBest) {
         currentBest = numDictionaryWords( plainText, testKey, dictionary);      // Update current best
   
         // Print out the plain text and the number of dictionary words found using the test key
         cout << numDictionaryWords( plainText, testKey, dictionary) << " words found using keyword: " << testKey 
              << " giving:" << endl<< "   " <<  plainText << endl;
      }
   }
  } // end while loop

  inStream.close();   // Close the file once it has been completely read
} // end findKeyword()


//---------------------------------------------------------------------------
int main()
{
  char inputText[WORD_SIZE] = { 0 };  // The user's chosen text that will be encoded or decoded to
  char inputKey[WORD_SIZE] = { 0 };   // The user's chosen key word to dictate how a word is encoded
  char plainText[WORD_SIZE] = { 0 };  // Encoded version of the user's chosen text
  char dictionary[DICTIONARY_SIZE][WORD_SIZE] = { 0 };    // Array that holds the dictionary words
  int menuOption;          // Userinput for menu option
  char returnCharacter;    // Separately store the return character so cin.getline does not consider 
                              // it the next user input
  
  readDictionary( dictionary);        // Open dictionary files and take in all the words
  // Print out the total number of words found in the dictionary.txt file. 
  // All the words in this file have at least 3 letters. 
  cout << "21735 words of size >= 3 were read in from dictionary. " << endl;

  // Display menu and handle the user's input accordingly
  cout << endl
       << "Choose from the following options: \n"
       << "    1. Lookup dictionary word \n"
       << "    2. Encode some text  \n"
       << "    3. Decode some text  \n"
       << "    4. Auto-decode the ciphertext given with the assignment  \n"
       << "    5. Exit program  \n"
       << "Your choice: ";
  cin >> menuOption;
  returnCharacter = cin.get();  // Read and discard the return character at the end of the above input line.
                                // This is necessary because otherwise a subsequent cin.getline() reads it as
                                // an empty line of input.


  switch (menuOption) {
  case 1: // Do dictionary lookup of a word and indicate whether or not it was found.
    cout << "Enter a word to be looked up in dictionary: ";
    cin >> inputText;
    cout << inputText;

    if ( isInDictionary(inputText, dictionary))    // Checks if word from user is in the dictionary
        cout << " IS in the dictionary." << endl;     // Message for when word IS in dictionary
    else
        cout << " is NOT in the dictionary." << endl; // Message for when word is NOT in dictionary
    break;

  case 2: // Encode some text
    cout << "Enter the text to be encoded: ";   // Prompt user for their chosen phrase
    fgets( inputText, WORD_SIZE, stdin); // Get user's input and put it in the inputText array
    cleanInput( inputText);       // Convert the text to all lowercase
    
    cout << "Enter a keyword for Vigenere encryption: "; // Prompt user for keyword
    fgets( inputKey, WORD_SIZE, stdin);  // Get user's input and put it in the inputKey array
    cleanInput( inputKey);        // Convert the key word to all lowercase

    cout << "Keyword, plainText and ciphertext are:  \n";
    // Encode phrase. The function will print out the keyWord, input text (plain text), and cipherText
    // (encoded version of text)
    encodeText( inputText, inputKey);   
    break;

  case 3: // Decode using user-entered values
    cout << "Enter the cipherText to be decoded: "; // Prompt user for their encoded phrase
    fgets( inputText, WORD_SIZE, stdin);   // Get user's input and put it in the inputText array
    cleanInput( inputText);         // Convert the text to all lowercase

    cout << "Enter a Vigenere keyword to be tried: ";
    fgets( inputKey, WORD_SIZE, stdin);    // Get user's input and put it in the inputKey array
    cleanInput( inputKey);          // Convert the key word to all lowercase
    decodeText( inputText, inputKey, plainText);   // Decode phrase
    
    // Print out the plain text and the number of dictionary words found using the inputKey
    cout << numDictionaryWords( plainText, inputKey, dictionary) << " words found using keyword: " << inputKey 
         << " giving:" << endl<< "   " <<  plainText << endl;
    break;

  case 4: // Decode ciphertext given with the assignment
    cout << "Enter the cipherText to be decoded: ";  // Prompt user for their encoded phrase
    fgets( inputText, WORD_SIZE, stdin);   // Get user's input and put it in the inputText array
    cleanInput(inputText);          // Convert the text to all lowercase

    findKeyword( inputText, dictionary); 
    break;

  case 5: // Exit program
      cout << "Exiting program" << endl;
      exit(0);  // Function for exiting a program
      break;

  default:
      // Print out error if the user's input does not fit a menu option
      cout << "Invalid menu option.  Exiting program." << endl;
      break;
  } // end switch( menuOption)

  return 0;   // Return someting for int main()
} // end main()
