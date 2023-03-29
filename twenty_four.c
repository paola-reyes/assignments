/*--------------------------
    Paola Reyes
    2/8/23
    UIC CS 211, Wed 2pm Lab
    Prof. Ellen Kidane
----------------------------    
Project 1 - Twenty Four

Twenty Four is a math game where the user wants make a total of 24 given only 4 numbers.

The program picks a random puzzle set of 4 numbers and the user must pick 3 math operators 
(+, -, *, /) to go in between them. 

For example: The numbers to use are: 2, 8, 7, 8
If the user types +++  the program runs 2 + 8 + 7 + 8 = 25. It is not 24, so this is not correct
If the user types +-*, the program runs 2 + 8 / 7 + 8 = 24 (ignoring PEMDAS). This is correct

The program will ask the user if they want to keep playing and will continue or end accordingly.
This is the default mode that the program runs called "Easy Mode". Easy Mode pulls a random puzzle
from an array of only 10 puzzles.

There are 2 more modes the user can choose. 

One is by turning off Easy Mode, which pulls a random puzzle from an array of 3188 puzzles.
In this game, there are 3188 usable puzzle sets. This increases the game's difficulty. 
The user turns Easy Mode off using the command terminal argument -e 0

For example: 
gcc main.c
./a.out -e 0

The other mode is Debug Mode, which prints out the answers to all 3188 puzzles before running the game.
This is turned on using the command argument -d 1

For example: 
gcc main.c
./a.out -d 1

The user can turn Easy Mode off and Debug Mode on using ./a.out -d 1 -e 0
*/
#include <stdio.h>
#include <stdlib.h>   // For malloc()
#include <string.h>   // For strlen()
#include <math.h>     // For fabs()

int max = 3188;

// For double comparisons. Checks if total equals 24
int equal24(double total) { 
  return fabs(24 - total) < 0.0000001f; 
}


// Helper function to operation(). It does an operation with just 2 numbers and 1 operator. 
// For example, operationHelper(1, 2, '+') does 1 + 2 and returns 3;
double operationHelper(double x, double y, char operator) {
  switch (operator) {
  case '+':
    return x + y;
  case '-':
    return x - y;
  case '*':
    return x * y;
  case '/':
    return x / y; // Cast as double to for accurate division
  }
} // end of operationHelper()


// Does 3 oeprations by calling operationHelper. 
double operation(int a, int b, int c, int d, char operator1, char operator2, char operator3) {
  double total = operationHelper((double)a, (double)b, operator1);  // For calculating in the correct order
  total = operationHelper(total, (double)c, operator2);
  total = operationHelper(total, (double)d, operator3);

  return total;
} // end of oepration()


// Helper function to findSolutions(). Goes through all the possible operator combinations for 1 given puzzle set. 
// The numbers that are solutions to 24 are added to the allSolutions array, which we'll use if Easy Mode is off.
// The solution is also added as a string to allSolutionsStrings, which we'll print if in Debug Mode.
void findSolutionsHelper(int a, int b, int c, int d, 
                         int *arrayIndex,   // Keeps track of how many arrays are in the 2D arrays so far
                         int ****allSolutions, char ****allSolutionsStrings) {   // 2D dynamic arrays that are located in main() 
  char operators[] = {'+', '-', '*', '/'};

  // Nested for-loop for every operator combination. It runs 4^3 or 64 combinations.
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        if (equal24(operation(a, b, c, d, operators[i], operators[j], operators[k]))) {   // If the total = 24
          (**allSolutions)[*arrayIndex][0] = a;   // Add puzzle numbers to allSolutions array
          (**allSolutions)[*arrayIndex][1] = b;
          (**allSolutions)[*arrayIndex][2] = c;
          (**allSolutions)[*arrayIndex][3] = d;

          (**allSolutionsStrings)[*arrayIndex][0] = (char)(a + '0');  // Add char by char to allSolutionsStrings
          (**allSolutionsStrings)[*arrayIndex][1] = operators[i];
          (**allSolutionsStrings)[*arrayIndex][2] = (char)(b + '0');
          (**allSolutionsStrings)[*arrayIndex][3] = operators[j];
          (**allSolutionsStrings)[*arrayIndex][4] = (char)(c + '0');
          (**allSolutionsStrings)[*arrayIndex][5] = operators[k];
          (**allSolutionsStrings)[*arrayIndex][6] = (char)(d + '0');
          (*arrayIndex)++;    // Increment to the next index
        } // end of if()
      } // end for-loop 3
    } // end for-loop 2
  } // end for-loop 1
} // end of findSolutions()


// This goes through all the possible number combination to find all the possible solutions.
// There are a total of 3188 possible solutions for the game.
void findSolutions(int ***allSolutions, char ***allSolutionsStrings) {
  int arrayIndex = 0;   // Keeps track of how many arrays are in the 2D arrays so far

  // Nested for-loops to find every combination 4 numbers from 1-9. It runs 9^4 or 6561 combinations
  for (int a = 1; a < 10; a++) {
    for (int b = 1; b < 10; b++) {
      for (int c = 1; c < 10; c++) {
        for (int d = 1; d < 10; d++) {
          findSolutionsHelper(a, b, c, d, &arrayIndex, &allSolutions, &allSolutionsStrings);
        }
      } // end for loop 4
    }// end for loop 3
  }  // end for loop 2
} // end for loop 1


// Checks if the user's input gives 24 based on the random puzzle values
void evaluateInput(int a, int b, int c, int d, char *playAgain) {
  // The three operations the user chooses. We're reading it as a string to avoid buffer problems from invalid input
  char input[10] = "\0";
  int validInput = 0;   // If input is valid

  printf("Enter the three operators to be used, in order (+, -, *, or /): ");
  scanf("%s", input);

  // User shouldn't input too few or too many operators
  if (strlen(input) != 3) { 
    printf("Error! The number of operators is incorrect. Please try again.\n");
  }
  // Check if each operator is either +, -, *, /
  else if ((input[0] == '+' || input[0] == '-' || input[0] == '*' || input[0] == '/') &&
           (input[1] == '+' || input[1] == '-' || input[1] == '*' || input[1] == '/') &&
           (input[2] == '+' || input[2] == '-' || input[2] == '*' || input[2] == '/')) {
    validInput = 1;
  } 
  else {    // Not valid input
    printf("Error! Invalid operator entered. Please try again.\n");
  }

  // Read input
  if (validInput) {   
    char operator1 = input[0];
    char operator2 = input[1];
    char operator3 = input[2];

    // Display the operation for the user. It prints [num] [operator] [num] = [total]
    // Convert operationHelper() to int so we don't get decimal
    printf("%d %c %d = %d.\n", a, operator1, b, (int) operationHelper(a, b, operator1));    
    int total = operationHelper(a, b, operator1);

    printf("%d %c %d = %d.\n", total, operator2, c, (int) operationHelper(total, c, operator2));
    total = operationHelper(total, c, operator2);

    printf("%d %c %d = %d.\n", total, operator3, d, (int) operationHelper(total, d, operator3));

    // Check for 24
    if (equal24(operation(a, b, c, d, operator1, operator2, operator3))) { // Correct answer
      printf("Well done! You are a math genius.\n");
    } 
    else {
      printf("Sorry. Your solution did not evaluate to 24.\n"); // Incorrect
    }

    // Determine if user wants to keep playing
    printf("\nWould you like to play again? Enter N for no and any other character for yes. ");
    scanf(" %c", &(*playAgain)); // Update playAgain
  } // end of if()
} // end of evaluateInput()


// Start the game and determine if the user wants to keep playing
void easyMode(int (*easyPuzzles)[10][4]) {
  char playAgain = 'Y';             // Whether or not the program should keep going
  int a, b, c, d, randomIndex = 0;  // Values of a random puzzle

  // The user presses any key to keep playing or N to stop the game. Lowercase 'n' doesn't count
  while (playAgain != 'N') {
    randomIndex = rand() % 10;  // Pick a random puzzle

    // Get the numbers from that puzzle
    a = (*easyPuzzles)[randomIndex][0];
    b = (*easyPuzzles)[randomIndex][1];
    c = (*easyPuzzles)[randomIndex][2];
    d = (*easyPuzzles)[randomIndex][3];
    
    // Print the puzzle we'll be using
    printf("\nThe numbers to use are: %d, %d, %d, %d", a, b, c, d);   
    printf(".\n");
    evaluateInput(a, b, c, d, &playAgain);
  }

  // Game ended and close program
  printf("\nThanks for playing!\n");
} // end of easyMode()


// The same as easyMode() but it allows a 2D dynamic array as a parameter
void hardMode(int ***allSolutions) {
  char playAgain = 'Y';             // Whether or not the program should keep going
  int a, b, c, d, randomIndex = 0;  // Values of a random puzzle

  // The user presses any key to keep playing or N to stop the game. Lowercase 'n' doesn't count
  while (playAgain != 'N') {
    randomIndex = rand() % max;  // Pick a random puzzle

    // Get the numbers from that puzzle
    a = (*allSolutions)[randomIndex][0];
    b = (*allSolutions)[randomIndex][1];
    c = (*allSolutions)[randomIndex][2];
    d = (*allSolutions)[randomIndex][3];
    
    // Print the puzzle we'll be using
    printf("\nThe numbers to use are: %d, %d, %d, %d", a, b, c, d);   
    printf(".\n");
    evaluateInput(a, b, c, d, &playAgain);
  }

  // Game ended and close program
  printf("\nThanks for playing!\n");
} // end of hardMode()


// Allocate space for two 2D arrays that hold all the puzzle solutions.
void allocateMemory(int ***allSolutions, char ***allSolutionsStrings) {
  *allSolutions = malloc(sizeof(int*) * max);
  *allSolutionsStrings = malloc(sizeof(char*) * max);    // Stored as strings to print in Debug Mode

  // Allocate memory to each index
  for (int i = 0; i < max; i++) {    
    (*allSolutions)[i] = malloc(sizeof(int) * 4);
    (*allSolutionsStrings)[i] = malloc(sizeof(char) * 7);  // 7 because the strings are made up of 4 numbers and 3 operators
  }
} // end of allocateMemory()


void freeMemory(int ***allSolutions, char ***allSolutionsStrings) {
  // Deallocate memory of each index
  for (int i = 0; i < max; i++) {    
    free((*allSolutions)[i]);
    free((*allSolutionsStrings)[i]);
    
    (*allSolutions)[i] = NULL;
    (*allSolutionsStrings)[i] = NULL;
  }

  // Free the pointer arrays
  free(*allSolutions);
  free(*allSolutionsStrings);
  *allSolutions = NULL;
  *allSolutionsStrings = NULL;
} // end of freeMemory()


// Prints all the solutions in allSolutionsStrings[3188][7]
void debugMode(char ***allSolutionsStrings) {
  for (int i = 0; i < max; i++) {
    printf("%d. ", i + 1);    // Print count

    for (int j = 0; j < 7; j++) { 
      printf("%c", (*allSolutionsStrings)[i][j]);
    }
    printf("\n");
  }
} // end of debugMode


// We will use argc and argv[] to take in commands from the terminal. The command is turning on/off debug mode and easy mode. 
// -d 1 = Turn Debug Mode on   ||   -d 0 = Turn Debug Mode off  ||   -e 1 = Turn Easy Mode on   ||   -e 0 = Turn Easy Mode off 
// argv[1][0] = '-'    ||   argv[1][1] = 'd' or 'e'   ||   argv[2] = '0' or '1'
int main(int argc, char *argv[]) {
  srand(1);

  // Welcome message
  printf("Welcome to the game of TwentyFour.\n");
  printf("Use each of the four numbers shown below exactly once,\n");
  printf("combining them somehow with the basic mathematical operators (+,-,*,/)\n");
  printf("to yield the value twenty-four.\n");

  // 10 puzzles that we'll use in Easy Mode. These are the default settings
  int easyPuzzles[10][4] = {
      {3, 9, 4, 1}, {8, 5, 8, 1}, {6, 1, 5, 1}, {2, 8, 7, 8}, {5, 2, 9, 2},
      {2, 6, 8, 4}, {5, 5, 4, 3}, {6, 6, 2, 6}, {8, 4, 2, 6}, {6, 2, 8, 1}};
  
  // If there is no arguments, the default is Easy Mode on
  if (argc < 2) {    
    easyMode(&easyPuzzles);
  } 
  else {
    // Only generate once since Debug Mode and "Hard" Mode may not be on at the same time 
    int generatedSolutions = 0;
    int **allSolutions = NULL;
    char **allSolutionsStrings = NULL;   

    // Iterate through argv[]
    for (int i = 1; i < argc; i += 2) { 

      // Invalid syntax, no "-" before option
      if (argv[i][0] != '-') {          
        printf("error! :( pls try again\n");
      }

      // Turn on Debug Mode
      if (argv[i][1] == 'd' && argv[i + 1][0] == '1') { 
        // The user might have turned off Easy Mode + generated solutions before this.
        if (!generatedSolutions) { 
          allocateMemory(&allSolutions, &allSolutionsStrings);
          findSolutions(&allSolutions, &allSolutionsStrings);
          generatedSolutions = 1;   // Change to true
        }

        debugMode(&allSolutionsStrings);

        // If there are no more arguments, run the default Easy Mode
        if (argc <= 3) {
          easyMode(&easyPuzzles);
        }
      }

      // Turn on/off Easy Mode
      if (argv[i][1] == 'e') {
        if (argv[i + 1][0] == '1') {  // Easy Mode on
          easyMode(&easyPuzzles);
        }

        if (argv[i + 1][0] == '0') {  // Easy Mode off
          // The user might have turned on Debug Mode before this.
          if (!generatedSolutions) { 
            allocateMemory(&allSolutions, &allSolutionsStrings);
            findSolutions(&allSolutions, &allSolutionsStrings);
            generatedSolutions = 1;   // Change to true
          }

          hardMode(&allSolutions);
        }
      } 
    } // end of for loop

    // Free the 2D dynamic arrays
    freeMemory(&allSolutions, &allSolutionsStrings);
  } // end of if-else

  return 0;
}
