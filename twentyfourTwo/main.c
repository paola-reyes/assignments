/*--------------------------
    Paola Reyes
    4/12/23
    UIC CS 211, Wed 2pm Lab
    Prof. Ellen Kidane
----------------------------    
Project 3 - Twenty Four Two

Twenty Four is a math game where the user wants make a total of 24 given only 4 numbers.

The program picks a random puzzle set of 4 numbers and the user must pick 3 math operators 
(+, -, *, /) to go in between them. 

For example: The numbers to use are: 2, 8, 7, 8
If the user types +++  the program runs 2 + 8 + 7 + 8 = 25. It is not 24, so this is not correct
If the user types +-*, the program runs 2 + 8 / 7 + 8 = 24 (ignoring PEMDAS). This is correct

The program will ask the user if they want to keep playing and will continue or end accordingly.
This is the default mode that the program runs called "Easy Mode". Easy Mode pulls a random puzzle
from an array of only 10 puzzles.
*/
#include <stdio.h>
#include <stdbool.h>   
#include <stdlib.h>   // For malloc()
#include <string.h>   // For strlen()
#include <math.h>     // For fabs()
#include <ctype.h>    // For isdigit()


/// @brief Linked list that will store each item in the user's solution
typedef struct Node *NodePtr;
struct Node {
    char value;
    NodePtr next;
};


/// @brief Reads the given file with all the puzzles. Stores the data in an array
/// @return 2D dynamic integer array. Each row is 1 puzzle
int** read(char filename[]) 
{
    FILE *pFile = fopen(filename, "r");

    // Check if we encountered any errors
    if (pFile == NULL) {
        printf("Error: could not open %s for reading\n", filename);
        exit(-1);
    }

    // Make a 2D dynamic array. Allocate space so we can return the array. Enough space for 25 puzzles
    int **puzzles = (int**) malloc(sizeof(int*) * 25);    

    // Allocate space in each row in the array. Enough for 4 numbers
    for (int i = 0; i < 25; i++) {
        puzzles[i] = (int*) malloc(sizeof(int) * 4);
    }

    int i = 0;
    char input[81];
    
    // Read the file line by line
    while ( fgets( input, 81, pFile)) 
    {
        // Add numbers to the list. Convert chars to int
        puzzles[i][0] = input[0] - '0';
        puzzles[i][1] = input[2] - '0';
        puzzles[i][2] = input[4] - '0';
        puzzles[i][3] = input[6] - '0';   

        i++;
    }

    fclose(pFile);  // Close file

    return puzzles;
}


/// @brief Adds valid input into the linked list
/// @param input A character in the user's solution. May be an operator or a number
/// @param pNode Head pointer of the linked list
void push(char input, NodePtr pNode) 
{
    NodePtr new = (NodePtr) malloc(sizeof(NodePtr));
    new->value = input;
    new->next = NULL;

    // Traverse to the end of the linked list
    while (pNode != NULL) {
        pNode = pNode->next;
    }

    // Add the new node to the end
    pNode->next = new;
}


/// @brief Remove the last node of the linked list
/// @param pNode Head pointer of the linked list
char pop(NodePtr pNode) 
{
    // Traverse to the penultimate node
    while (pNode->next != NULL) {
        pNode = pNode->next;
    }

    // Delete the last node
    NodePtr temp = pNode->next;
    char val = temp->value;     // Save the value
    free(temp);
    temp = NULL;

    // Make this node the last one
    pNode->next = NULL;
    
    return val;
}


/// @brief Calcuates an expression
/// @param operator +, -, *, /
/// @return Answer
double calculate(NodePtr pNode) {
    int x, y = 0;
    char operator = '\0';

    // Begin calculating what we have
    while (pNode->value != '(') {
        x = pop(pNode) - '0';    // Convert to int
        operator = pop(pNode);   // Operator
        y = pop(pNode) - '0';    // Other int
        
        switch (operator) {
            case '+':
                return x + y;
            case '-':
                return x - y;
            case '*':
                return x * y;
            case '/':
                return x / y; // Cast as double to for accurate division
        };
    }

    pop(pNode);  // Remove '('
    return 0;
}


/// @brief Checks if the user's input gives 24 based on the random puzzle values
/// @return Whether it was a valid solution/should user try again
bool evaluate(int puzzle[], char solution[]) 
{

    NodePtr head = NULL;
    char val, operator = '\0';
    double total = 0;
    int x, y, j = 0;

    for (int i = 0; i < strlen(solution); i++) {
        val = solution[i];

        if ( isdigit(val) ) {
            // Make sure the numbers are in the right order
            if (val == puzzle[j++]) {
                push(val, head);
            }
            else {
                printf("Error! Invalid operator. Please try again.\n");
                return false;
            }
        }
        else if (val == '+' || val == '-' || val == '*' || val == '/' || val == '(') {
            push(val, head);
        }
        else if (val == ')') {
            // Calculate what we have
            total += calculate(head);
        }
        else if (val == ' ') {
            ;   // Skip whitespace
        }
        else {
            printf("Error! Invalid operator. Please try again.\n");
            return false;
        }
    }

    return fabs(24 - total) < 0.0000001f;
}


/// @brief Default mode for the game. Takes puzzles from "easy.txt"
void easyMode() 
{
    char choice = 'Y';                  // Whether or not the program should keep going
    char solution[81];                  // User's input
    int **list = read("easy.txt");      // Take in the values from the file
    int numPuzzles =  sizeof(list) / sizeof(list[0]);

    // Pick a random puzzle
    int i = rand() % numPuzzles;
    int puzzle[4] = { list[i][0], list[i][1], list[i][2], list[i][3] };
    printf("The numbers to use are %d, %d, %d, and %d.\n", puzzle[0], puzzle[1], puzzle[2], puzzle[3]);
    printf("Enter your solution: ");
    scanf("%s", solution);
    
    // Check if input is valid. Perform appropriate functions
    bool win = evaluate(puzzle, solution);

    if (win) {
        printf("Well done! You are a math genius!\n");
    }
    else {
        printf("Sorry. Your solution did not evaluate to 24.\n");
    }

    // Free the dynamic array memory
    for (int i = 0; i < numPuzzles; i++) {
        free(list[i]);
        list[i] = NULL;
    }

    free(list);
    list = NULL;
} 


/// @brief Takes puzzles from "medium.txt"
void mediumMode() {
    char choice = 'Y';                  // Whether or not the program should keep going
    char solution[81];                  // User's input
    int **list = read("medium.txt");    // Take in the values from the file
    int numPuzzles =  sizeof(list) / sizeof(list[0]);

    // The user presses any key to keep playing or N to stop the game. Lowercase 'n' doesn't count
    while (choice != 'N') 
    {
        // Pick a random puzzle
        int i = rand() % numPuzzles;
        int puzzle[4] = { list[i][0], list[i][1], list[i][2], list[i][3] };
        
        // Print the puzzle we'll be using
        printf("The numbers to use are: %d, %d, %d, %d.\n", puzzle[0], puzzle[1], puzzle[2], puzzle[3]);   
        printf("Enter your solution: ");
        scanf("%s", solution);

        // Check if input is valid. Perform appropriate functions
        evaluate(solution);

        // Ask for input again
        printf("Play again? ");
        scanf("%c", choice);
    }

    // Game ended and close program
    printf("\nThanks for playing!\n");
    
    // Free the dynamic array memory
    for (int i = 0; i < numPuzzles; i++) {
        free(list[i]);
        list[i] = NULL;
    }

    free(list);
    list = NULL;
}


/// @brief Takes puzzles from "hard.txt"
void hardMode() {
    char choice = 'Y';               // Whether or not the program should keep going
    int **list = read("hard.txt");   // Store the values from the file
    int numPuzzles =  sizeof(list) / sizeof(list[0]);

    // The user presses any key to keep playing or N to stop the game. Lowercase 'n' doesn't count
    while (choice != 'N') 
    {
        // Pick a random puzzle
        int i = rand() % numPuzzles;
        int puzzle[4] = { list[i][0], list[i][1], list[i][2], list[i][3] };
        
        // Print the puzzle we'll be using
        printf("\nThe numbers to use are: %d, %d, %d, %d", puzzle[0], puzzle[1], puzzle[2], puzzle[3]);   
        printf(".\n");

        printf("Play again? ");
        scanf("%c", choice);
    }

    // Game ended and close program
    printf("\nThanks for playing!\n");

    // Free the dynamic array memory
    for (int i = 0; i < numPuzzles; i++) {
        free(list[i]);
        list[i] = NULL;
    }

    free(list);
    list = NULL;
} 


int main(int argc, char *argv[]) {
    srand(1);

    // Welcome message
    printf("Welcome to the game of TwentyFour.\n");
    printf("Use each of the four numbers shown below exactly once,\n");
    printf("combining them somehow with the basic mathematical operators (+,-,*,/)\n");
    printf("to yield the value twenty-four.\n");
    printf("Choose your difficulty level: E for easy, M for medium, and H for hard (default is easy).\n");
    printf("Your choice --> ");

    char mode = '\0';
    scanf("%c", &mode);
    
    // If there is no arguments, the default is Easy Mode on
    switch (mode) 
    {
        case 'E':
            easyMode();
            break;
        
        case 'M':
            mediumMode();
            break;

        case 'H':
            hardMode();
            break;

        default:
            easyMode();
    }    

    int choice = 0;
    while (choice != 3)
        // Prompt user for input
        printf("Enter: \t1 to play again,\n");
        printf("\t2 to change the difficulty level and then play again, or\n");
        printf("\t3 to exit the program.\n");
        printf("Your choice --> ");
        scanf("%c", &mode);

    printf("\nThanks for playing!\n");
	printf("Exiting...\n");

    return 0;
}