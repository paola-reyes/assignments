/* -----------------------------------------------------------
Program 2: Cuatro
  Class: CS 141, Spring 2020. Tues 1pm lab
  System: Zybooks
  Author: Paola Reyes

  Cuatro is a game where 2 players try to get 4 types of letters lined up together
  on a 4x4 grid. They get 8 letters to choose from and can place them in 16 
  different spots on the board. The goal is to get either 4 vowels, 4 consonants, 4 
  lower case letters, 4 upper case letters, 4 curvy letters, or 4 straight-lined 
  letters all together. The letters can be arranged horitontally, vertically, 
  diagonally, or as corner quadrants to win.
  
  Running the program and inputting a value (for example, C 6) should look like this:

    Welcome to the game of Cuatro, where you try to complete a set      
    of four pieces that are alike.  Players take turns making moves.    
    On each move your OPPONENT chooses the piece, then YOU get to       
    place it on the board.  If you create a set of four alike when      
    you place your piece, then you win!       

    A set of four alike can be completed by using four all upper (or all
    lower) case characters, four all vowels (or all consonants), or four
    all curved (or all straight-lined). Curved letters are 'O' and 'C'
    (upper or lower), and straight-line letters are 'I' and 'Z' (upper or
    lower). Groups of four can be created in a row, column, diagonal, or
    corner quadrant.

    When prompted for input you may also enter 'x' or 'X' to exit.

         ---------    Square #  
        | . . . . |  1  2  3  4 
        | . . . . |  5  6  7  8 
        | . . . . |  9 10 11 12 
        | . . . . | 13 14 15 16 
         ---------              
        Pieces:     Curved Straight                
              Upper: OO/CC  II/ZZ
              Lower: oo/cc  ii/zz
                    Vowel/Consonant  
    1. Player 1 enter piece, and Player 2 enter destination: C 6

         ---------    Square #  
        | . . . . |  1  2  3  4 
        | . C . . |  5  6  7  8 
        | . . . . |  9 10 11 12 
        | . . . . | 13 14 15 16 
         ---------              
        Pieces:     Curved Straight                
              Upper: OO/ C  II/ZZ
              Lower: oo/cc  ii/zz
                    Vowel/Consonant

----------------------------------------------------------*/
#include <iostream>   // for cin and cout
#include <iomanip>    // for setw()
using namespace std;  // so that we don't need to preface every cin and cout with std::

// Global variables to represent the 16 board pieces and C++ strings representing
// the pieces that have not yet been played.  Since these are global they don't
// need to be passed as parameters to functions, and are shared over the entire program.
// Normally global variables will not be allowed.
char p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16;
string upperRowPiecesToPlay = "OO/CC  II/ZZ";
string lowerRowPiecesToPlay = "oo/cc  ii/zz";

//-------------------------------------------------------------------------------------
void displayInstructions()
{
    cout << "Welcome to the game of Cuatro, where you try to complete a set      \n"
         << "of four pieces that are alike.  Players take turns making moves.    \n"
         << "On each move your OPPONENT chooses the piece, then YOU get to       \n"
         << "place it on the board.  If you create a set of four alike when      \n"
         << "you place your piece, then you win!       \n"
         << "\n"
         << "A set of four alike can be completed by using four all upper (or all\n"
         << "lower) case characters, four all vowels (or all consonants), or four\n"
         << "all curved (or all straight-lined). Curved letters are 'O' and 'C'\n"
         << "(upper or lower), and straight-line letters are 'I' and 'Z' (upper or\n"
         << "lower). Groups of four can be created in a row, column, diagonal, or\n"
         << "corner quadrant.\n"
         << "\n"
         << "When prompted for input you may also enter 'x' or 'X' to exit." << endl;
}// end displayInstructions()


//-------------------------------------------------------------------------------------
void displayBoard() {
  // Print out updated game board and its square number labels
  cout << endl
       << setw(27) << "---------    Square #" << endl
       << setw(7) << "| " << p1  << " " << p2  << " " << p3  << " " << p4  << " |  1  2  3  4" << endl
       << setw(7) << "| " << p5  << " " << p6  << " " << p7  << " " << p8  << " |  5  6  7  8" << endl 
       << setw(7) << "| " << p9  << " " << p10 << " " << p11 << " " << p12 << " |  9 10 11 12" << endl
       << setw(7) << "| " << p13 << " " << p14 << " " << p15 << " " << p16 << " | 13 14 15 16" << endl 
       << "      ---------" << endl; 

  // Print out the available pieces left
  cout << "     Pieces:     Curved Straight" << endl                
       << setw(19) << "Upper:  " << upperRowPiecesToPlay << endl
       << setw(19) << "Lower:  " << lowerRowPiecesToPlay << endl
       << setw(32) << "Vowel/Consonant" << endl;
} // end displayBoard()


//-------------------------------------------------------------------------------------
/* Given the player's chosen position number, return the address of the piece character 
in that position. 
This is to minimize many series of if-statements needed throughout the code assigning a 
position number to a piece character. If we need to derive a piece's value from a position 
number or we need to change the piece's value, it can be done with a pointer. */
char* positionToPiece( int position) {
  char* piece;

  if ( position == 1) {
    piece = &p1;
  } 
  else if ( position == 2) {
    piece = &p2;
  }
  else if ( position == 3) {
    piece = &p3;
  }
  else if ( position == 4) {
    piece = &p4;
  }
  else if ( position == 5) {
    piece = &p5;
  }
  else if ( position == 6) {
    piece = &p6;
  }
  else if ( position == 7) {
    piece = &p7;
  }
  else if ( position == 8) {
    piece = &p8;
  }
  else if ( position == 9) {
    piece = &p9;
  }
  else if ( position == 10) {
    piece = &p10;
  }
  else if ( position == 11) {
    piece = &p11;
  }
  else if ( position == 12) {
    piece = &p12;
  }
  else if ( position == 13) {
    piece = &p13;
  }
  else if ( position == 14) {
    piece = &p14;
  }
  else if ( position == 15) {
    piece = &p15;
  }
  else if ( position == 16) {
    piece = &p16;
  }

  return piece;
} // end positionToPiece()


//-------------------------------------------------------------------------------------
// Once a player has used a character, remove it as an option on the pieces to play strings
void removePieceToPlayChar( char letter) {
  int index;

  // find() should return a digit for the index of piece if it finds one in the string
  if ( upperRowPiecesToPlay.find( letter) != string::npos ) {
    // The place in the string where the character is located
    index = upperRowPiecesToPlay.find( letter);

    // Delete the used character from the string and replace it with an empty space
    upperRowPiecesToPlay.replace( index, 1, " ");
  }
  else if ( lowerRowPiecesToPlay.find( letter) != string::npos ) {
    index = lowerRowPiecesToPlay.find( letter);
    lowerRowPiecesToPlay.replace( index, 1, " ");
  }
} // end removePieceToPlayChar


//-------------------------------------------------------------------------------------
// Verify that the player's given move is possible under Cuatro rules
bool validMove( char letter, int position) {
  char* piece = positionToPiece( position);

  // A letter is a valid input it's one of the letters on the pieces to play strings
  bool validLetter = letter == 'o' || letter == 'O' || letter == 'c' || letter == 'C' ||
                     letter == 'i' || letter == 'I' || letter == 'z' || letter == 'Z';
  // A position number is valid if it is within the range 1-16 
  bool validPosition = position >= 1 && position <= 16;

  // If a player makes an invalid move, they get a second chance to make a move. As a 
  // result, the moveNumber doesn't increase in makeMove(). 
  if ( !validLetter) {
    cout << "*** Sorry, that is an invalid piece.  Please retry." << endl;
    return false;
  }
  else if ( !validPosition) {
    cout << "*** Sorry, that destination is invalid.  Please retry." << endl;
    return false;
  }
  else if ( *piece != '.') {  // If the spot is already taken
    cout << "*** Sorry, that destination is occupied.  Please retry." << endl;
    return false;
  }
  // If the letter was used up, it won't show up as an option on the pieces to play strings.
  else if ( validLetter && upperRowPiecesToPlay.find( letter) == string::npos &&
                           lowerRowPiecesToPlay.find( letter) == string::npos) {
    cout << "*** Sorry, that is an invalid piece.  Please retry." << endl;
    return false;
  }
  else {
    return true;
  }
} // end validMove()


//-------------------------------------------------------------------------------------
// Ask player for their input and, depending on whether it's a valid move, either place 
// it on the board or exit the game. Takes it moveNumber address to update the moveNumber
// variable found in the main function 
void makeMove( int &moveNumber) {
  char letter;
  int position;

  // Display intrustions for the players depending on whose turn it is. 
  // Player 1 has the odd number moves and Player 2 has the even number moves 
  if ( moveNumber % 2 != 0) {
    cout << moveNumber << ". Player 1 enter piece, and Player 2 enter destination: ";
  } else {
    cout << moveNumber << ". Player 2 enter piece, and Player 1 enter destination: ";
  }

  cin >> letter;  // Ask player for their chosen letter

  // The letter x/X exits the program. This command doesn't have an accopanying position 
  // number so we don't ask for one until after we've searched for an X.
  if ( letter == 'x' || letter == 'X') {
    cout << "Exiting program...";
    exit(0);
  }

  cin >> position;  // Ask player for their chosen position number 

  // Start by verifying if the player's input is valid. validMove() will output the 
  // appropriate instructions when called
  if ( !validMove( letter, position)); 
  else {
    // Change board piece character to the given letter
    char* piece = positionToPiece( position);
    *piece = letter;   // Change the character value from '.' to the given letter
    removePieceToPlayChar( letter);  // Remove letter as an option on the pieces to play strings
    moveNumber++;  // Update moveNumber
  }
} // end makeMove()


//-------------------------------------------------------------------------------------
// Checks if the given letter is a vowel
bool isVowel( char letter) {
  return letter == 'i' || letter == 'I' || letter == 'o' || letter == 'O';
} // end isVowel()


//-------------------------------------------------------------------------------------
// Checks if the given letter is a consonant
bool isConsonant( char letter) {
  return letter == 'c' || letter == 'C' || letter == 'z' || letter == 'Z';
} // end isConsonant()


//-------------------------------------------------------------------------------------
// Checks if the given letter is a lower case letter
bool isLowerCase( char letter) {
  return letter == 'c' || letter == 'i' || letter == 'o' || letter == 'z';
} // end isLowerCase()


//-------------------------------------------------------------------------------------
// Checks if the given letter is an upper case letter
bool isUpperCase( char letter) {
  return letter == 'C' || letter == 'I' || letter == 'O' || letter == 'Z';
} // end isLowerCase()


//-------------------------------------------------------------------------------------
// Checks if the given letter has a curved shape
bool isCurved( char letter) {
  return letter == 'c' || letter == 'C' || letter == 'o' || letter == 'O';
} // end isCurved()

//-------------------------------------------------------------------------------------
// Checks if the given letter has a straight line shape
bool isStraight( char letter) {
  return letter == 'i' || letter == 'I' || letter == 'z' || letter == 'Z';
} // end isStraight()


//-------------------------------------------------------------------------------------
// Checks if 4 given pieces are all vowels, consonants, lower case, upper case, curved, 
// or straight. This is a helper function to make the code more readable
bool checkGrouping( string group, char pos1, char pos2, char pos3, char pos4) {
  bool validGrouping;

  if ( group == "vowel") {
    validGrouping = isVowel( pos1) && isVowel( pos2) && isVowel( pos3) && isVowel( pos4);
  } 
  else if ( group == "consonant") {
    validGrouping = isConsonant( pos1) && isConsonant( pos2) && isConsonant( pos3) && isConsonant( pos4);
  }
  else if ( group == "lower case") {
    validGrouping = isLowerCase( pos1) && isLowerCase( pos2) && isLowerCase( pos3) && isLowerCase( pos4);
  }
  else if ( group == "upper case") {
    validGrouping = isUpperCase( pos1) && isUpperCase( pos2) && isUpperCase( pos3) && isUpperCase( pos4);
  }
  else if ( group == "curved") {
    validGrouping = isCurved( pos1) && isCurved( pos2) && isCurved( pos3) && isCurved( pos4);
  }
  else if ( group == "straight") {
    validGrouping = isStraight( pos1) && isStraight( pos2) && isStraight( pos3) && isStraight( pos4);
  }

  return validGrouping;
} // end checkGrouping


//-------------------------------------------------------------------------------------
// Checks if there is a win across any row in the board
bool horizontalWin() {
  
  // Checks if any row has 4 consecutive vowels
  if ( checkGrouping( "vowel", p1, p2, p3, p4) || checkGrouping( "vowel", p5, p6, p7, p8) ||
       checkGrouping( "vowel", p9, p10, p11, p12) || checkGrouping( "vowel", p13, p14, p15, p16)) {
    return true;
  } 
  // Checks if any row has 4 consecutive consonants
  else if ( checkGrouping( "consonant", p1, p2, p3, p4) || 
            checkGrouping( "consonant", p5, p6, p7, p8) ||
            checkGrouping( "consonant", p9, p10, p11, p12) ||
            checkGrouping( "consonant", p13, p14, p15, p16)) {
    return true;
  }
  // Checks if any row has 4 consecutive lower case letters
  else if ( checkGrouping( "lower case", p1, p2, p3, p4) || 
            checkGrouping( "lower case", p5, p6, p7, p8) ||
            checkGrouping( "lower case", p9, p10, p11, p12) ||
            checkGrouping( "lower case", p13, p14, p15, p16)) {
    return true;
  }
  // Checks if any row has 4 consecutive upper case letters
  else if ( checkGrouping( "upper case", p1, p2, p3, p4) || 
            checkGrouping( "upper case", p5, p6, p7, p8) ||
            checkGrouping( "upper case", p9, p10, p11, p12) ||
            checkGrouping( "upper case", p13, p14, p15, p16)) {
    return true;
  }
  // Checks if any row has 4 consecutive curved letters
  else if ( checkGrouping( "curved", p1, p2, p3, p4) || 
            checkGrouping( "curved", p5, p6, p7, p8) ||
            checkGrouping( "curved", p9, p10, p11, p12) ||
            checkGrouping( "curved", p13, p14, p15, p16)) {
    return true;
  }
  // Checks if any row has 4 consecutive straight letters
  else if ( checkGrouping( "straight", p1, p2, p3, p4) || 
            checkGrouping( "straight", p5, p6, p7, p8) ||
            checkGrouping( "straight", p9, p10, p11, p12) ||
            checkGrouping( "straight", p13, p14, p15, p16)) {
    return true;
  } 
  else {
    return false;
  }
} // end horizontalWin()


//-------------------------------------------------------------------------------------
// Checks if there is a win across any column in the board
bool verticalWin() {
  
  // Checks if any row has 4 consecutive vowels
  if ( checkGrouping( "vowel", p1, p5, p9, p13) || 
       checkGrouping( "vowel", p2, p6, p10, p14) ||
       checkGrouping( "vowel", p9, p10, p11, p12) ||
       checkGrouping( "vowel", p13, p14, p15, p16)) {
    return true;
  } 
  // Checks if any row has 4 consecutive consonants
  else if ( checkGrouping( "consonant", p1, p5, p9, p13) || 
            checkGrouping( "consonant", p2, p6, p10, p14) ||
            checkGrouping( "consonant", p3, p7, p11, p15) ||
            checkGrouping( "consonant", p4, p8, p12, p16)) {
    return true;
  }
  // Checks if any row has 4 consecutive lower case letters
  else if ( checkGrouping( "lower case", p1, p5, p9, p13) || 
            checkGrouping( "lower case", p2, p6, p10, p14) ||
            checkGrouping( "lower case", p3, p7, p11, p15) ||
            checkGrouping( "lower case", p4, p8, p12, p16)) {
    return true;
  }
  // Checks if any row has 4 consecutive upper case letters
  else if ( checkGrouping( "upper case", p1, p5, p9, p13) || 
            checkGrouping( "upper case", p2, p6, p10, p14) ||
            checkGrouping( "upper case", p3, p7, p11, p15) ||
            checkGrouping( "upper case", p4, p8, p12, p16)) {
    return true;
  }
  // Checks if any row has 4 consecutive curved letters
  else if ( checkGrouping( "curved", p1, p2, p3, p4) || 
            checkGrouping( "curved", p2, p6, p10, p14) ||
            checkGrouping( "curved", p3, p7, p11, p15) ||
            checkGrouping( "curved", p4, p8, p12, p16)) {
    return true;
  }
  // Checks if any row has 4 consecutive straight letters
  else if ( checkGrouping( "straight", p1, p2, p3, p4) || 
            checkGrouping( "straight", p2, p6, p10, p14) ||
            checkGrouping( "straight", p3, p7, p11, p15) ||
            checkGrouping( "straight", p4, p8, p12, p16)) {
    return true;
  } 
  else {
    return false;
  }
} // end verticalWin()


//-------------------------------------------------------------------------------------
// Checks if there is a win across any diagonal in the board
bool diagonalWin() {
    
  // Checks if any row has 4 consecutive vowels
  if ( checkGrouping( "vowel", p1, p6, p11, p16) || 
       checkGrouping( "vowel", p4, p7, p10, p13)) {
    return true;
  } 
  // Checks if any row has 4 consecutive consonants
  else if ( checkGrouping( "consonant", p1, p6, p11, p16) ||
            checkGrouping( "consonant", p4, p7, p10, p13)) {
    return true;
  }
  // Checks if any row has 4 consecutive lower case letters
  else if ( checkGrouping( "lower case", p1, p6, p11, p16) || 
            checkGrouping( "lower case", p4, p7, p10, p13)) {
    return true;
  }
  // Checks if any row has 4 consecutive upper case letters
  else if ( checkGrouping( "upper case", p1, p6, p11, p16) || 
            checkGrouping( "upper case", p4, p7, p10, p13)) {
    return true;
  }
  // Checks if any row has 4 consecutive curved letters
  else if ( checkGrouping( "curved", p1, p6, p11, p16) || 
            checkGrouping( "curved", p4, p7, p10, p13)) {
    return true;
  }
  // Checks if any row has 4 consecutive straight letters
  else if ( checkGrouping( "straight", p1, p6, p11, p16) || 
            checkGrouping( "straight", p4, p7, p10, p13)) {
    return true;
  } 
  else {
    return false;
  }
} // end diagonalWin()


//-------------------------------------------------------------------------------------
// Checks if there is a win at any corner quadrant in the board
bool cornerWin() {
  
  // Checks if any row has 4 consecutive vowels
  if ( checkGrouping( "vowel", p1, p2, p5, p6) || 
       checkGrouping( "vowel", p4, p3, p7, p8) ||
       checkGrouping( "vowel", p13, p14, p9, p10) ||
       checkGrouping( "vowel", p16, p15, p11, p12)) {
    return true;
  } 
  // Checks if any row has 4 consecutive consonants
  else if ( checkGrouping( "consonant", p1, p2, p5, p6) || 
            checkGrouping( "consonant", p4, p3, p7, p8) ||
            checkGrouping( "consonant", p13, p14, p9, p10) ||
            checkGrouping( "consonant", p16, p15, p11, p12)) {
    return true;
  }
  // Checks if any row has 4 consecutive lower case letters
  else if ( checkGrouping( "lower case", p1, p2, p5, p6) || 
            checkGrouping( "lower case", p4, p3, p7, p8) ||
            checkGrouping( "lower case", p13, p14, p9, p10) ||
            checkGrouping( "lower case", p16, p15, p11, p12)) {
    return true;
  }
  // Checks if any row has 4 consecutive upper case letters
  else if ( checkGrouping( "upper case", p1, p2, p5, p6) || 
            checkGrouping( "upper case", p4, p3, p7, p8) ||
            checkGrouping( "upper case", p13, p14, p9, p10) ||
            checkGrouping( "upper case", p16, p15, p11, p12)) {
    return true;
  }
  // Checks if any row has 4 consecutive curved letters
  else if ( checkGrouping( "curved", p1, p2, p5, p6) || 
            checkGrouping( "curved", p4, p3, p7, p8) ||
            checkGrouping( "curved", p13, p14, p9, p10) ||
            checkGrouping( "curved", p16, p15, p11, p12)) {
    return true;
  }
  // Checks if any row has 4 consecutive straight letters
  else if ( checkGrouping( "straight", p1, p2, p5, p6) || 
            checkGrouping( "straight", p4, p3, p7, p8) ||
            checkGrouping( "straight", p13, p14, p9, p10) ||
            checkGrouping( "straight", p16, p15, p11, p12)) {
    return true;
  } 
  else {
    return false;
  }
} // end cornerWin()


//-------------------------------------------------------------------------------------
// Check board for any possible combination of a win
bool winFound() {
  if ( horizontalWin()) {
    return true;
  }
  else if ( verticalWin()) {
    return true;
  }
  else if ( diagonalWin()) {
    return true;
  }
  else if ( cornerWin()) {
    return true;
  }
  else {
    return false;
  }
} // end winFound()


//-------------------------------------------------------------------------------------
int main()
{
  // Declare and initialize variables
  p1=p2=p3=p4=p5=p6=p7=p8=p9=p10=p11=p12=p13=p14=p15=p16 = '.';
  int moveNumber = 1;

  displayInstructions();
  displayBoard();
  

  while ( true) {
    // The game is a draw if the board is full and no win is possible
    bool noPiecesLeft = upperRowPiecesToPlay == "  /      /  " && lowerRowPiecesToPlay == "  /      /  ";
  
    if ( winFound()) {
      // Announce winner based on the last turn
      if( moveNumber % 2 != 0) {
        cout << "*** Player 1 you won!" << endl;
      }
      else {
        cout << "*** Player 2 you won!" << endl;
      }

      break;
    }
    else if ( noPiecesLeft) {
      break;
    }
    else {
      makeMove( moveNumber);
      displayBoard();
    }
  }  

  return 0;
} // end main()
