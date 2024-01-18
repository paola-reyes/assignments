/*
----------------------------
  Paola Reyes
  4/10/23
  UIC CS 251, Wed 4pm Lab
  Prof. Adam Koehler
----------------------------    
Project 5 - Priority Queue

This project is class implementation of a priority queue, which we organize as a 
binary search tree.

Each NODE* in the tree has the following properties:
    int priority;  // used to build BST
    T value;  // stored data for the p-queue
    bool dup;  // marked true when there are duplicate priorities
    NODE* parent;  // links back to parent
    NODE* link;  // links to linked list of NODES with duplicate priorities
    NODE* left;  // links to left child
    NODE* right;  // links to right child

The member functions for the priorityqueue class include:
    = operator
    == operator
    clear()
    size()
    enqueue()
    dequeue()
    begin()
    next()
    toString()
    peek()


Provided testing file to implement framework based tests in. The examples
below demonstrates a basic empty test in each framework with a single
assertion. The version uses the supplied catch.hpp file in starter code.

Assignment details and provided code are created and
owned by Adam T Koehler, PhD - Copyright 2023.
University of Illinois Chicago - CS 251 Spring 2023
Catch 1.0 Framework Testing
*/

#pragma once

#include <iostream>
#include <sstream>
#include <stack>    // For next()

using namespace std;

template<typename T>

class priorityqueue {
private:
    struct NODE {
        int priority;  // used to build BST
        T value;  // stored data for the p-queue
        bool dup;  // marked true when there are duplicate priorities
        NODE* parent;  // links back to parent
        NODE* link;  // links to linked list of NODES with duplicate priorities
        NODE* left;  // links to left child
        NODE* right;  // links to right child
    };

    NODE* root;  // pointer to root node of the BST
    int size;  // # of elements in the pqueue
    NODE* curr;  // pointer to next item in pqueue (see begin and next)


    // Helper function to enqueue()
    // Finds a empty spot to place the new leaf. Returns what will be the new leaf's parent
    NODE* _enqueue(NODE *current, int priority)
    {
        NODE *parent = nullptr;     // Will be the new leaf's parent

        // Will stop once we've found an empty spot
        while (current != nullptr) 
        {
            // It is a duplicate
            if (priority == current->priority) 
            {
                // Iterate to the end of the duplicates list
                while (current != nullptr) {
                    parent = current;           // Save this node
                    current = current->link;    // Move to the next node
                }
            }
            // It is left oriented
            else if (priority < current->priority) {
                parent = current;
                current = current->left;
            }
            // It is right oriented
            else {
                parent = current;
                current = current->right;
            }
        }

        return parent;
    }

    // Helper function to toString()
    // Adds the entire priority queue to a stringstream, in order.  
    // Format:
    // "1 value: Ben
    //  2 value: Jen
    //  2 value: Sven
    //  3 value: Gwen"
    void _toString(NODE *current, ostringstream &output) 
    {
        if (current == nullptr) {
            return ;
        }
        else {
            // Start with the higher priority
            _toString(current->left, output);

            // Add the current node's data to the stream
            output << current->priority << " value: " << current->value << endl;
            
            // Move to the lower priority
            _toString(current->link, output);      // Duplicates printed from oldest to most recent
            _toString(current->right, output);            
        }
    }

    // Helper function to clear().
    // Iterate through the tree and delete nodes from the bottom up
    void _clear(NODE *current)
    {
        if (current != nullptr) {
            _clear(current->left);
            _clear(current->link);
            _clear(current->right);

            // Free the memory and set to nullptr
            delete current;
            current = nullptr;
        }
    }

    // Helper function to the assignment operator =
    // Goes through the given tree and copies each node to this tree
    NODE* _copy(NODE *prev, NODE *other)
    {
        if (other == nullptr) {
            return nullptr;
        } 
        else {
            // Create a new node for the other node
            NODE *newLeaf = new NODE;  
            newLeaf->value = other->value;
            newLeaf->priority = other->priority;
            newLeaf->dup = other->dup;
            newLeaf->parent = prev;

            newLeaf->link = _copy(newLeaf, other->link);
            newLeaf->left = _copy(newLeaf, other->left);
            newLeaf->right = _copy(newLeaf, other->right);

            return newLeaf;
        }
    }

    // Helper function to begin() and dequeue()
    // Traverses all the way to the left to find the highest priority node
    NODE* _begin(NODE *current) 
    {
        if (current->left != nullptr) {
            current = _begin(current->left);
        }

        return current;
    }

    // Helper function to dequeue()
    // Connects current's child to it's parent
    void _moveChild(NODE* current) 
    {
        // Move the link
        if (current->link != nullptr) 
        {
            // Connect current's children to the link
            if (current->right != nullptr) {
                current->link->right = current->right;
            }
            else {
                current->link->right = current->left;
            }

            // Find out if we need to move to the parent's right or left
            if (current == current->parent->left) {
                current->parent->left = current->link;
            }
            else {
                current->parent->right = current->link;
            }
        }
        // Move the right child
        else if (current->right != nullptr) {
            if (current == current->parent->left) {
                current->parent->left = current->right;
            }
            else {
                current->parent->right = current->right;
            }
        }
        // Move the left child
        else {
            if (current == current->parent->left) {
                current->parent->left = current->left;
            }
            else {
                current->parent->right = current->left;
            }
        }       
    }

    // Helper function to == operator
    // Iterates through both trees in order and compares their values
    bool _equal(const NODE *current, const NODE *other) const
    {
        if (current == nullptr || other == nullptr) {
            return true;
        }
        else {
            // They are not equal
            if (current->value != other->value) {
                return false;
            }

            _equal(current->left, other->left);
            _equal(current->link, other->link);
            _equal(current->right, other->right);
        }

        return true;
    }


public:
    //
    // default constructor:
    //
    // Creates an empty priority queue.
    // O(1)
    //
    priorityqueue() {
        size = 0;
        root = nullptr;
        curr = nullptr;            
    }
    
    //
    // operator=
    //
    // Clears "this" tree and then makes a copy of the "other" tree.
    // Sets all member variables appropriately.
    // O(n), where n is total number of nodes in custom BST
    //
    priorityqueue& operator=(const priorityqueue& other) 
    {
        // Delete all the values of this tree
        _clear(root);
        size = other.size;
        root = nullptr;
  
        // Copy the other tree's values
        if (other.root != nullptr) { 
            root = _copy(root, other.root);
        }

        return *this;       
    }
    
    //
    // clear:
    //
    // Frees the memory associated with the priority queue but is public.
    // O(n), where n is total number of nodes in custom BST
    //
    void clear() {
        _clear(root); 

        // Reset default values
        size = 0;
        root = nullptr;
    }
    
    //
    // destructor:
    //
    // Frees the memory associated with the priority queue.
    // O(n), where n is total number of nodes in custom BST
    //
    ~priorityqueue() {   
        // Iterate through the tree and delete nodes
        if (root != nullptr) {
           _clear(root);
        }
    }
    
    //
    // enqueue:
    //
    // Inserts the value into the custom BST in the correct location based on
    // priority.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    void enqueue(T value, int priority) 
    { 
        // Create a new node for the given info
        NODE *newLeaf = new NODE;  
        newLeaf->value = value;
        newLeaf->priority = priority;
        newLeaf->dup = false;
        newLeaf->parent = nullptr;
        newLeaf->left = nullptr;
        newLeaf->right = nullptr;
        newLeaf->link = nullptr;

        // Check if tree is empty
        if (root == nullptr) {
            root = newLeaf;
        }
        else {
            // Iterate through the tree to find a spot
            NODE *parent = _enqueue(root, priority);           

            // Add it to the left or right of the previous node
            if (priority == parent->priority) {
                parent->dup = true;
                parent->link = newLeaf;
                newLeaf->dup = true;
            }
            else if (priority < parent->priority) {
                parent->left = newLeaf;
            }
            else {
                parent->right = newLeaf;
            }

            newLeaf->parent = parent;   // Assign the newLeaf's parent
        }
        
        size++;     // Update tree size
    }

    //
    // dequeue:
    //
    // returns the value of the next element in the priority queue and removes
    // the element from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    
    T dequeue() 
    {
        // Will not work on an empty queue
        if (size == 0) {
            return T();
        } 

        // Find the highest priority node
        NODE *current = _begin(root);
        T val = current->value;        

        // This node is the root
        if (current == root) {
            if (current->link != nullptr) 
            {
                // Connect current's children to this link
                if (current->right != nullptr) {
                    current->link->right = current->right;
                }
                else {
                    current->link->right = current->left;
                }

                root = current->link;
            }        
            else {
                // Move the right or left child into the vacancy
                if (current->right != nullptr) {
                    root = current->right;
                }
                else {
                    root = current->left;
                }
            }
        } 
        // Curr is a duplicate
        else if (current->dup) {
            // Curr is within a duplicate chain
            if (current->priority == current->parent->priority) {
                current->parent->link = current->link;
            }
            // Curr is the first item of a duplicate chain
            else {
                _moveChild(current);
            }
        }
        // Connect current's child to its parent
        else {
            _moveChild(current);
        }

        delete current;
        current = nullptr;
        
        size--;
        return val;
    }
    
    //
    // Size:
    //
    // Returns the # of elements in the priority queue, 0 if empty.
    // O(1)
    //
    int Size() {
        return size; 
    }
    
    //
    // begin
    //
    // Resets internal state for an inorder traversal.  After the
    // call to begin(), the internal state denotes the first inorder
    // node; this ensure that first call to next() function returns
    // the first inorder node value.
    //
    // O(logn), where n is number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (tree.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    void begin() 
    {
        // Check if tree is empty
        if (root == nullptr) {
            curr = nullptr;
        }
        else {  
            NODE* head = new NODE;   // Dummy node to prepare for furst next() call

            // Traverse all the way to the left to get the first priority node
            head->parent = _begin(root);
            head->priority = -1;
            head->dup = false;

            curr = head;
        }
    }
    
    //
    // next
    //
    // Uses the internal state to return the next inorder priority, and
    // then advances the internal state in anticipation of future
    // calls.  If a value/priority are in fact returned (via the reference
    // parameter), true is also returned.
    //
    // False is returned when the internal state has reached null,
    // meaning no more values/priorities are available.  This is the end of the
    // inorder traversal.
    //
    // O(logn), where n is the number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (pq.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    //
    bool next(T& value, int &priority) 
    {   
        // Check if it's the initial dummy node
        if (curr->priority == -1) {
            NODE* temp = curr->parent;
            delete curr;

            // Update curr
            curr = temp;
            value = curr->value;
            priority = curr->priority;

            return true;
        }

        // Finds the next node in the queue. Returns bool and updates values and priority
        // Traverse until you reach the root 
        while (curr != nullptr)
        {
            // Check if curr has duplicates
            if (curr->dup && curr->link != nullptr) 
            {
                // Update curr
                curr = curr->link;
                value = curr->value;
                priority = curr->priority;

                return true;
            }
            // Check if curr a right child. We covered all left children in begin()
            else if (curr->right != nullptr) 
            {
                // Update curr
                curr = curr->right;
                value = curr->value;
                priority = curr->priority;

                return true;
            }
            // Check if curr's right sibling is empty
            else if (curr->parent->right != nullptr) 
            {
                // Update curr
                curr = curr->parent->right;
                value = curr->value;
                priority = curr->priority;

                return true;
            }   
            else // Look for curr's most recent left-oriented ancestor
            {  
                // If it's a duplicate, move out of the duplicate list
                while (curr->parent->priority == curr->priority) {
                    curr = curr->parent;
                }

                // Move up to it's parent
                curr = curr->parent;                

                // Check if this node is left-oriented or we've reached the root
                if (curr->parent == nullptr || curr == curr->parent->left) 
                {
                    // Update curr
                    value = curr->value;
                    priority = curr->priority;

                    return true;
                }
            }
        } // end of while-loop

        // We reached the end of the queue
        return false;
    }
    
    // 
    // toString:
    //
    // Returns a string of the entire priority queue, in order.  
    // Format:
    // "1 value: Ben
    //  2 value: Jen
    //  2 value: Sven
    //  3 value: Gwen"
    //
    string toString() {
        ostringstream output;

        _toString(root, output);
        string values = output.str();

        return values;     
    }
    
    //
    // peek:
    //
    // returns the value of the next element in the priority queue but does not
    // remove the item from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    T peek() {
        // If queue is empty
        if (root == nullptr) {
            return T();
        }
        // Find the first priority node
        NODE* current = _begin(root);
        T val = current->value;

        return val; // TO DO: update this return        
    }
    
    //
    // ==operator
    //
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST
    //
    bool operator==(const priorityqueue& other) const { 
        if (size != other.size) {
            return false;
        }

        return _equal(root, other.root);
    }
    
    //
    // getRoot - Do not edit/change!
    //
    // Used for testing the BST.
    // return the root node for testing.
    //
    void* getRoot() {
        return root;
    }
};
