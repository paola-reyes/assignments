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
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "priorityqueue.h"
#include <string>   // For string comparison
using namespace std;

TEST_CASE("Default constructor") 
{
    priorityqueue<string> q;

    REQUIRE(q.Size() == 0);
    REQUIRE(q.getRoot() == nullptr);

    
}

//----------------------------------------------------------------------------------------------
TEST_CASE("Enqueue to an empty queue") {
    priorityqueue<string> q;
    q.enqueue("Paola", 1);

    string expected = "1 value: Paola\n";

    REQUIRE(q.Size() == 1);
    REQUIRE(expected.compare(q.toString()) == 0);   // == 0 means they're equal / have 0 difference

    
}

TEST_CASE("Enqueue - consecutive numbers right branch") {
    priorityqueue<string> q;
    q.enqueue("Paola", 1);
    q.enqueue("Thiago", 2);       // My pets' names <3
    q.enqueue("Peluchina", 3);
    q.enqueue("Betty", 4);

    string expected = "1 value: Paola\n2 value: Thiago\n3 value: Peluchina\n4 value: Betty\n";

    REQUIRE(q.Size() == 4);
    REQUIRE(expected.compare(q.toString()) == 0);   

    
}

TEST_CASE("Enqueue - consecutive numbers left branch") {
    priorityqueue<string> q;
    q.enqueue("Paola", 4);
    q.enqueue("Thiago", 3);              //   ..^____/
    q.enqueue("Peluchina", 2);           //  `-. ___ )
    q.enqueue("Betty", 1);               //     ||  || 

    string expected = "1 value: Betty\n2 value: Peluchina\n3 value: Thiago\n4 value: Paola\n";

    REQUIRE(q.Size() == 4);
    REQUIRE(expected.compare(q.toString()) == 0);

    
}

TEST_CASE("Enqueue - non-consecutive numbers") {
    priorityqueue<string> q;
    q.enqueue("Paola", 3);              //                               .-.
    q.enqueue("Thiago", 8);             //  (___________________________() *`-,                    
    q.enqueue("Peluchina", 2);          //  (   ______________________   /''"`
    q.enqueue("Betty", 13);             //  /\\                      //\\*
                                        // "" ""                     "" ""
    string expected = "2 value: Peluchina\n3 value: Paola\n8 value: Thiago\n13 value: Betty\n";    

    REQUIRE(q.Size() == 4);
    REQUIRE(expected.compare(q.toString()) == 0);

    
}

TEST_CASE("Enqueue - multiple duplicates for one node") {
    priorityqueue<string> q;
    q.enqueue("Paola", 1);
    q.enqueue("Thiago", 1);
    q.enqueue("Peluchina", 1);
    q.enqueue("Betty", 1);
    q.enqueue("Coco", 1);
    q.enqueue("Michi", 1);

    string expected = "1 value: Paola\n1 value: Thiago\n1 value: Peluchina\n1 value: Betty\n1 value: Coco\n1 value: Michi\n";    
    
    REQUIRE(q.Size() == 6);
    REQUIRE(expected.compare(q.toString()) == 0);

    
}

TEST_CASE("Enqueue - duplicates") {
    priorityqueue<string> q;
    q.enqueue("Paola", 1);
    q.enqueue("Thiago", 2);
    q.enqueue("Peluchina", 3);
    q.enqueue("Betty", 1);
    q.enqueue("Coco", 2);
    q.enqueue("Michi", 3);

    string expected = "1 value: Paola\n1 value: Betty\n2 value: Thiago\n2 value: Coco\n3 value: Peluchina\n3 value: Michi\n";    

    REQUIRE(q.Size() == 6);
    REQUIRE(expected.compare(q.toString()) == 0);

    
}

TEST_CASE("Enqueue - different types")
{
    priorityqueue<int> i;
    i.enqueue(8, 3);
    i.enqueue(6, 2);
    i.enqueue(4, 5);
    i.enqueue(2, 2);
    string iExpected = "2 value: 6\n2 value: 2\n3 value: 8\n5 value: 4\n";
    REQUIRE(iExpected.compare(i.toString()) == 0);

    priorityqueue<char> c;
    c.enqueue('d', 3);
    c.enqueue('o', 2);
    c.enqueue('g', 5);
    c.enqueue('s', 2);
    string cExpected = "2 value: o\n2 value: s\n3 value: d\n5 value: g\n";  
    REQUIRE(cExpected.compare(c.toString()) == 0);

    priorityqueue<double> d;
    d.enqueue(8.123, 3);
    d.enqueue(6.223, 2);
    d.enqueue(4.323, 5);
    d.enqueue(2.423, 2);
    string dExpected = "2 value: 6.223\n2 value: 2.423\n3 value: 8.123\n5 value: 4.323\n";  
    REQUIRE(dExpected.compare(d.toString()) == 0);

    priorityqueue<float> f;
    f.enqueue(8.1, 3);
    f.enqueue(6.2, 2);
    f.enqueue(4.3, 5);
    f.enqueue(2.4, 2);
    string fExpected = "2 value: 6.2\n2 value: 2.4\n3 value: 8.1\n5 value: 4.3\n";  
    REQUIRE(fExpected.compare(f.toString()) == 0);

    priorityqueue<bool> b;
    b.enqueue(true, 3);
    b.enqueue(false, 2);
    b.enqueue(true, 5);
    b.enqueue(false, 2);
    string bExpected = "2 value: 0\n2 value: 0\n3 value: 1\n5 value: 1\n";   
    REQUIRE(bExpected.compare(b.toString()) == 0);

    i.clear();
    c.clear();
    d.clear();
    f.clear();
    b.clear();
}


//----------------------------------------------------------------------------------------------
TEST_CASE("Clear on default constructor") 
{
    priorityqueue<string> q;
    q.clear();

    REQUIRE(q.Size() == 0);
    REQUIRE(q.getRoot() == nullptr);

    
}

TEST_CASE("Clear - one node")
{
    priorityqueue<string> q;
    q.enqueue("Paola", 1);
    q.clear();

    REQUIRE(q.Size() == 0);
    REQUIRE(q.getRoot() == nullptr);
    
    
}

TEST_CASE("Clear - consecutive numbers right branch") {
    priorityqueue<string> q;
    q.enqueue("Paola", 1);
    q.enqueue("Thiago", 2);
    q.enqueue("Peluchina", 3);
    q.enqueue("Betty", 4);
    q.clear();

    REQUIRE(q.Size() == 0);
    REQUIRE(q.getRoot() == nullptr);

    
}

TEST_CASE("Clear - consecutive numbers left branch") {
    priorityqueue<string> q;
    q.enqueue("Betty", 4);
    q.enqueue("Paola", 3);
    q.enqueue("Thiago", 2);
    q.enqueue("Peluchina", 1);
    q.clear();

    REQUIRE(q.Size() == 0);
    REQUIRE(q.getRoot() == nullptr);
}

TEST_CASE("Clear - non-consecutive numbers") {
    priorityqueue<string> q;
    q.enqueue("Paola", 3);
    q.enqueue("Thiago", 8);
    q.enqueue("Peluchina", 2);
    q.enqueue("Betty", 13);
    q.clear();

    REQUIRE(q.Size() == 0);
    REQUIRE(q.getRoot() == nullptr);
}

TEST_CASE("Clear - multiple duplicates for one node") {
    priorityqueue<string> q;
    q.enqueue("Paola", 1);
    q.enqueue("Thiago", 1);
    q.enqueue("Peluchina", 1);
    q.enqueue("Betty", 1);
    q.enqueue("Coco", 1);
    q.enqueue("Michi", 1);
    q.clear();

    REQUIRE(q.Size() == 0);
    REQUIRE(q.getRoot() == nullptr);
}

TEST_CASE("Clear - duplicates") {
    priorityqueue<string> q;
    q.enqueue("Paola", 1);
    q.enqueue("Thiago", 2);
    q.enqueue("Peluchina", 3);
    q.enqueue("Betty", 1);
    q.enqueue("Coco", 2);
    q.enqueue("Michi", 3);
    q.clear();

    REQUIRE(q.Size() == 0);
    REQUIRE(q.getRoot() == nullptr);
}


//--------------------------------------------------------------------------------------
TEST_CASE("Copy - default constructor") {
    priorityqueue<string> q1;
    priorityqueue<string> q2 = q1;

    REQUIRE(q2.Size() == 0);
    REQUIRE(q2.getRoot() == nullptr);

    
}

TEST_CASE("Copy - consecutive numbers right branch")
{
    priorityqueue<string> q1;
    q1.enqueue("Paola", 1);
    q1.enqueue("Thiago", 2);
    q1.enqueue("Peluchina", 3);
    q1.enqueue("Betty", 4);
    string expected = "1 value: Paola\n2 value: Thiago\n3 value: Peluchina\n4 value: Betty\n";

    // Pre-existing tree
    priorityqueue<string> q2;
    q2.enqueue("Coco", 1);
    q2.enqueue("Michi", 2);
    q2 = q1;
    REQUIRE(q2.Size() == 4);
    REQUIRE(expected.compare(q2.toString()) == 0);
    
    // Empty tree
    priorityqueue<string> q3;
    q3 = q1;
    REQUIRE(q3.Size() == 4);
    // REQUIRE(expected.compare(q3.toString()) == 0);

    
    
    
}

TEST_CASE("Copy - consecutive numbers left branch")
{
    priorityqueue<string> q1;
    q1.enqueue("Paola", 4);
    q1.enqueue("Thiago", 3);
    q1.enqueue("Peluchina", 2);
    q1.enqueue("Betty", 1);
    string expected = "1 value: Betty\n2 value: Peluchina\n3 value: Thiago\n4 value: Paola\n";

    // Pre-existing tree
    priorityqueue<string> q2;
    q2.enqueue("Coco", 1);
    q2.enqueue("Michi", 2);
    q2 = q1;
    REQUIRE(q2.Size() == 4);
    REQUIRE(expected.compare(q2.toString()) == 0);
    
    // Empty tree
    priorityqueue<string> q3;
    q3 = q1;
    REQUIRE(q3.Size() == 4);
    REQUIRE(expected.compare(q3.toString()) == 0);

    
    
    
}

TEST_CASE("Copy - non-consecutive numbers")
{
    priorityqueue<string> q1;
    q1.enqueue("Paola", 3);
    q1.enqueue("Thiago", 8);
    q1.enqueue("Peluchina", 2);
    q1.enqueue("Betty", 13);
    string expected = "2 value: Peluchina\n3 value: Paola\n8 value: Thiago\n13 value: Betty\n";

    // Pre-existing tree
    priorityqueue<string> q2;
    q2.enqueue("Coco", 1);
    q2.enqueue("Michi", 2);
    q2 = q1;
    REQUIRE(q2.Size() == 4);
    REQUIRE(expected.compare(q2.toString()) == 0);
    
    // Empty tree
    priorityqueue<string> q3;
    q3 = q1;
    REQUIRE(q3.Size() == 4);
    REQUIRE(expected.compare(q3.toString()) == 0);

    
    
    
}

TEST_CASE("Copy - multiple duplicates on one node")
{
    priorityqueue<string> q1;
    q1.enqueue("Paola", 1);
    q1.enqueue("Thiago", 1);
    q1.enqueue("Peluchina", 1);
    q1.enqueue("Betty", 1);
    string expected = "1 value: Paola\n1 value: Thiago\n1 value: Peluchina\n1 value: Betty\n";

    // Pre-existing tree
    priorityqueue<string> q2;
    q2.enqueue("Coco", 1);
    q2.enqueue("Michi", 2);
    q2 = q1;
    REQUIRE(q2.Size() == 4);
    REQUIRE(expected.compare(q2.toString()) == 0);
    
    // Empty tree
    priorityqueue<string> q3;
    q3 = q1;
    REQUIRE(q3.Size() == 4);
    REQUIRE(expected.compare(q3.toString()) == 0);

    
    
    
}

TEST_CASE("Copy - duplicates")
{
    priorityqueue<string> q1;
    q1.enqueue("Paola", 1);
    q1.enqueue("Thiago", 2);
    q1.enqueue("Peluchina", 3);
    q1.enqueue("Betty", 1);
    q1.enqueue("Coco", 2);
    q1.enqueue("Michi", 3);
    string expected = "1 value: Paola\n1 value: Betty\n2 value: Thiago\n2 value: Coco\n3 value: Peluchina\n3 value: Michi\n"; 

    // Pre-existing tree
    priorityqueue<string> q2;
    q2.enqueue("Coco", 1);
    q2.enqueue("Michi", 2);
    q2 = q1;

    REQUIRE(q2.Size() == 6);
    REQUIRE(expected.compare(q2.toString()) == 0);
    
    // Empty tree
    priorityqueue<string> q3;
    q3 = q1;
    REQUIRE(q3.Size() == 6);
    REQUIRE(expected.compare(q3.toString()) == 0);

    
    
    
}

TEST_CASE("Copy - different types")
{    
    priorityqueue<int> i;
    i.enqueue(8, 3);
    i.enqueue(6, 2);
    i.enqueue(4, 5);
    i.enqueue(2, 2);
    string iExpected = "2 value: 6\n2 value: 2\n3 value: 8\n5 value: 4\n";

        // Pre-existing queue
        priorityqueue<int> qI;
        qI.enqueue(1, 1);
        qI.enqueue(2, 2);
        qI = i; 
        REQUIRE(iExpected.compare(qI.toString()) == 0);

    priorityqueue<char> c;
    c.enqueue('d', 3);
    c.enqueue('o', 2);
    c.enqueue('g', 5);
    c.enqueue('s', 2);
    string cExpected = "2 value: o\n2 value: s\n3 value: d\n5 value: g\n"; 
    
        // Pre-existing queue
        priorityqueue<char> qC;
        qC.enqueue('h', 1);
        qC.enqueue('i', 2);
        qC = c; 
        REQUIRE(cExpected.compare(c.toString()) == 0);

    priorityqueue<double> d;
    d.enqueue(8.123, 3);
    d.enqueue(6.223, 2);
    d.enqueue(4.323, 5);
    d.enqueue(2.423, 2);
    string dExpected = "2 value: 6.223\n2 value: 2.423\n3 value: 8.123\n5 value: 4.323\n";  

        // Pre-existing queue
        priorityqueue<double> qD;
        qD.enqueue(0.1, 1);
        qD.enqueue(0.2, 2);
        qD = d; 
        REQUIRE(dExpected.compare(qD.toString()) == 0);

    priorityqueue<float> f;
    f.enqueue(8.1, 3);
    f.enqueue(6.2, 2);
    f.enqueue(4.3, 5);
    f.enqueue(2.4, 2);
    string fExpected = "2 value: 6.2\n2 value: 2.4\n3 value: 8.1\n5 value: 4.3\n";  

        // Pre-existing queue
        priorityqueue<float> qF;
        qF.enqueue('h', 1);
        qF.enqueue('i', 2);
        qF = f; 
        REQUIRE(fExpected.compare(qF.toString()) == 0);

    priorityqueue<bool> b;
    b.enqueue(true, 3);
    b.enqueue(false, 2);
    b.enqueue(true, 5);
    b.enqueue(false, 2);
    string bExpected = "2 value: 0\n2 value: 0\n3 value: 1\n5 value: 1\n";   
    REQUIRE(bExpected.compare(b.toString()) == 0);

        // Pre-existing queue
        priorityqueue<bool> qB;
        qB.enqueue('h', 1);
        qB.enqueue('i', 2);
        qB = b; 
        REQUIRE(bExpected.compare(qB.toString()) == 0);
}


//---------------------------------------------------------------------------------------------
// TEST_CASE("Begin - multiple duplicates") {
//     priorityqueue<string> q;
//     q.enqueue("Paola", 4);
//     q.enqueue("Thiago", 3);
//     q.enqueue("Peluchina", 2);
//     q.enqueue("Betty", 3);
//     q.enqueue("Coco", 1);
//     q.enqueue("Michi", 2);
//     q.enqueue("Boomer", 1);

//     string value = "\0";
//     int priority = 0;

//     q.begin();  // Should print: "1 value: Coco"
//     
// }

//---------------------------------------------------------------------------------------------
TEST_CASE("Next - consecutive numbers right branch")
{
    priorityqueue<string> q;
    q.enqueue("Paola", 1);
    q.enqueue("Thiago", 2);
    q.enqueue("Peluchina", 3);
    q.enqueue("Betty", 4);

    q.begin();
    string value = "\0";
    int priority = 0;

    q.next(value, priority);
    REQUIRE(value.compare("Paola") == 0);
    REQUIRE(priority == 1);

    q.next(value, priority);
    REQUIRE(value.compare("Thiago") == 0);
    REQUIRE(priority == 2);

    q.next(value, priority);
    REQUIRE(value.compare("Peluchina") == 0);
    REQUIRE(priority == 3);

    q.next(value, priority);
    REQUIRE(value.compare("Betty") == 0);
    REQUIRE(priority == 4);
} 

TEST_CASE("Next - consecutive numbers left branch")
{
    priorityqueue<string> q;
    q.enqueue("Paola", 4);
    q.enqueue("Thiago", 3);
    q.enqueue("Peluchina", 2);
    q.enqueue("Betty", 1);

    q.begin();
    string value = "\0";
    int priority = 0;

    q.next(value, priority);
    REQUIRE(value.compare("Betty") == 0);
    REQUIRE(priority == 1);
    
    q.next(value, priority);
    REQUIRE(value.compare("Peluchina") == 0);
    REQUIRE(priority == 2);

    q.next(value, priority);
    REQUIRE(value.compare("Thiago") == 0);
    REQUIRE(priority == 3);

    q.next(value, priority);
    REQUIRE(value.compare("Paola") == 0);
    REQUIRE(priority == 4);
} 

TEST_CASE("Next - multiple duplicates for one node") {
    priorityqueue<string> q;
    q.enqueue("Paola", 1);
    q.enqueue("Thiago", 1);
    q.enqueue("Peluchina", 1);
    q.enqueue("Betty", 1);

    string value = "\0";
    int priority = 0;

    q.begin(); 

    q.next(value, priority);
    REQUIRE(value.compare("Paola") == 0);
    REQUIRE(priority == 1);

    q.next(value, priority);
    REQUIRE(value.compare("Thiago") == 0);
    REQUIRE(priority == 1);

    q.next(value, priority);
    REQUIRE(value.compare("Peluchina") == 0);
    REQUIRE(priority == 1);

    q.next(value, priority);
    REQUIRE(value.compare("Betty") == 0);
    REQUIRE(priority == 1);
}

TEST_CASE("Next - duplicates") {
    priorityqueue<string> q;
    q.enqueue("Paola", 4);
    q.enqueue("Thiago", 3);
    q.enqueue("Peluchina", 2);
    q.enqueue("Betty", 3);
    q.enqueue("Coco", 1);
    q.enqueue("Michi", 2);
    q.enqueue("Boomer", 1);

    string value = "\0";
    int priority = 0;

    q.begin(); 

    q.next(value, priority);
    REQUIRE(priority == 1);
    REQUIRE(value.compare("Coco") == 0);

    q.next(value, priority);
    REQUIRE(priority == 1);
    REQUIRE(value.compare("Boomer") == 0);

    q.next(value, priority);
    REQUIRE(priority == 2);
    REQUIRE(value.compare("Peluchina") == 0);

    q.next(value, priority);
    REQUIRE(priority == 2);
    REQUIRE(value.compare("Michi") == 0);

    q.next(value, priority);
    REQUIRE(priority == 3);
    REQUIRE(value.compare("Thiago") == 0);

    q.next(value, priority);
    REQUIRE(priority == 3);
    REQUIRE(value.compare("Betty") == 0);

    q.next(value, priority);
    REQUIRE(priority == 4);
    REQUIRE(value.compare("Paola") == 0);
}

//--------------------------------------------------------------------------------------------
TEST_CASE("Dequeue - consecutive numbers right branch") {
    priorityqueue<string> q;
    q.enqueue("Paola", 1);
    q.enqueue("Thiago", 2);
    q.enqueue("Peluchina", 3);
    q.enqueue("Betty", 4);

    string value = q.dequeue();    // Remove Paola and return "Paola"
    string expected = "2 value: Thiago\n3 value: Peluchina\n4 value: Betty\n";

    REQUIRE(value.compare("Paola") == 0);
    REQUIRE(expected.compare(q.toString()) == 0);
    REQUIRE(q.Size() == 3);
}

TEST_CASE("Dequeue - consecutive numbers left branch") {
    priorityqueue<string> q;
    q.enqueue("Paola", 4);
    q.enqueue("Thiago", 3);
    q.enqueue("Peluchina", 2);
    q.enqueue("Betty", 1);

    string value = q.dequeue();    // Remove Betty
    string expected = "2 value: Peluchina\n3 value: Thiago\n4 value: Paola\n";

    REQUIRE(value.compare("Betty") == 0);
    REQUIRE(expected.compare(q.toString()) == 0);
    REQUIRE(q.Size() == 3);
    
}

TEST_CASE("Dequeue - multiple duplicates for one node") {
    priorityqueue<string> q;
    q.enqueue("Paola", 1);
    q.enqueue("Thiago", 1);
    q.enqueue("Peluchina", 1);
    q.enqueue("Betty", 1);

    string value = q.dequeue();    // Remove Paola
    string expected = "1 value: Thiago\n1 value: Peluchina\n1 value: Betty\n";
    
    REQUIRE(value.compare("Paola") == 0);
    REQUIRE(expected.compare(q.toString()) == 0);
    REQUIRE(q.Size() == 3);
    
}

TEST_CASE("Dequeue - duplicates") {
    priorityqueue<string> q;
    q.enqueue("Paola", 1);
    q.enqueue("Thiago", 2);
    q.enqueue("Peluchina", 3);
    q.enqueue("Betty", 1);
    q.enqueue("Coco", 2);
    q.enqueue("Michi", 3);

    string value = q.dequeue();    // Remove Paola
    string expected = "1 value: Betty\n2 value: Thiago\n2 value: Coco\n3 value: Peluchina\n3 value: Michi\n";

    REQUIRE(value.compare("Paola") == 0);
    REQUIRE(expected.compare(q.toString()) == 0);
    REQUIRE(q.Size() == 5);
    
}

//--------------------------------------------------------------------------------------------
TEST_CASE("Peek - consecutive numbers right branch") {
    priorityqueue<string> q;
    q.enqueue("Paola", 1);
    q.enqueue("Thiago", 2);
    q.enqueue("Peluchina", 3);
    q.enqueue("Betty", 4);

    string value = q.peek();    // Return "Paola"
    string expected = "1 value: Paola\n2 value: Thiago\n3 value: Peluchina\n4 value: Betty\n";

    REQUIRE(value.compare("Paola") == 0);
    REQUIRE(expected.compare(q.toString()) == 0);
    
}

TEST_CASE("Peek - consecutive numbers left branch") {
    priorityqueue<string> q;
    q.enqueue("Paola", 4);
    q.enqueue("Thiago", 3);
    q.enqueue("Peluchina", 2);
    q.enqueue("Betty", 1);

    string value = q.peek();    // Return "Betty"
    string expected = "1 value: Betty\n2 value: Peluchina\n3 value: Thiago\n4 value: Paola\n";

    REQUIRE(value.compare("Betty") == 0);
    REQUIRE(expected.compare(q.toString()) == 0);
    
}

TEST_CASE("Peek - multiple duplicates for one node") {
    priorityqueue<string> q;
    q.enqueue("Paola", 1);
    q.enqueue("Thiago", 1);
    q.enqueue("Peluchina", 1);
    q.enqueue("Betty", 1);

    string value = q.peek();    // Return "Paola"
    string expected = "1 value: Paola\n1 value: Thiago\n1 value: Peluchina\n1 value: Betty\n";
    
    REQUIRE(value.compare("Paola") == 0);
    REQUIRE(expected.compare(q.toString()) == 0);
    
}

TEST_CASE("Peek - duplicates") {
    priorityqueue<string> q;
    q.enqueue("Paola", 1);
    q.enqueue("Thiago", 2);
    q.enqueue("Peluchina", 3);
    q.enqueue("Betty", 1);
    q.enqueue("Coco", 2);
    q.enqueue("Michi", 3);

    string value = q.peek();    // Return "Paola"
    string expected = "1 value: Paola\n1 value: Betty\n2 value: Thiago\n2 value: Coco\n3 value: Peluchina\n3 value: Michi\n";

    REQUIRE(value.compare("Paola") == 0);
    REQUIRE(expected.compare(q.toString()) == 0);
    
}

//--------------------------------------------------------------------------------------
TEST_CASE("Equality - Default constructor") {
    priorityqueue<string> q1;
    priorityqueue<string> q2;

    bool equal = q1 == q2;
    REQUIRE(equal);
    
    
}     

TEST_CASE("Equality - consecutive numbers right branch") {
    priorityqueue<string> q1;
    q1.enqueue("Paola", 1);
    q1.enqueue("Thiago", 2);
    q1.enqueue("Peluchina", 3);
    q1.enqueue("Betty", 4);
    
    priorityqueue<string> q2;
    q2.enqueue("Paola", 1);
    q2.enqueue("Thiago", 2);
    q2.enqueue("Peluchina", 3);
    q2.enqueue("Betty", 4);

    bool equal = q1 == q2;
    REQUIRE(equal);
    
    
} 


TEST_CASE("Equality - consecutive numbers left branch") {
    priorityqueue<string> q1;
    q1.enqueue("Betty", 4);
    q1.enqueue("Paola", 3);
    q1.enqueue("Thiago", 2);
    q1.enqueue("Peluchina", 1);
    
    priorityqueue<string> q2;
    q2.enqueue("Betty", 4);
    q2.enqueue("Paola", 3);
    q2.enqueue("Thiago", 2);
    q2.enqueue("Peluchina", 1);

    bool equal = q1 == q2;
    REQUIRE(equal);
    
    
}

TEST_CASE("Equality - non-consecutive numbers") {
    priorityqueue<string> q1;
    q1.enqueue("Paola", 3);
    q1.enqueue("Thiago", 8);
    q1.enqueue("Peluchina", 2);
    q1.enqueue("Betty", 13);

    priorityqueue<string> q2;
    q2.enqueue("Paola", 3);
    q2.enqueue("Thiago", 8);
    q2.enqueue("Peluchina", 2);
    q2.enqueue("Betty", 13);

    bool equal = q1 == q2;
    REQUIRE(equal);
    
    
}

TEST_CASE("Equality - multiple duplicates for one node") {
    priorityqueue<string> q1;
    q1.enqueue("Paola", 1);
    q1.enqueue("Thiago", 1);
    q1.enqueue("Peluchina", 1);
    q1.enqueue("Betty", 1);
    q1.enqueue("Coco", 1);
    q1.enqueue("Michi", 1);

    priorityqueue<string> q2;
    q2.enqueue("Paola", 1);
    q2.enqueue("Thiago", 1);
    q2.enqueue("Peluchina", 1);
    q2.enqueue("Betty", 1);
    q2.enqueue("Coco", 1);
    q2.enqueue("Michi", 1);

    bool equal = q1 == q2;
    REQUIRE(equal);
    
    
}

TEST_CASE("Equality - duplicates") {
    priorityqueue<string> q1;
    q1.enqueue("Paola", 1);
    q1.enqueue("Thiago", 2);
    q1.enqueue("Peluchina", 3);
    q1.enqueue("Betty", 1);
    q1.enqueue("Coco", 2);
    q1.enqueue("Michi", 3);

    priorityqueue<string> q2;
    q2.enqueue("Paola", 1);
    q2.enqueue("Thiago", 2);
    q2.enqueue("Peluchina", 3);
    q2.enqueue("Betty", 1);
    q2.enqueue("Coco", 2);
    q2.enqueue("Michi", 3);

    bool equal = q1 == q2;
    REQUIRE(equal);
    
    
}

//---------------------------------------------------------
TEST_CASE("Destructor - default constructor")
{
    priorityqueue<string> q;
}

TEST_CASE("Destructor - consecutive numbers right branch") {
    priorityqueue<string> q1;
    q1.enqueue("Paola", 1);
    q1.enqueue("Thiago", 2);
    q1.enqueue("Peluchina", 3);
    q1.enqueue("Betty", 4);
    
    priorityqueue<string> q2;
    q2.enqueue("Paola", 1);
    q2.enqueue("Thiago", 2);
    q2.enqueue("Peluchina", 3);
    q2.enqueue("Betty", 4);
} 


TEST_CASE("Destructor - consecutive numbers left branch") {
    priorityqueue<string> q1;
    q1.enqueue("Betty", 4);
    q1.enqueue("Paola", 3);
    q1.enqueue("Thiago", 2);
    q1.enqueue("Peluchina", 1);
    
    priorityqueue<string> q2;
    q2.enqueue("Betty", 4);
    q2.enqueue("Paola", 3);
    q2.enqueue("Thiago", 2);
    q2.enqueue("Peluchina", 1);
}

TEST_CASE("Destructor - non-consecutive numbers") {
    priorityqueue<string> q1;
    q1.enqueue("Paola", 3);
    q1.enqueue("Thiago", 8);
    q1.enqueue("Peluchina", 2);
    q1.enqueue("Betty", 13);

    priorityqueue<string> q2;
    q2.enqueue("Paola", 3);
    q2.enqueue("Thiago", 8);
    q2.enqueue("Peluchina", 2);
    q2.enqueue("Betty", 13);
}

TEST_CASE("Destructor - multiple duplicates for one node") {
    priorityqueue<string> q1;
    q1.enqueue("Paola", 1);
    q1.enqueue("Thiago", 1);
    q1.enqueue("Peluchina", 1);
    q1.enqueue("Betty", 1);
    q1.enqueue("Coco", 1);
    q1.enqueue("Michi", 1);

    priorityqueue<string> q2;
    q2.enqueue("Paola", 1);
    q2.enqueue("Thiago", 1);
    q2.enqueue("Peluchina", 1);
    q2.enqueue("Betty", 1);
    q2.enqueue("Coco", 1);
    q2.enqueue("Michi", 1);
}

TEST_CASE("Destructor - duplicates") {
    priorityqueue<string> q1;
    q1.enqueue("Paola", 1);
    q1.enqueue("Thiago", 2);
    q1.enqueue("Peluchina", 3);
    q1.enqueue("Betty", 1);
    q1.enqueue("Coco", 2);
    q1.enqueue("Michi", 3);

    priorityqueue<string> q2;
    q2.enqueue("Paola", 1);
    q2.enqueue("Thiago", 2);
    q2.enqueue("Peluchina", 3);
    q2.enqueue("Betty", 1);
    q2.enqueue("Coco", 2);
    q2.enqueue("Michi", 3);
}