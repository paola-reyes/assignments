/*--------------------------
    Paola Reyes
    3/6/23
    UIC CS 211, Wed 2pm Lab
    Prof. Ellen Kidane
----------------------------
Program 2: Weaver

Weaver is a text-based word game. The user has to try to convert the first
word into the second word by changing one letter at a time.
For example: meat => ball

meat
meal
mell
mall
ball

The user can choose the length of words they want to work with. In the last
example, it is word length of 4. The user can also choose what start and end
words to use, as long as they are of that length. The program reads in words
from a dictionary to make sure the user is using valid words.
*/

#include <ctype.h>   // For tolower()
#include <stdbool.h> // For bool
#include <stdio.h>
#include <stdlib.h> // For malloc(), realloc()
#include <string.h> // For strlen(), strcpy(), strcmp()

// Estimates for how much heap space we should allocate for pointer arrays. Reallocate later as needed.
const int ESTIMATE = 100000;

// Stores a pointer to an array as well as the array's current size
typedef struct
{
  char **array;
  size_t size;
  size_t capacity;
} List;

typedef struct
{
  char *word;
  char **children;
  int size;
  struct WordNode *parent; 
} WordNode;

// Read in the words in "words.txt" and store them in dynamic array
void read(List *dictionary)
{
  char filename[] = "words.txt";
  FILE *filePtr = fopen(filename, "r"); // "r" means we open the file for reading

  // Check that the file was able to be opened
  if (filePtr == NULL) {
    printf("Error: could not open %s for reading\n", filename);
    exit(-1);
  }

  // Read each word from file, and print them one by one
  dictionary->array = (char **)malloc(sizeof(char *) * ESTIMATE); // Allocate space for array
  char inputString[81];

  while (fscanf(filePtr, "%s", inputString) != EOF)
  {
    // Expand the array if needed
    if (dictionary->size == dictionary->capacity)
    {
      dictionary->capacity += ESTIMATE;                                                               // Update capacity
      dictionary->array = (char **)realloc(dictionary->array, sizeof(char *) * dictionary->capacity); // Allocate space for more words
    }

    // Allocate space for the dynamic string
    (dictionary->array)[dictionary->size] = (char *)malloc(sizeof(char) * strlen(inputString) + 1); // Allocate space for that word's size. +1 for \0
    strcpy((dictionary->array)[dictionary->size], inputString);                                     // Add the new word
    (dictionary->size)++;
  }

  fclose(filePtr); // Close the file
} // end of read()

// Find the words of # length within the dictionary
void search(int length, List *words, List *dictionary)
{
  words->array = (char **)malloc(sizeof(char *) * ESTIMATE); // Allocate space for array

  for (size_t i = 0; i < dictionary->size; i++)
  {
    // Check if we need to expand the array
    if (i == words->capacity)
    {
      words->capacity += ESTIMATE;
      words->array = (char **)realloc(words->array, sizeof(char *) * words->capacity); // Allocate space for more words
    }

    // Add words of the chosen length to the list
    if (strlen((dictionary->array)[i]) == length)
    {
      (words->array)[words->size] = (char *)malloc(sizeof(char) * strlen((dictionary->array)[i]) + 1); // Allocate space for that word's size. +1 for \0
      strcpy((words->array)[words->size], (dictionary->array)[i]);
      (words->size)++;
    }
  }
} // end of findWords()

// Check if word exists in the dictionary using binary search
bool found(char *word, List *dictionary)
{
  int low = 0;
  int high = dictionary->size - 1;
  int mid;

  // Look through dictionary in parts
  while (high - low > 1)
  {
    int mid = (low + high) / 2;

    if (strcmp((dictionary->array)[mid], word) < 0)
    {
      low = mid + 1;
    }
    else
    {
      high = mid;
    }
  }

  // Check if word was found
  if (strcmp((dictionary->array)[low], word) == 0)
  {
    return true;
  }
  else if (strcmp((dictionary->array)[high], word) == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
} // end of found()

// Convert word to all lowercase
char *lowercase(char word[])
{
  printf("%zd", strlen(word));
  for (int i = 0; i < strlen(word); i++)
  {
    word[i] = tolower(word[i]);
  }

  return word;
}

// Ask user for the start and end words
void getGameWords(char start[], char end[], int length, List *words, List *dictionary)
{
  bool foundStart = false;
  bool foundEnd = false;

  // Keep looking until we have a word for both
  while (!foundStart && !foundEnd)
  {
    // Get most recent input
    printf("Enter starting and ending words, or 'r' for either for a random word: ");
    scanf("%s", start);
    scanf("%s", end);

    // Pick random word for start
    if (strcmp(start, "r") == 0 || strcmp(start, "R") == 0)
    {
      size_t random = rand() % words->size;
      strcpy(start, (words->array)[random]);
      foundStart = true;
    }

    // Pick random word for end
    if (strcmp(end, "r") == 0 || strcmp(end, "R") == 0)
    {
      size_t random = rand() % words->size;
      strcpy(end, (words->array)[random]);
      foundEnd = true;
    }

    // Print out error messages for invalid words
    if (strlen(start) != length)
    {
      printf("Your word, '%s', is not a %d-letter word. Try again.\n", start, length);
    }
    else if (strlen(end) != length)
    {
      printf("Your word, '%s', is not a %d-letter word. Try again.\n", end, length);
    }
    else if (!found(start, dictionary))
    {
      printf("Your word, '%s', is not a valid dictionary word. Try again.\n", start);
    }
    else if (!found(end, dictionary))
    {
      printf("Your word, '%s', is not a valid dictionary word. Try again.\n", end);
    }
    else
    { // Use user's chosen words
      foundStart = true;
      foundEnd = true;
    }
  } // end of while-loop

  printf("Your starting word is: %s.\n", start);
  printf("Your ending word is: %s.\n", end);
} // end getGameWords()

// Checks if the difference between 2 words is only 1 letter
bool oneCharDif(char *input, char *prevWord)
{
  int count = 0;

  // Loop through both words
  for (int i = 0; i < strlen(prevWord); i++)
  {
    if (prevWord[i] != input[i])
    {
      count++;
    }
  }

  return count == 1;
} // end of oneCharDif()

// User is making moves to solve the puzzle
void move(char *start, char *end, int length, List *dictionary)
{
  int moveNum = 1;
  char prevWord[81] = "\0";
  char input[81] = "\0";
  strcpy(prevWord, start); // Start is the first "previous word"

  printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ", moveNum, prevWord, end);
  scanf("%s", input);

  // While the user doesn't input the quit token, 'q'
  while (strcmp(input, "q") != 0 && strcmp(input, "Q") != 0)
  {
    // Check if input is valid
    if (strlen(input) != length)
    {
      printf("Your word, '%s', is not a %d-letter word. Try again.\n", input, length);
    }
    else if (!found(input, dictionary))
    {
      printf("Your word, '%s', is not a valid dictionary word. Try again.\n", input);
    }
    else if (!oneCharDif(input, prevWord))
    {
      printf("Your word, '%s', is not exactly 1 character different. Try again.\n", input);
    }
    // Check if user won
    else if (strcmp(input, end) == 0)
    {
      printf("Congratulations! You changed '%s' into '%s' in %d moves.\n", start, end, moveNum);
      break;
    }
    else
    { // Update move number and previous word
      moveNum++;
      strcpy(prevWord, input);
    }

    // Print current status of game
    printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ", moveNum, prevWord, end);
    scanf("%s", input);
  } // end of while-loop
} // end of move()

void solution(int start, int end, WordNode *tree, int treeSize)
{ 
  int size = tree[0].size; // assume all nodes have the same number of children
  int visited[treeSize];
  memset(visited, 0, sizeof visited);

  int queue[treeSize];
  int front = 0, rear = 0;
  queue[rear++] = start;

  int parents[treeSize]; // array to store the parent node of each node in the tree
  memset(parents, -1, sizeof parents); // initialize all parent nodes to -1

  queue[front++] = start;

  while (front < rear) {
    int index = queue[front++];

    if (index == end) {
      // Found the end node, print the path
      printf("%s ", tree[end].word);

      int parentIndex = parents[end];
      while (parentIndex != start) {
        printf("%s ", tree[parentIndex].word);
        parentIndex = parents[parentIndex];
      }

      printf("%s\n", tree[start].word);
      return;
    }

    visited[index] = 1;

    for (int i = 0; i < treeSize; i++) {
      if (!visited[i] && oneCharDif(tree[index].word, tree[i].word)) {
        parents[i] = index; // set the parent of the child node
        queue[rear++] = i;
      }
    }
  }

  printf("No path found.\n");
}

// Free all the array pointers and set them to NULL
void freeMem(List *obj)
{
  // Free all array elements
  for (int i = 0; i < obj->size; i++)
  {
    free((obj->array)[i]);
    (obj->array)[i] = NULL;
  }

  // Free the array pointer
  free(obj->array);
  obj->array = NULL;
}

int main()
{
  // Welcome message
  printf("Weaver is a game where you try to find a way to get from the "
         "starting word to the ending word.\n");
  printf("You can change only one letter at a time, and each word along the "
         "way must be a valid word.\n");
  printf("Enjoy!\n\n");

  // Settings for whether user will play again. Determined later on
  // srand(1);
  bool changeWordSize = true;
  bool exit = false;

  // Initialize array, size, and capacity
  List dictionary = {NULL, 0, ESTIMATE};
  List sameSizeWords = {NULL, 0, ESTIMATE};
  int length = 0;    // User's chosen word length
  read(&dictionary); // Read dictionary and store values

  WordNode *tree;
  int treeIndex = 0;

  while (!exit)
  {
    // Ask the user for desired word length
    if (changeWordSize)
    {
      // Reset words object to default values if needed
      if (sameSizeWords.size > 0)
      {
        freeMem(&sameSizeWords);
        sameSizeWords.size = 0;
        sameSizeWords.capacity = ESTIMATE;
      }

      // Get word size and print the # of dictionary words with that length
      printf("How many letters do you want to have in the words? ");
      scanf("%d", &length);
      search(length, &sameSizeWords, &dictionary);
      printf("Number of %d-letter words found: %zd.\n\n", length, sameSizeWords.size);

      // Make a tree of all the sameSizeWords and their one char dif words
      tree = (WordNode *)malloc(sizeof(WordNode) * dictionary.size);

      // Go through the sameSizeWords List and make a WordNode for each word
      for (int i = 0; i < sameSizeWords.size; i++) {
        WordNode parent;
        parent.word = sameSizeWords.array[i];
        parent.parent = NULL;

        // Allocate space in the WordNode's 2D dynamic array
        parent.children = (char **)malloc(sizeof(char *) * sameSizeWords.size);
        for (int i = 0; i < sameSizeWords.size; i++) {
          parent.children[i] = (char *)malloc(sizeof(char) * length);
        }

        int childIndex = 0;

        // If we find a oneCharDif word, add it to the children array
        for (int i = 0; i < sameSizeWords.size; i++) {
          if (oneCharDif(sameSizeWords.array[i], parent.word)) {
            strcpy(parent.children[childIndex++], sameSizeWords.array[i]);
          }
        }

        if (childIndex == 0) {
          parent.children = NULL;
        }

        tree[treeIndex++] = parent;
      }
    }

    // Ask user for start and end words
    char start[81] = "\0";
    char end[81] = "\0";
    getGameWords(start, end, length, &sameSizeWords, &dictionary);

    int startIndex = -1;
    int endIndex = -1;

    for (int i = 0; i < sameSizeWords.size; i++) {
      if ( strcmp(sameSizeWords.array[i], start) == 0) {
        startIndex = i;
      }

      if ( strcmp(sameSizeWords.array[i], end) == 0) {
        endIndex = i;
      }
    }

    solution(startIndex, endIndex, tree, treeIndex);

    // Game is over. Ask for next direction
    printf("\nEnter: \t1 to have another puzzle solved,\n");
    printf("\t2 to change the number of letters in the words and then have another puzzle solved, or\n");
    printf("\t3 to exit the program.\n");
    printf("Your choice --> ");

    int direction = 0;
    scanf("%d", &direction);

    if (direction == 1)
    {
      changeWordSize = false;
    }
    else if (direction == 2)
    {
      changeWordSize = true;
    }
    else if (direction == 3)
    {
      exit = true;
    }
  } // end of while-loop

  printf("\nThanks for playing!\n");
  printf("Exiting...\n");

  // Free arrays and set them to NULL
  freeMem(&dictionary);
  freeMem(&sameSizeWords);

  return 0;
}