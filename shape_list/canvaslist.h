/*
----------------------------
  Paola Reyes
  3/27/23
  UIC CS 251, Wed 4pm Lab
  Prof. Adam Koehler
----------------------------    
Project 4 - Shape List

Shape List is a program that mimics the storage component of a drawing program. 
There are two main classes: Shape and CanvasList. CanvasList is a linked list of various 
Shapes that we create. 

The Shape properties are:
Shape (base class): x & y position
Circle (derived class): x, y, and radius values
Rectangle (derived class): x, y, width, and height values
RightTriangle (derived class): x, y, base, and height values

The Shape class allows you to set the x, y, etc. values to currate where you want the
Shape to be and with what size dimensions. They are then "placed" onto the canvas.
*/

#pragma once
#include "shape.h"
#include <iostream>
using namespace std;


class ShapeNode
{
    public:
        Shape *value;
        ShapeNode *next;
};


class CanvasList
{
    private:    
        int listSize;
        ShapeNode *listFront;

    public:
        CanvasList();
        CanvasList(const CanvasList &);
        CanvasList operator=(const CanvasList &);
        
        virtual ~CanvasList();
        void clear();
        
        void insertAfter(int, Shape *);
        void push_front(Shape *);
        void push_back(Shape *);
        
        void removeAt(int);
        Shape* pop_front();
        Shape* pop_back();

        ShapeNode* front() const;
        bool isempty() const;
        int size() const;

        int find(int x, int y) const;
        Shape* shapeAt(int) const;
        
        void draw() const;
        void printAddresses() const;
};


// Default constructor. Set data members to 0 and the head Node to NULL
CanvasList::CanvasList() 
{
    listSize = 0;
    listFront = NULL;
}


// Copy constructor. Copy the given linked list data into the implicit CanvasList
CanvasList::CanvasList(const CanvasList &other) 
{
    // Default data member values
    listSize = 0;   
    listFront = NULL;

    // If other list is empty, set listFront to default value
    if (other.front() == NULL) {
        listFront = NULL;
    }
    else {        
        ShapeNode *pOther = other.front();  // Pointer to traverse through other linked list

        ShapeNode *newNode = new ShapeNode;
        newNode->value = pOther->value->copy();

        listFront = newNode;
        ShapeNode *pPrevious = listFront;   // Pointer to traverse through link list

        pOther = pOther->next;
        listSize++;
        
        while (pOther != NULL) {
            // Make a new node and copy over values
            ShapeNode *newNode = new ShapeNode;    
            newNode->value = pOther->value->copy();

            pPrevious->next = newNode;  // Connect the last and the current nodes          
            pPrevious = newNode;        // Move to the next node
            pOther = pOther->next;      // Move on to next node in other list
            listSize++;                 // Update list size
        }

        pPrevious->next = NULL;  // For the last node
    }
}


// Copy using = operator
CanvasList CanvasList::operator=(const CanvasList &other) {
    ShapeNode *pTemp = NULL;    // Pointer to prevent memory leak

    // Delete existing data
    if (listSize > 0) {
        pTemp = NULL;    // Pointer to prevent memory leak
    }

    // Traverse through the linked list
    while (listFront != NULL) {
        pTemp = listFront;            // Save front node location
        listFront = listFront->next;  // Move on to next node
        delete pTemp->value;          // Delete ShapeNode
        delete pTemp;                 // Delete front node
    }

    listSize = 0;   // Reset listSize

    // Copy over data
    // If other list is empty, set listFront to default value
    if (other.front() == NULL) {
        listFront = NULL;
    }
    else {        
        ShapeNode *pOther = other.front();  // Pointer to traverse through other linked list

        ShapeNode *newNode = new ShapeNode;
        newNode->value = pOther->value->copy();

        listFront = newNode;
        ShapeNode *pPrevious = listFront;   // Pointer to traverse through link list

        pOther = pOther->next;
        listSize++;
        
        while (pOther != NULL) {
            // Make a new node and copy over values
            ShapeNode *newNode = new ShapeNode;    
            newNode->value = pOther->value->copy();

            pPrevious->next = newNode;  // Connect the last and the current nodes          
            pPrevious = newNode;        // Move to the next node
            pOther = pOther->next;      // Move on to next node in other list
            listSize++;                 // Update list size
        }

        pPrevious->next = NULL;  // For the last node
    }

    return *this;   // Return implicit CanvasList
}


// Destructor. Free linked list memory
CanvasList::~CanvasList() {
    ShapeNode *pTemp = NULL;    // Pointer to prevent memory leak

    // Traverse through the linked list
    while (listFront != NULL) {
        pTemp = listFront;            // Save front node location
        listFront = listFront->next;  // Move on to next node
        delete pTemp->value;          // Delete ShapeNode
        delete pTemp;                 // Delete front node
    }
}


// Free linked list memory
void CanvasList::clear() {
    ShapeNode *pTemp = NULL;    // Pointer to prevent memory leak

    // Traverse through the linked list
    while (listFront != NULL) {
        pTemp = listFront;            // Save front node location
        listFront = listFront->next;  // Move on to next node
        delete pTemp->value;          // Delete ShapeNode
        delete pTemp;                 // Delete front node
    }

    listSize = 0;      // Update list size
}


// Insert the given Shape after the given index
void CanvasList::insertAfter(int n, Shape *s) {
    // Do nothing if n is out of bounds
    if (n < 0 || n > listSize) {
        return ;    
    }
    else {
        ShapeNode *newNode = new ShapeNode;     // Make a new node with the given Shape
        newNode->value = s;             // Store a copy of s to newNode's Shape 
        ShapeNode *pCurrent = listFront;        // Pointer to traverse through listFront

        // Traverse through list until we reach the node at index n
        for (int i = 0; i < n; i++) {
            pCurrent = pCurrent->next;
        }

        ShapeNode *pTemp = pCurrent->next;      // Save the next node's address
        pCurrent->next = newNode;               // Insert newNode in it's new spot
        newNode->next = pTemp;                  // Make newNode points to the old next node
   
        listSize++;     // Update listSize
    }
}


// Add a Shape to the front of the linked list
void CanvasList::push_front(Shape *s) {
    ShapeNode *newNode = new ShapeNode; // Make a new node with the given Shape
    newNode->value = s;         // Store a copy of s to newNode's Shape 
    newNode->next = listFront;          // Save the current listFront's location
    listFront = newNode;                // listFront points to the newNode

    listSize++;
}


// Add a Shape to the end of the linked list
void CanvasList::push_back(Shape *s) 
{
    ShapeNode *newNode = new ShapeNode; // Make a new node with the given Shape
    newNode->value = s;         // Store a copy of s to newNode's Shape 
    newNode->next = NULL;               // Last node. Points to nothing
    
    // If list is empty, listFront points to newNode
    if (listFront == NULL) {
        listFront = newNode;
    }
    else {
        ShapeNode *pCurrent = listFront;    // Pointer to traverse through listFront
        
        // Traverse to the last node of the list
        while (pCurrent && pCurrent->next != NULL) {
            pCurrent = pCurrent->next;      // Move to the next node
        }

        pCurrent->next = newNode;   // Make the last node point to newNode
    }
    
    listSize++;     // Update list size
}


// Delete the ShapeNode at index n
void CanvasList::removeAt(int n) {
    // Do nothing if the index is out of range or if list is empty
    if (n < 0 || n > listSize || listFront == NULL) {
        return ;
    }
    
    ShapeNode *pCurrent = listFront;    // Pointer to traverse through listFront

    if (n == 0) {
        listFront = listFront->next;    // Bring the next node to the front
        delete pCurrent;
    }
    else {
        // Stop at the node before index n
        for (int i = 0; i < n - 1; i++) {
            pCurrent = pCurrent->next;      // Move to next node
        }

        ShapeNode *pTemp = pCurrent->next;    // Save the node to delete
        pCurrent->next = pTemp->next;         // Save the node after the wanted node         
        delete pTemp->value;    // Free ShapeNode
        delete pTemp;           // Delete the wanted node
    }

    listSize--;     // Update listSize
}


// Remove the node at the front of the list and return that Shape
Shape* CanvasList::pop_front() {
    // Return NULL if list is empty
    if (listSize == 0) {
        return NULL;
    }

    Shape *s = listFront->value;    // Save the front node's Shape

    ShapeNode *pTemp = listFront;   // Pointer to save the listFront node
    listFront = listFront->next;    // Move to the next node 
    delete pTemp;                   // Delete the current front node

    listSize--;     // Update listSize
    return s;
}


// Remove the ShapeNode at the end of the linked list and return that Shape
Shape* CanvasList::pop_back() {
    // Return NULL if list is empty
    if (listSize == 0) {
        return NULL;
    }

    ShapeNode* pCurrent = listFront;    // Pointer to traverse through linked list
    ShapeNode* pPrevious = NULL;        // To set the new last node to NULL

    // Traverse to the list. Stop at the node before the last node
    while (pCurrent->next != NULL) {
        pPrevious = pCurrent;
        pCurrent = pCurrent->next;
    }
    
    Shape* s = pCurrent->value;     // Save a copy of the last Shape

    if (pPrevious == NULL) {
        listFront = NULL;
    }
    else {  
        // Make the penultimate node the last one
        pPrevious->next = NULL;     
    }

    delete pCurrent->next;

    listSize--;
    return s;
}


// Returns the pointer to the front of the linked list
ShapeNode* CanvasList::front() const {
    return listFront;
}

// Check if a list is empty
bool CanvasList::isempty() const {
    return listSize == 0 && listFront == NULL;
}


// Returns the size of the linked list
int CanvasList::size() const {
    return listSize;
}


// Return a Shape's index of the linked list based on the given x and y values
int CanvasList::find(int x, int y) const {
    int index = 0;
    ShapeNode *pCurrent = listFront;    // Pointer to traverse through listFront

    while (pCurrent != NULL) {
        // Call the Shape functions getX() and getY() for the node's value
        if (pCurrent->value->getX() == x && pCurrent->value->getY() == y) {
            return index;   // Found Shape
        }

        index++;    // Next index
    }

    return -1;  // If not found, return -1
}


// Return the Shape at index n
Shape* CanvasList::shapeAt(int n) const {
    // Return NULL if n is out of bounds
    if (n < 0 || n > listSize) {
        return NULL;
    }

    ShapeNode *pCurrent = listFront;

    for (int i = 0; i < n; i++) {
        pCurrent = pCurrent->next;  // Move to the next node
    }

    return pCurrent->value;   // Return the Shape value
}


// Print out the linked list Shapes details
void CanvasList::draw() const {
    ShapeNode *pCurrent = listFront;    // Pointer to traverse through listFront

    while (pCurrent != NULL) {
        pCurrent->value->printShape();  // Call printShape()
        pCurrent = pCurrent->next;      // Move to the next node
    }
}


// Print out the addresses of each node and Shape
void CanvasList::printAddresses() const {
    ShapeNode *pCurrent = listFront;    // Pointer to traverse through listFront

    while (pCurrent != NULL) {
        cout << "Node Address: " << pCurrent << "	Shape Address: " << pCurrent->value << endl;
        pCurrent = pCurrent->next;  // Move to next node
    }
}