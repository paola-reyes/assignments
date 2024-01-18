/* ---------------------------------------------
Program 1: Wumpus, version 1 (fixed array)

Course: CS 211 Fall 2022
System: Windows using Visual Studio Code
Author: Paola Reyes
--------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>        // For malloc()
#include <stdlib.h>        // For srand()
#include <time.h>          // For time()
#include <stdbool.h>       // For bool
#include <ctype.h>         // For toupper()

void printCave() {
  printf("\n"
         "       ______18______             \n"
         "      /      |       \\           \n"
         "     /      _9__      \\          \n"
         "    /      /    \\      \\        \n"
         "   /      /      \\      \\       \n"
         "  17     8        10     19       \n"
         "  | \\   / \\      /  \\   / |    \n"
         "  |  \\ /   \\    /    \\ /  |    \n"
         "  |   7     1---2     11  |       \n"
         "  |   |    /     \\    |   |      \n"
         "  |   6----5     3---12   |       \n"
         "  |   |     \\   /     |   |      \n"
         "  |   \\       4      /    |      \n"
         "  |    \\      |     /     |      \n"
         "  \\     15---14---13     /       \n"
         "   \\   /            \\   /       \n"
         "    \\ /              \\ /        \n"
         "    16---------------20           \n"
         "\n");
}


void displayInstructions() {
  printf("Hunt the Wumpus:                                             \n"
         "The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
         "room has 3 tunnels leading to other rooms.                   \n"
         "                                                             \n"
         "Hazards:                                                     \n"
        "1. Two rooms have bottomless pits in them.  If you go there you fall and die.   \n"
        "2. The Wumpus is not bothered by the pits, as he has sucker feet. Usually he is \n"
        "   asleep. He will wake up if you enter his room. When you move into the Wumpus'\n"
        "   room, then he wakes and moves if he is in an odd-numbered room, but stays    \n"
        "   still otherwise.  After that, if he is in your room, he snaps your neck and  \n"
        "   you die!                                                                     \n"
        "                                                                                \n"
        "Moves:                                                                          \n"
        "On each move you can do the following, where input can be upper or lower-case:  \n"
        "1. Move into an adjacent room.  To move enter 'M' followed by a space and       \n"
        "   then a room number.                                                          \n"
        "2. Enter 'R' to reset the person and hazard locations, useful for testing.      \n"
        "3. Enter 'C' to cheat and display current board positions.                      \n"
        "4. Enter 'D' to display this set of instructions.                               \n"
        "5. Enter 'P' to print the maze room layout.                                     \n"
        "6. Enter 'G' to guess which room Wumpus is in, to win or lose the game!         \n"
        "7. Enter 'X' to exit the game.                                                  \n"
        "                                                                                \n"
        "Good luck!                                                                      \n"
        " \n\n");
}


// Prints closing message and closes the program
void gameOver() {
   printf("\nExiting Program ...");
   exit(0);    // game over. close the program
}


// Check if the room is between 1-20
bool validRoomNumber(int room) {
   return room >= 1 && room <= 20;
} 


// Check if a room is next to another room according to the cave array
bool adjacent( int currentRoom,  int destination[3]) {
   return currentRoom == destination[0] || currentRoom == destination[1] || currentRoom == destination[2];
}


// Print the player's new location. If they are now adjacent to a pit or Wumpus, a special script is printed
void printPlayer( int player,  int wumpus,  int pit1,  int pit2,  int cave[20][3]) {  
  printf("You are in room %d. ", player);
  
   // Check if player is adjacent to Wumpus
   if ( adjacent(player, cave[wumpus - 1])) {     // Subtract 1 because array starts indexing at 0
      printf("You smell a stench. ");
   }
  
   // Check if player is adjacent to a pit
   if ( adjacent(player, cave[pit1 - 1]) || adjacent(player, cave[pit2 - 1])) {
      printf("You feel a draft. ");
   }
} // end of printPlayer()


// Allows the user to manually change the room numbers for each player, wumpus, and the pits. Also used for testing
void reset( int *player,  int *wumpus,  int *pit1,  int *pit2,  int cave[20][3]) {
   // Prompt for user when they choose to reset
   printf("Enter the room locations (1..20) for player, wumpus, pit1, and pit2: \n\n");
   scanf(" %d", player);
   scanf(" %d", wumpus);
   scanf(" %d", pit1);
   scanf(" %d", pit2);

   // Make sure the rooms don't overlap. Player shouldn't start with Wumpus and neither should start off down a pit
   bool playerWithWumpus = *wumpus == *player;
   bool playerInAPit = *player == *pit1 || *player == *pit2;
   bool wumpusInAPit = *wumpus == *pit1 || *wumpus == *pit2;
   bool pitsOverlap = *pit1 == *pit2;
   bool validNumbers = validRoomNumber(*player) &&
                        validRoomNumber(*wumpus) &&
                        validRoomNumber(*pit1) &&
                        validRoomNumber(*pit2);

   // Check if the input is valid. If it is, proceed witht the instructions. If not, the function will end here
   if (validNumbers && !playerWithWumpus && !playerInAPit && !wumpusInAPit && !pitsOverlap) {
      printPlayer(*player, *wumpus, *pit1, *pit2, cave);      // print updated player location
   }
   else {
      printf("Invalid input.  Please retry. \n");
   }
} // end of reset()


// Tells the player the current location of each room. 
void cheat( int player,  int wumpus,  int pit1,  int pit2,  int cave[20][3]) {  // Does not require pointer parameters because it's just printing the numbers
   // Message for menu option C (cheating).
   printf("Cheating! Game elements are in the following rooms: \n"
         "Player Wumpus Pit1 Pit2  \n"
         "%4d %7d %5d %5d \n\n", 
         player, wumpus, pit1, pit2);

   printPlayer(player, wumpus, pit1, pit2, cave);   
} // end of cheat()


// Player guesses what room Wumpus is in. They win if correct and game over if they lose
void guessRoom( int wumpus) {
    int guess;
  
   // Prompt for guess of where Wumpus room is
   printf("Enter room (1..20) you think Wumpus is in: ");
   scanf("%d", &guess);

   if (guess == wumpus) {
      printf("You won!\n");
   }
   else {
      printf("You lost.\n");
   }

   gameOver();
} // end guessRoom()


// If player encounters Wumpus, Wumpus kills them or moves to another room
void wumpusMoves( int *wumpus,  int adjacentRooms[3]) {
   int newRoom = adjacentRooms[0];     

   // Look for the smallest room number of the adjacent rooms
   for ( int i = 0; i < 3; i++) {
      if (adjacentRooms[i] > adjacentRooms[0]) {
         newRoom = adjacentRooms[i];
      }
   }

   *wumpus = newRoom;   // Wumpus moves to that room
} // end of wumpusMoves()


void move( int *player,  int *wumpus,  int pit1,  int pit2,  int cave[20][3],  int *moveNumber) {
    int room = 0;     // Set to 0 so it doesn't hold garbage
   scanf(" %d", &room);       // Take in the room number the player wants

   // First check if the move is valid or invalid
   if ( !adjacent(room, cave[*player - 1]) || !validRoomNumber(room)) {   //*player - 1 because cave starts indexing at 0, not 1
      printf("Invalid move.  Please retry. \n"); 
      (*moveNumber)--;     // Does not increase move number   

      printPlayer(*player, *wumpus, pit1, pit2, cave);
   }
   else {
      *player = room;   // update the player room

      // Check if the player has run into Wumpus or fallen into a pit
      if (*player == *wumpus && *player % 2 == 1) {        // if player encounters Wumpus but the room is odd, they survive
         printf("You hear a slithering sound, as the Wumpus slips away. \n"
                "Whew, that was close! \n");

         wumpusMoves(wumpus, cave[*wumpus - 1]);    // Wumpus moves to adjacent room w the 
      }
      else if (*player == *wumpus && *player % 2 == 0) {  // if player encounters Wumpus but the room is even, they die
         printf("You briefly feel a slimy tentacled arm as your neck is snapped. \n"
                "It is over.\n");
         gameOver();
      }
      else if (*player == pit1 || *player == pit2) {      // if player encounters a pit, they fall down and die
         printf("Aaaaaaaaahhhhhh....    \n"
                "    You fall into a pit and die. \n"); 
         gameOver();
      }  
     
      printPlayer(*player, *wumpus, pit1, pit2, cave);
   } // end of outer if-else
} // end of move()


// 8 possible moves user can make: move, reset, cheat, display instructions, print cave, guess room, exit, and invalid move
void evaluateInput( int *player,  int *wumpus,  int *pit1,  int *pit2,  int cave[20][3],   int *moveNumber) { 
   char input = '\0';          // Set equal to \0 so it doesn't hold garbage
   
   // Ask for user input
   printf("\n\n%d. Enter your move (or 'D' for directions): ", *moveNumber);
   scanf(" %c", &input);      // Space before %c to ignore whitespace  
   input = toupper(input);    // Change all inputs to capital letters

   // Moves are determinted by a character
   switch(input) {
   
   case 'X':   // Exit
      gameOver();

   case 'P':   // Print cave
      printCave();
      printPlayer(*player, *wumpus, *pit1, *pit2, cave);    // print player's current location
      break;

   case 'D':   // Directions
      printCave();
      displayInstructions();    
      printPlayer(*player, *wumpus, *pit1, *pit2, cave);    // print player's current location
      break;

   case 'M':   // Move
      move(player, wumpus, *pit1, *pit2, cave, moveNumber);
      (*moveNumber)++;     // Update moveNumber
      break;

   case 'R':   // Reset
      reset(player, wumpus, pit1, pit2, cave);
      break;
   
   case 'C':   // Cheat 
      cheat(*player, *wumpus, *pit1, *pit2, cave);  
      break;
      
   case 'G':   // Guess
      guessRoom(*wumpus);
      (*moveNumber)++;     // Update moveNumber
      break;
      
   default: 
      printf("Invalid move.  Please retry. \n"); 
   }
} // end evaluateInput()


// Starts up the game at the beginning or whenever the game is reset: creates random room numbers, displays the instructions, and prepares for the first move
void start( int *player,  int *wumpus,  int *pit1,  int *pit2,  int cave[20][3]) {
   // srand(time(0));    // Change seed to time(0) to change output every run
   srand(1);
   
   // Generate a random room number (1-20) for the four rooms
   *pit1 = rand() % 20 + 1;      // Using +1 gives random number 1..20 rather than 0..19
   *pit2 = rand() % 20 + 1; 
   *wumpus = rand() % 20 + 1;
   *player = rand() % 20 + 1;     

   // Make sure the rooms don't overlap. Player shouldn't spawn with Wumpus and neither should start off down a pit
   bool playerWithWumpus = *wumpus == *player;
   bool playerInAPit = *player == *pit1 || *player == *pit2;
   bool wumpusInAPit = *wumpus == *pit1 || *wumpus == *pit2;
   bool pitsOverlap = *pit1 == *pit2;
 
   // Chnage the room numbers if they overlap
   while (playerWithWumpus || playerInAPit || wumpusInAPit || pitsOverlap) {
      if (playerWithWumpus || playerInAPit) {
         *player = rand() % 20 + 1;   // Change player away to accomodate the other room numbers
      }
      else if (wumpusInAPit) {    
         *wumpus = rand() % 20 + 1;
      }
      else if (pitsOverlap) {
         *pit1 = rand() % 20 + 1;    // Change the value of one of the pits if they match each other
      }
   } // repeat just in case a new room number happens to equal an existing one

   printPlayer(*player, *wumpus, *pit1, *pit2, cave);    // Print the player's current location
} // end of start()


int main() {
   // Initialize the 4 rooms
    int player = 0;
    int wumpus = 0;
    int pit1 = 0;
    int pit2 = 0;
    int moveNumber = 1;     // What number move the player is at. Updates within evaluateInput()

   // The cave layout. The first [] is the room number and the second [] is the 3 rooms adjacent to that room number.
    int cave[20][3] = {
      {2, 5, 8}, {1, 3, 10}, {2, 4, 12}, {3, 5, 14}, {1, 4, 6},
      {5, 7, 15}, {6, 8, 17}, {1, 7, 9}, {8, 10, 18}, {2, 9, 11},
      {10, 12, 19}, {3, 11, 13}, {12, 14, 20}, {4, 13, 15}, {6, 14, 16},
      {15, 17, 20}, {7, 16, 18}, {9, 17, 19}, {11, 18, 20}, {13, 16, 19}
   };

   // Start gameplay
   start(&player, &wumpus, &pit1, &pit2, cave);

   // Continue asking for user input until game is over
   while (true) {
      evaluateInput(&player, &wumpus, &pit1, &pit2, cave, &moveNumber);  
   }

   return 0;
}