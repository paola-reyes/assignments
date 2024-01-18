/*--------------------------
    Paola Reyes
    4/30/23
    UIC CS 211, Wed 2pm Lab
    Prof. Ellen Kidane
----------------------------    
Project 4 - Student Database

This program uses a linked list to implement a database of students.
The data we store inludes name, ID, GPA, and total credit hours. Using
this information, we also determin the students' grade level and if they 
are on the Honor Roll or Academic Probation. 
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	char* name;
	char* id;
	double gpa;
	int creditHours;
} Student;

typedef struct StudentNode {
	Student* pStudent;
	struct StudentNode* pNext;
} StudentNode;

typedef struct {
	StudentNode* pIDList;
	StudentNode* pHonorRollList;
	StudentNode* pAcademicProbationList;
	StudentNode* pFreshmanList;
	StudentNode* pSophomoreList;
	StudentNode* pJuniorList;
	StudentNode* pSeniorList;
} Database;


// Print the list in order
void printList(StudentNode **pHead) {
    StudentNode *pCurrent = *pHead;

    // Check if the list is empty
    if (pCurrent == NULL) {
        printf("There are no students matching that criteria.\n\n");
        return ;    // End function here
    }

    // Go through every Student in the list
    while (pCurrent != NULL) {
        // Print out their data
        printf("%s:\n", pCurrent->pStudent->name);
        printf("\tID - %s\n", pCurrent->pStudent->id);
        printf("\tGPA - %.2f\n", pCurrent->pStudent->gpa);
        printf("\tCredit Hours - %d\n", pCurrent->pStudent->creditHours);

        pCurrent = pCurrent->pNext;
    }
}


// Add student to the ID list
void addByID(Student **newStudent, StudentNode **pHead)
{
    // Make a new node for this student
    StudentNode *newNode = malloc(sizeof(StudentNode));
    newNode->pStudent = *newStudent;
    newNode->pNext = NULL;

    // Empty list
    if (*pHead == NULL) {
        *pHead = newNode;
    }
    // If we need to prepend to the list
    else if (strcmp(newNode->pStudent->id, (*pHead)->pStudent->id) < 0) {
        newNode->pNext = *pHead;
        *pHead = newNode;
    }
    else {
        // The node is in the middle of the list
        StudentNode* pCurrent = *pHead;
        while (pCurrent->pNext != NULL && strcmp(newNode->pStudent->id, pCurrent->pNext->pStudent->id) >= 0) {
            pCurrent = pCurrent->pNext;
        }
        newNode->pNext = pCurrent->pNext;
        pCurrent->pNext = newNode;
    }
}
  

// Sort student into given list by comapring GPA
void addByGPA(Student **newStudent, StudentNode **pHead) 
{
    // Make a new node for this student
    StudentNode *newNode = malloc(sizeof(StudentNode));
    newNode->pStudent = *newStudent;
    newNode->pNext = NULL;

    // Empty list
    if (*pHead == NULL) {
        *pHead = newNode;
    }
    // If we need to prepend to the list
    else if (newNode->pStudent->gpa <= (*pHead)->pStudent->gpa ) {
        newNode->pNext = *pHead;
        *pHead = newNode;
    }
    else {
        // The node is in the middle of the list
        StudentNode* pCurrent = *pHead;
        while (pCurrent->pNext != NULL && newNode->pStudent->gpa > pCurrent->pNext->pStudent->gpa) {
            pCurrent = pCurrent->pNext;
        }
        newNode->pNext = pCurrent->pNext;
        pCurrent->pNext = newNode;
    }
}


// Sort student into the givel list by comparing first names
void addByFirstName(Student **newStudent, StudentNode **pHead) 
{
    // Make a new node for this student
    StudentNode *newNode = malloc(sizeof(StudentNode));
    newNode->pStudent = *newStudent;
    newNode->pNext = NULL;

    // Empty list
    if (*pHead == NULL) {
        *pHead = newNode;
    }
    // If we need to prepend to the list
    else if (strcmp(newNode->pStudent->name, (*pHead)->pStudent->name) < 0) {
        newNode->pNext = *pHead;
        *pHead = newNode;
    }
    else {
        // The node is in the middle of the list
        StudentNode* pCurrent = *pHead;
        while (pCurrent->pNext != NULL && strcmp(newNode->pStudent->name, pCurrent->pNext->pStudent->name) >= 0) {
            pCurrent = pCurrent->pNext;
        }
        newNode->pNext = pCurrent->pNext;
        pCurrent->pNext = newNode;
    }
}


// Append a StudentNode to the ID, Grade, and appropriate GPA lists. Add them in sorted order
void addStudent(Student *newStudent, Database **pDatabase) 
{
    // Add the student to the ID list
    addByID(&newStudent, &((*pDatabase)->pIDList));

    // Add them to the Honor Roll list if needed. Sort by GPA
    if (newStudent->gpa >= 3.50) {
        addByGPA(&newStudent, &((*pDatabase)->pHonorRollList));
    }

    // Add them to the Academic Probation list if needed. Sort by GPA
    if (newStudent->gpa < 2.0) {
        addByGPA(&newStudent, &((*pDatabase)->pAcademicProbationList));
    }

    // Add them to the appropriate grade level list. Sort by first name
    if (newStudent->creditHours >= 0 && newStudent->creditHours <= 29) {          // Freshman
        addByFirstName(&newStudent, &((*pDatabase)->pFreshmanList));
    }
    else if (newStudent->creditHours >= 30 && newStudent->creditHours <= 59) {    // Sophomore
        addByFirstName(&newStudent, &((*pDatabase)->pSophomoreList));
    }
    else if (newStudent->creditHours >= 60 && newStudent->creditHours <= 89) {    // Junior
        addByFirstName(&newStudent, &((*pDatabase)->pJuniorList));
    }
    else {    
        addByFirstName(&newStudent, &((*pDatabase)->pSeniorList));                // Senior
    }
}


// Read a file's information and add each Student to the database. Return the database we made
void read(char *file, Database *pDatabase) {
    FILE *pFile = fopen(file, "r");

    if (pFile == NULL) {
        printf("Error: could not open %s for reading\n", file);
        exit(-1);
    }

    char line[81];
    fgets(line, 81, pFile);     // Skip the first line, which we don't need

    // Read the file in format Name,ID,GPA,Credit Hours Taken
    while (fgets(line, 81, pFile) != NULL) 
    {   
        // Add those values to the Student
        Student *newStudent = malloc(sizeof(Student));
        newStudent->name = (char*) malloc(sizeof(char) * 81);
        newStudent->id = (char*) malloc(sizeof(char) * 81);

        // Store the info separated by the comma delimiter
        char gpaStr[81], hoursStr[81];
        strcpy(newStudent->name, strtok(line, ","));
    
        strcpy(newStudent->id, strtok(NULL, ","));

        strcpy(gpaStr, strtok(NULL, ","));
        newStudent->gpa = strtod(gpaStr, NULL);
        
        strcpy(hoursStr, strtok(NULL, ","));
        newStudent->creditHours = atoi(hoursStr);
        
        // Add them to their respective lists
        addStudent(newStudent, &pDatabase);   
    }

    fclose(pFile);      // Close the file
}


// Check if the ID exists in the ID list
bool idExists(char **id, StudentNode **pHead, Student **memAddress) 
{
    // Check for empty list
    if (*pHead == NULL) {
        return false;
    }
    else {
        StudentNode *pCurrent = *pHead;

        // Iterate through the list until we find it or reach the end
        while (pCurrent != NULL) {
            if ( strcmp(pCurrent->pStudent->id, *id) == 0) {
                *memAddress = pCurrent->pStudent;
                return true;
            }

            pCurrent = pCurrent->pNext;
        }

        // ID wasn't found
        return false;
    }
}


// Remove one node from one list. Helper function to delete()
void _delete(char **id, StudentNode **pHead) 
{
    // Check for empty list
    if (*pHead == NULL) {
        return ;
    }
    // Check if it's the first element
    else if (strcmp((*pHead)->pStudent->id, *id) == 0) {
        StudentNode* pTemp = *pHead;

        *pHead = (*pHead)->pNext;
        free(pTemp);
    }
    else { 
        StudentNode* pCurrent = *pHead;

        // Traverse until we find the ID
        while (pCurrent->pNext != NULL && strcmp(pCurrent->pNext->pStudent->id, *id) != 0) {
            pCurrent = pCurrent->pNext;
        }

        // Free the memory
        if (pCurrent->pNext != NULL) {
            StudentNode* pTemp = pCurrent->pNext;

            pCurrent->pNext = pTemp->pNext;
            free(pTemp);
            pTemp = NULL;
        }
    }
}


// Remove a student from the database
void delete(char *ID, Database *pDatabase) {
    Student *memAddress = NULL;
    bool found = idExists(&ID, &(pDatabase->pIDList), &memAddress);    
    
    // Go through all the lists to search for the ID
    if (found) {
        // Delete the nodes
        _delete( &ID, &(pDatabase->pIDList));
        _delete( &ID, &(pDatabase->pHonorRollList)); 
        _delete( &ID, &(pDatabase->pAcademicProbationList)); 
        _delete( &ID, &(pDatabase->pFreshmanList)); 
        _delete( &ID, &(pDatabase->pSophomoreList)); 
        _delete( &ID, &(pDatabase->pJuniorList)); 
        _delete( &ID, &(pDatabase->pSeniorList));  

        // Delete the student
        free(memAddress->name);
        free(memAddress->id);
        free(memAddress);       
    }
    else {
        // The ID does not exist
        printf("Sorry, there is no student in the database with the id %s.\n", ID);        
    }
}


// Print the first 10 sudents in the ID list
void printPreview(StudentNode **pHead) {    
    // Check if the list is empty
    if (*pHead == NULL) {
        printf("There are no students matching that criteria.\n");
        return ;        // End function here
    }

    StudentNode *pCurrent = *pHead;

    // Print out their data
    int i = 0;
    while (i < 10 && pCurrent != NULL) {        
        printf("%s:\n", pCurrent->pStudent->name);
        printf("\tID - %s\n", pCurrent->pStudent->id);
        printf("\tGPA - %.2f\n", pCurrent->pStudent->gpa);
        printf("\tCredit Hours - %d\n", pCurrent->pStudent->creditHours);

        pCurrent = pCurrent->pNext;
        i++;
    }
}


// Print the specified student's info
void printStudent(char *ID, const Database *pDatabase) {
    StudentNode *pCurrent = pDatabase->pIDList;

    // Check if the list is empty
    if (pDatabase->pIDList == NULL) {
        printf("There are no students matching that criteria.\n");
        return ;    // End function here
    }

    // Go through every Student in the list
    while (pCurrent != NULL) 
    {
        // Print out their data if found
        if (strcmp(pCurrent->pStudent->id, ID) == 0) { 
            printf("%s:\n", pCurrent->pStudent->name);
            printf("\tID - %s\n", pCurrent->pStudent->id);
            printf("\tGPA - %.2f\n", pCurrent->pStudent->gpa);
            printf("\tCredit Hours - %d\n", pCurrent->pStudent->creditHours);

            return; // End function here
        }

        pCurrent = pCurrent->pNext;
    }

    // Student wasn't found
    printf("Sorry, there is no student in the database with the id %s.\n", ID);	
}


// Make a Student object and add it to the database
void makeStudent(Database *pDatabase) {
    Student *newStudent = malloc(sizeof(Student));
    newStudent->name = (char*) malloc(sizeof(char) * 81);
    newStudent->id = (char*) malloc(sizeof(char) * 81);

    double GPA;
    int hours;

    printf("Enter the name of the new student: ");
    char first[81], last[81];
    scanf("%s", first);
    scanf("%s", last);
    strcat(first, " ");
    strcat(first, last);
    strcpy(newStudent->name, first);

    printf("Enter the ID of the new student: ");
    scanf(" %s", newStudent->id);
    bool exists = idExists(&newStudent->id, &pDatabase->pIDList, NULL);
    if (exists) {
        exit(1);
    }

    printf("Enter the GPA of the new student: ");
    scanf(" %lf", &GPA);
    newStudent->gpa = GPA;

    printf("Enter the credit hours of the new student: ");
    scanf(" %d", &hours);
    newStudent->creditHours = hours;

    addStudent(newStudent, &pDatabase);    // Add them to the appropriate lists
    printf("Successfully added the following student to the database!\n");

    // Print this student's info
    printf("%s:\n", newStudent->name);
    printf("\tID - %s\n", newStudent->id);
    printf("\tGPA - %.2f\n", newStudent->gpa);
    printf("\tCredit Hours - %d\n", newStudent->creditHours);
}


// Free all the Database memory
void clear(Database *pDatabase) 
{
    // Clear the ID List
    if (pDatabase->pIDList != NULL) {
        StudentNode *pCurrent = pDatabase->pIDList;
        StudentNode *pTemp = NULL;

        while (pCurrent != NULL) {
            pTemp = pCurrent->pNext;
            free(pCurrent->pStudent->name);
            free(pCurrent->pStudent->id);
            free(pCurrent->pStudent);
            free(pCurrent);
            pCurrent = pTemp;
        }

        pDatabase->pIDList = NULL;
    }

    // Clear the Honor Roll List
    if (pDatabase->pHonorRollList != NULL) {
        StudentNode *pCurrent = pDatabase->pHonorRollList;
        StudentNode *pTemp = NULL;
    
        while (pCurrent != NULL) {
            pTemp = pCurrent->pNext;
            free(pCurrent);             // We already freed the name + ID
            pCurrent = pTemp;
        }
    
        pDatabase->pHonorRollList = NULL;
    }

    // Clear the Academic Probation List
    if (pDatabase->pAcademicProbationList != NULL) {
        StudentNode *pCurrent = pDatabase->pAcademicProbationList;
        StudentNode *pTemp = NULL;
    
        while (pCurrent != NULL) {
            pTemp = pCurrent->pNext;
            free(pCurrent);
            pCurrent = pTemp;
        }
    
        pDatabase->pAcademicProbationList = NULL;
    }

    // Clear the Freshman List
    if (pDatabase->pFreshmanList != NULL) {
        StudentNode *pCurrent = pDatabase->pFreshmanList;
        StudentNode *pTemp = NULL;
    
        while (pCurrent != NULL) {
            pTemp = pCurrent->pNext;
            free(pCurrent);
            pCurrent = pTemp;
        }
    
        pDatabase->pFreshmanList = NULL;
    }

    // Clear the Sophomore List
    if (pDatabase->pSophomoreList != NULL) {
        StudentNode *pCurrent = pDatabase->pSophomoreList;
        StudentNode *pTemp = NULL;
    
        while (pCurrent != NULL) {
            pTemp = pCurrent->pNext;
            free(pCurrent);
            pCurrent = pTemp;
        }
    
        pDatabase->pSophomoreList = NULL;
    }

    // Clear the Junior List
    if (pDatabase->pJuniorList != NULL) {
        StudentNode *pCurrent = pDatabase->pJuniorList;
        StudentNode *pTemp = NULL;
    
        while (pCurrent != NULL) {
            pTemp = pCurrent->pNext;
            free(pCurrent);
            pCurrent = pTemp;
        }
    
        pDatabase->pJuniorList = NULL;
    }

    // Clear the Senior List
    if (pDatabase->pSeniorList != NULL) {
        StudentNode *pCurrent = pDatabase->pSeniorList;
        StudentNode *pTemp = NULL;
    
        while (pCurrent != NULL) {
            pTemp = pCurrent->pNext;
            free(pCurrent);
            pCurrent = pTemp;
        }
    
        pDatabase->pSeniorList = NULL;
    }
}


int main() {
    // Make all the linked lists point to NULL
    Database studentDatabase;
    studentDatabase.pIDList = NULL;
    studentDatabase.pHonorRollList = NULL;
    studentDatabase.pAcademicProbationList = NULL;
    studentDatabase.pFreshmanList = NULL;
    studentDatabase.pSophomoreList = NULL;
    studentDatabase.pJuniorList = NULL;
    studentDatabase.pSeniorList = NULL;

	printf("CS 211, Spring 2023\n");
	printf("Program 4: Database of Students\n\n");

    // Print the file options
	printf("Enter E to start with an empty database, \n");
	printf("or F to start with a database that has information on students from a file.\n");
	printf("Your choice --> ");
    
    char fileChoiceStr[81];
    scanf(" %s", fileChoiceStr);
    char fileChoice = fileChoiceStr[0];

    while (strlen(fileChoiceStr) > 1) {
        printf("Sorry, that input was invalid. Please try again.\n");
        printf("Your choice --> ");

        scanf(" %s", fileChoiceStr);
        fileChoice = fileChoiceStr[0];
    }

    // Repeat until we have valid input
    while (fileChoice != 'F' && fileChoice != 'E') {
        printf("Sorry, that input was invalid. Please try again.\n");
        printf("Your choice --> ");
        scanf(" %c", &fileChoice);
    }

    // Evaluate user input
    switch (fileChoice) {
        case 'E':
            break;
        case 'F':
            // Read the given file and add the info to the database
            printf("Enter the name of the file you would like to use: ");
            char file[81];
            scanf(" %s", file);

            read(file, &studentDatabase); 
            break;
        default:
            break;        
    };
	
	// Print the program's commands
	printf("\nEnter: \tC to create a new student and add them to the database,\n");
	printf("\tR to read from the database,\n");
	printf("\tD to delete a student from the database, or\n");
	printf("\tX to exit the program.\n");
	printf("Your choice --> ");

    char commandStr[81];
    scanf(" %s", commandStr);
    char command = commandStr[0];

    // Handle non-char input
    while (strlen(commandStr) > 1) {
        printf("Invalid option. Try again.\n");
        
        // Print the program's commands
        printf("Enter: \tC to create a new student and add them to the database,\n");
        printf("\tR to read from the database,\n");
        printf("\tD to delete a student from the database, or\n");
        printf("\tX to exit the program.\n");
        printf("Your choice --> ");

        scanf(" %s", commandStr);
        command = commandStr[0];
    }

    // Evaluate user input. Repeat until the user wants to exit
    while (command != 'X') 
    {
        // Handle non-char input
        while (strlen(commandStr) > 1) {
            printf("Invalid option. Try again.\n");
            
            // Print the program's commands
            printf("Enter: \tC to create a new student and add them to the database,\n");
            printf("\tR to read from the database,\n");
            printf("\tD to delete a student from the database, or\n");
            printf("\tX to exit the program.\n");
            printf("Your choice --> ");

            scanf(" %s", commandStr);
            command = commandStr[0];
        }

        switch (command) {
            case 'C':
                makeStudent(&studentDatabase);
                break;
            case 'R':
                // Print options
                printf("Select one of the following: \n");
                printf("\t1) Display the head (first 10 rows) of the database\n");
                printf("\t2) Display students on the honor roll, in order of their GPA\n");
                printf("\t3) Display students on academic probation, in order of their GPA\n");
                printf("\t4) Display freshmen students, in order of their name\n");
                printf("\t5) Display sophomore students, in order of their name\n");
                printf("\t6) Display junior students, in order of their name\n");
                printf("\t7) Display senior students, in order of their name\n");
                printf("\t8) Display the information of a particular student\n");
                printf("Your choice --> ");

                int printOption;
                scanf(" %d", &printOption);

                // Ask again until we get valid input
                while (printOption < 1 || printOption > 8) {
                    printf("Sorry, that input was invalid. Please try again.\n");
                    printf("Your choice --> ");
                    scanf(" %d", &printOption);
                }
                
                switch(printOption) {
                    case 1:
                        printPreview( &(studentDatabase.pIDList));
                        break;
                    case 2:
                        printList( &(studentDatabase.pHonorRollList));
                        break;
                    case 3: 
                        printList( &(studentDatabase.pAcademicProbationList));
                        break;
                    case 4:
                        printList( &(studentDatabase.pFreshmanList));
                        break;
                    case 5:
                        printList( &(studentDatabase.pSophomoreList));
                        break;
                    case 6:
                        printList( &(studentDatabase.pJuniorList));
                        break;
                    case 7:
                        printList( &(studentDatabase.pSeniorList));
                        break;
                    case 8:
                        printf("Enter the id of the student to find: ");
                        char ID[81];
                        scanf(" %s", ID);

                        printStudent(ID, &studentDatabase);
                        break;
                    default:
                        printf("Sorry, that input was invalid. Please try again.\n");
                        break;
                };
                break;
            case 'D':
                // Delete this student from the database
                printf("Enter the ID of the student to be removed: ");
                char id[81];
                scanf(" %s", id);
                delete(id, &studentDatabase);
                break;
            case 'X':
                // Exit the program
                printf("\n");
                break;
            default: 
                printf("Invalid option. Try again.\n");
                break;
        };

        // Print the program's commands
        printf("\nEnter: \tC to create a new student and add them to the database,\n");
        printf("\tR to read from the database,\n");
        printf("\tD to delete a student from the database, or\n");
        printf("\tX to exit the program.\n");
        printf("Your choice --> ");

        scanf(" %c", &command);
    }
	        
	printf("\nThanks for playing!\n");
	printf("Exiting...\n");

    clear(&studentDatabase);    // Free all our memory
	
	return 0;
}