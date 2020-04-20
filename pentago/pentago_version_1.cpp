/* ----------------------------------------------------------- 
  Program 5: Pentago
  
  Class: CS 141, Spring 2020.  Tues 1pm lab
  System: Zybooks
  Author: Paola Reyes
----------------------------------------------------------- */
#include <iostream>  // Needed to avoid compiler error for the exit() command
#include <cctype>    // For toupper()
using namespace std;

// Global constants
const int BOARD_SIZE = 36;

//-------------------------------------------------------------------------------------
class Board {
  public:
    // Functions called to start the game
    Board();  // Default constructor with no parameters
    void displayInstructions();      
    void displayBoard();

    // Functions called to set a piece on the board
    void makeMove();
    bool validMove( char row, int column, int quadrant, char direction);
    void rotate( char direction, char &p1, char &p2, char &p3, char &p4, char &p5, char &p6, char &p7, char &p8);
    void quadrantRotate( int quadrant, char direction);

    // Functions called to check when the game should end
    bool winFound( char player);
    bool match( char player, char p1, char p2, char p3, char p4, char p5);
    bool tieFound();
    void checkEndGame();
    bool getGameNotOver() { return gameNotOver;}

  private:
    char board[ BOARD_SIZE];   // 1d array holding all the board values
    int moveNumber;
    char currentPlayer;   // the two players are X and O
    bool gameNotOver;     // True when game should continue, false when game should end
}; // end class Board


//-------------------------------------------------------------------------------------
// Default Board class constructor
Board::Board() {
  // Initialize starting values. The first player is X
  gameNotOver = true;
  moveNumber = 1;
  currentPlayer = 'X';  

  // Go through each quadrant array and change each item to a '.' for a blank board
  for (int i = 0; i < BOARD_SIZE; i++) {
    board[i] = '.';
  }
} // end Board::Board


//-------------------------------------------------------------------------------------
// Print out current playing board
void Board::displayBoard() {
  cout << endl
       << "    1   2   3   4   5   6    " << endl 
       << "  1-----------------------2  " << endl 
       << "A | " <<  board[0] << "   " <<  board[1] << "   " <<  board[2] << " | " <<  board[3] << "   " <<  board[4] << "   " <<  board[5] << " | A" << endl
       << "  |           |           |  " << endl
       << "B | " <<  board[6] << "   " <<  board[7] << "   " <<  board[8] << " | " <<  board[9] << "   " << board[10] << "   " << board[11] << " | B" << endl
       << "  |           |           |  " << endl
       << "C | " << board[12] << "   " << board[13] << "   " << board[14] << " | " << board[15] << "   " << board[16] << "   " << board[17] << " | C" << endl
       << "  |-----------+-----------|  " << endl
       << "D | " << board[18] << "   " << board[19] << "   " << board[20] << " | " << board[21] << "   " << board[22] << "   " << board[23] << " | D" << endl
       << "  |           |           |  " << endl
       << "E | " << board[24] << "   " << board[25] << "   " << board[26] << " | " << board[27] << "   " << board[28] << "   " << board[29] << " | E" << endl
       << "  |           |           |  " << endl
       << "F | " << board[30] << "   " << board[31] << "   " << board[32] << " | " << board[33] << "   " << board[34] << "   " << board[35] << " | F" << endl
       << "  3-----------------------4  " << endl
       << "    1   2   3   4   5   6    " << endl;
} // end Board::displayBoard()


//-------------------------------------------------------------------------------------
void Board::displayInstructions()
{
    cout << "\n"
         << "Play the two-player game of Pentago. Be the first to get 5 in a row. \n"
         << "                                                                 \n"
         << "Pentago is played on a 6 by 6 board, divided into four 3 by 3    \n"
         << "quadrants.  There are two players, X and O, who alternate turns. \n"
         << "The goal of each player is to get five of their pieces in a row, \n"
         << "either horizontally, vertically, or diagonally.                  \n"
         << "                                                                 \n"
         << "Players take turns placing one of their pieces into an empty     \n"
         << "space anywhere on the board, then choosing one of the four       \n"
         << "board quadrants to rotate 90 degrees left or right.              \n"
         << "                                                                 \n"
         << "If both players get five in a row at the same time, or the       \n"
         << "last move is played with no five in a row, the game is a tie.    \n"
         << "If a player makes five a row by placing a piece, there is no need\n"
         << "to rotate a quadrant and the player wins immediately.            \n"
         << "                                                                 \n"
         << "     Play online at:  https://perfect-pentago.net                \n"
         << "     Purchase at:     www.mindtwisterusa.com                     \n"
         << "                                                                 \n"
         << "For each move provide four inputs:                               \n"
         << "   row (A-F), column (1-6), quadrant (1-4), rotation direction (L or R) \n"
         << "For instance input of B32R places the next piece at B3 and then  \n"
         << "would rotate quadrant 2 (upper-right) to the right (clockwise).  \n"
         << "                                                                 \n"
         << "At any point enter 'x' to exit the program or 'i' to display instructions." << endl;
} // end Board::displayInstructions()


//-------------------------------------------------------------------------------------
// Check if each value in the user's input makes is valid according to Pentago rules
bool Board::validMove( char row, int column, int quadrant, char direction) {
  if ( row < 'A' || row > 'F') {  // Row should be between A & F
    cout << "    *** Invalid move row.  Please retry." << endl;
    return false;
  }
  else if ( column < 1 || column > 6) {  // Column should be between 1 & 6
    cout << "    *** Invalid move column.  Please retry." << endl;
    return false;
  }
  else if ( quadrant < 1 || quadrant > 4) {  // Quadrant should be between 1 & 4
    cout << "    *** Selected quadrant is invalid.  Please retry." << endl;
    return false;
  }
  else if ( direction != 'L' && direction != 'R') {  // Direction should be L or R
    cout << "    *** Quadrant rotation direction is invalid.  Please retry." << endl;
    return false;
  }
  else if ( board[ (row - 'A') * 6 + column - 1] != '.') {  // Input is valid but the spot is taken
    cout << "    *** That board location is already taken.  Please retry." << endl;
    return false;
  }
  else {
    return true;
  }
} // end Board::validMove()


//-------------------------------------------------------------------------------------
// Rotates a quadrant section of the board given the user's input
void Board::rotate( char direction, char &p1, char &p2, char &p3, char &p4, char &p5, char &p6, char &p7, char &p8) {
  // Hold original values of a pieces that have been overwritten
  char temp1;    
  char temp2;

  if (direction == 'L') {  // Switch value counter-clockwise
    temp1 = p1;
    temp2 = p2;
    p1 = p3;
    p2 = p4;
    p3 = p5;
    p4 = p6;
    p5 = p7;
    p6 = p8;
    p7 = temp1;
    p8 = temp2;
  }
  else { // Switch the values clockwise
    temp1 = p8;
    temp2 = p7;
    p8 = p6;
    p7 = p5;
    p6 = p4;
    p5 = p3;
    p4 = p2;
    p3 = p1;
    p2 = temp1;
    p1 = temp2;
  }
} // end Board::rotate()


//-------------------------------------------------------------------------------------
// Identify the pieces to roate given the user's input
void Board::quadrantRotate( int quadrant, char direction) {
  // Set which pieces to rotate based on the quadrant
  if ( quadrant == 1) {
    rotate( direction, board[0], board[1], board[2], board[8], board[14], board[13], board[12], board[6]);
  }
  else if ( quadrant == 2) {
    rotate( direction, board[3], board[4], board[5], board[11], board[17], board[16], board[15], board[9]);
  }
  else if ( quadrant == 3) {
    rotate( direction, board[18], board[19], board[20], board[26], board[32], board[31], board[30], board[24]);
  }
  else {
    rotate( direction, board[21], board[22], board[23], board[29], board[35], board[34], board[33], board[27]);
  }
} // end Board::quadrantRotate()


//-------------------------------------------------------------------------------------
// Helper function to winFound(). Checks if any 5 used spots are the same 
bool Board::match( char player, char p1, char p2, char p3, char p4, char p5) {
  return (p1 == player) && (p1 == p2) && (p2 == p3) && (p3 == p4) && (p4 == p5);
} // end Board::match()


//-------------------------------------------------------------------------------------
// Check if any player's piece make a five-in-a-row win
bool Board::winFound( char player) {
  if ( match( player, board[0],  board[6],  board[12], board[18], board[24]) ||
       match( player, board[1],  board[7],  board[13], board[19], board[25]) ||
       match( player, board[2],  board[8],  board[14], board[20], board[26]) ||
       match( player, board[3],  board[9],  board[15], board[21], board[27]) ||
       match( player, board[4],  board[10], board[16], board[22], board[28]) ||
       match( player, board[5],  board[11], board[17], board[23], board[29]) ||
       match( player, board[30], board[24], board[18], board[12], board[6])  ||
       match( player, board[31], board[25], board[19], board[13], board[7])  ||
       match( player, board[32], board[26], board[20], board[14], board[8])  ||
       match( player, board[33], board[27], board[21], board[15], board[9])  ||
       match( player, board[34], board[28], board[22], board[16], board[10]) ||
       match( player, board[35], board[29], board[23], board[17], board[11]) ||  // 12 possible vertical wins
       match( player, board[0],  board[1],  board[2],  board[3],  board[4])  ||
       match( player, board[6],  board[7],  board[8],  board[9],  board[10]) ||
       match( player, board[12], board[13], board[14], board[15], board[16]) ||
       match( player, board[28], board[19], board[20], board[21], board[22]) ||
       match( player, board[24], board[25], board[26], board[27], board[28]) ||
       match( player, board[30], board[31], board[32], board[33], board[34]) ||
       match( player, board[1],  board[2],  board[3],  board[4],  board[5])  ||
       match( player, board[11], board[10], board[9],  board[8],  board[7])  ||
       match( player, board[17], board[16], board[15], board[14], board[13]) ||
       match( player, board[23], board[22], board[21], board[20], board[19]) ||
       match( player, board[29], board[28], board[27], board[26], board[25]) ||
       match( player, board[35], board[34], board[33], board[32], board[31]) ||  // 12 possible horizontal wins
       match( player, board[0],  board[7],  board[14], board[21], board[28]) ||
       match( player, board[5],  board[10], board[15], board[20], board[25]) ||
       match( player, board[30], board[25], board[20], board[15], board[10]) ||
       match( player, board[35], board[28], board[21], board[14], board[7])  || 
       match( player, board[1],  board[8],  board[15], board[22], board[29]) || 
       match( player, board[6],  board[13], board[20], board[27], board[34]) ||
       match( player, board[4],  board[9],  board[14], board[19], board[24]) ||
       match( player, board[11], board[16], board[21], board[26], board[31]) ){  // 8 possible diagonal wins
    return true;
  }
  else {
    return false;
  }
} // end Board::winFound()


//-------------------------------------------------------------------------------------
// Check for a tie where either both players get a win at the same time or the 
// board has been filled up yet no one won
bool Board::tieFound() {
  if ( winFound('X') && winFound('O')) {
    cout << "   *** Both X and O have won.  Game is a tie." << endl;
    return true;
  }
  else {
    // Check if any spot is still the default '.'
    for ( int i = 0; i < BOARD_SIZE; i++) {
      if ( board[i] == '.') {
        return false;
      }
    }

    // If no '.' was found the game is a tie
    cout << "    *** No one has won.  Game is a tie." << endl;
    return true;
  }
} // end Board::tieFound()


//-------------------------------------------------------------------------------------
// Check if game should end if there's a tie or at least one person won
void Board::checkEndGame() {
  if ( tieFound()) {    
    gameNotOver = false;
  }
  else if ( winFound('X') || winFound('O')) {   // Someone wins the game & it's not a tie
    cout << "    *** " << currentPlayer << " has won the game!" << endl; // Print win message
    gameNotOver = false;
  }
} // end Board::checkEndGame()


//-------------------------------------------------------------------------------------
// Take in user's input and calls functions that correspond that input
void Board::makeMove() {
  char row, colChar, quadChar, direction;   // Inputs taken in as chars for easier reading
  int column, quadrant;                     // Integers will be converted from char to int

  // The players, X and O, take turns based on the current move number
  if ( moveNumber % 2 != 0) {
    currentPlayer = 'X';
  }
  else {
    currentPlayer = 'O';
  }
  
  // Print out instructions with current move number and player & ask for user input
  cout << moveNumber << ". Enter row, column, quadrant, direction for " << currentPlayer << ": ";
  cin >> row;
  row = toupper( row);  // Change row input to uppercase

  // Check the instances where the input is just 1 letter first
  if ( row == 'I') {  // Input 'I' shows the instructions
    displayInstructions();
  }
  else if ( row == 'X') {  // Input 'X' exits the program
    cout << "Exiting program...";
    exit(0);
  } 
  else {  // Instances where all 4 variables are used
    // Read in the rest of the input and modify as needed. 
    cin >> colChar >> quadChar >> direction;
    column = colChar - '0';         // Calculate integer values from character
    quadrant = quadChar - '0';  
    direction = toupper( direction);

    if ( !validMove( row, column, quadrant, direction));  // Check if input is valid 
    else {
      int position = (row - 'A') * 6 + column - 1;  // Calculation from input to index of board[]
      board[position] = currentPlayer;              // Set play piece in that spot
      quadrantRotate( quadrant, direction);         // Rotate board quadrant
      checkEndGame();                               // Check if game should end before making the next move
      moveNumber++;                                 // Increment moveNumber for the next move
    } // end inner if-else statement
  } // end outer if-else statement
} // end Board::makeMove()


//-------------------------------------------------------------------------------------
int main() {
  Board theBoard;   // Create the board as an instance of the Board class

  // Welcome message shown only at the beginning along with the empty board
  cout << "Welcome to Pentago, where you try to get 5 of your pieces in a line." << endl
       << "At any point enter 'x' to exit or 'i' for instructions." << endl;
  theBoard.displayBoard();
  
  // Prompt player to make a move until the game is over
  while ( theBoard.getGameNotOver()) {
    theBoard.makeMove();
    theBoard.displayBoard();  // Display updated game board
  }
  
  // Thank player after the game is over
  cout << "Thanks for playing.  Exiting... " << endl;
  return 0;
} // end main()
