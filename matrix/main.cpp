/*
----------------------------
  Paola Reyes
  2/14/23
  UIC CS 251, Wed 4pm Lab
  Prof. Adam Koehler
----------------------------    
Project 3 - Matrix

 Assignment details and provided code are created and
 owned by Adam T Koehler, PhD - Copyright 2023.
 University of Illinois Chicago - CS 251 Spring 2023

The mymatrix class provides a matrix (2D array) abstraction.
The size can grow dynamically in both directions (rows and 
cols).  Also, rows can be "jagged" --- i.e. rows can have 
different column sizes, and thus the matrix is not necessarily 
rectangular.  All elements are initialized to the default value
for the given type T.  Example:

  mymatrix<int>  M;  // 4x4 matrix, initialized to 0
  
  M(0, 0) = 123;
  M(1, 1) = 456;
  M(2, 2) = 789;
  M(3, 3) = -99;

  M.growcols(1, 8);  // increase # of cols in row 1 to 8

  for (int r = 0; r < M.numrows(); ++r)
  {
     for (int c = 0; c < M.numcols(r); ++c)
        cout << M(r, c) << " ";
     cout << endl;
  }

Output:
  123 0 0 0
  0 456 0 0 0 0 0 0
  0 0 789 0
  0 0 0 -99
*/
#include <iostream>
#include "mymatrix.h"
using namespace std;

int passed = 0;
int failed = 0;

// -----------------------------------------------------------------------------------------
// Test accessing using at() from a default matrix
bool at_test1() {
  mymatrix<int> M;

  if (M.at(0, 0) == 0) {  // Should be default value
    passed++;
  }
  else {
    cout << "at_test1() failed" << endl;
    failed++;
  }
}

// Test assigning a value multiple times to the same space
bool at_test2() {
  mymatrix<int> M;
  M.at(0, 0) = -1;
  M.at(0, 0) = -2;
  M.at(0, 0) = -3;  

  if (M.at(0, 0) == -3) {   // Most recent update
    passed++;
  }
  else {
    cout << "at_test2() failed" << endl;
    failed++;
  }
}

// Test at() with invalid arguments
bool at_test3() {
  try {
    mymatrix<int> M;
    M.at('0', -1) = -1;   // Out of bounds

    cout << "at_test3() failed: expected throw exception" << endl;
    failed++;
  }
  catch(...) {
    passed++;
  }
}

// Test at() with doubles arguments
bool at_test4() {
  mymatrix<int> M;
  M.at(3.111, 2.9999) = -1;   // Should convert doubles to int

  if (M.at(3.111, 2.999) == -1) {
    passed++;
  }
  else {
    cout << "at_test4() failed" << endl;
    failed++;
  }
}

// Test at() with out of bounds arguments
bool at_test5() {
  try {
    mymatrix<int> M;
    M.at(5, 2) = -1;
    M.at(2, 5) = -1;
    M.at(5, 8) = -1;

    cout << "at_test5() failed" << endl;
    failed++;
  }
  catch(...) {
    passed++;
  }
}

// Test at() after growcols() and grow()
bool at_test6() {
  mymatrix<int> M;
  M.growcols(0, 5);   // Row 0 is 1x5
  M.grow(5, 8);       // Matrix is 5x8

  M.at(4, 7) = -1;

  if (M.size() == 40 && M.at(0, 0) == 0 && M.at(4, 7) == -1) {
    passed++;
  }
  else {
    cout << "at_test6() failed" << endl;
    failed++;
  }
}

// Test at() after scalar and matrix multiplication
bool at_test7() {
  mymatrix<int> M1(1, 2);
  mymatrix<int> M2(2, 1);

  // Assign values to matrices
  M1.at(0, 0) = -1;
  M1.at(0, 1) = -1;

  M2.at(0, 0) = 5;
  M2.at(1, 0) = 5;

  mymatrix<int> M3 = M1 * 2;
  mymatrix<int> M4 = M1 * M2;   // Matrix is 1x1

  if (M3.at(0, 0) == -2 && M4.at(0, 0) == -10) {
    passed++;
  }
  else {
    cout << "at_test7() failed" << endl;
    failed++;
  } 
}

// -----------------------------------------------------------------------------------------
// Test accessing using () from a default matrix
bool parentheses_test1() {
  mymatrix<int> M;

  if (M(0, 0) == 0) {   // Should have default value
    passed++;
  }
  else {
    cout << "parentheses_test1_test1() failed" << endl;
    failed++;
  }
}

// Test assigning a value multiple times to the same space
bool parentheses_test2() {
  mymatrix<int> M;
  M(0, 0) = -1;
  M(0, 0) = -2;
  M(0, 0) = -3;

  if (M(0, 0) == -3) {  // Most recent assignment
    passed++;
  }
  else {
    cout << "parentheses_test2() failed" << endl;
    failed++;
  }
}

// Test () with invalid arguments
bool parentheses_test3() {
  try {
    mymatrix<int> M;
    M('0', -1) = -1;  // Out of bounds

    cout << "parentheses_test3() failed: expected throw exception" << endl;
    failed++;
  }
  catch(...) {
    passed++;
  }
}

// Test at() with doubles arguments
bool parentheses_test4() {
  mymatrix<int> M;
  M(3.111, 2.9999) = -1;   // Should convert to int

  if (M(3.111, 2.999) == -1) {
    passed++;
  }
  else {
    cout << "parentheses_test4() failed" << endl;
    failed++;
  }
}

// Test () with out of bounds arguments
bool parentheses_test5() {
  try {
    mymatrix<int> M;
    M(5, 2) = -1;
    M(2, 5) = -1;
    M(5, 8) = -1;

    cout << "parentheses_test5() failed" << endl;
    failed++;
  }
  catch(...) {
    passed++;
  }
}

// Test at() after growcols() and grow()
bool parentheses_test6() {
  mymatrix<int> M;
  M.growcols(0, 5);   // Row 0 is 1x5
  M.grow(5, 8);       // Matrix is 5x8

  M(4, 7) = -1;

  if (M.size() == 40 && M(0, 0) == 0 && M(4, 7) == -1) {
    passed++;
  }
  else {
    cout << "parentheses_test6() failed" << endl;
    failed++;
  }
}

// Test at() after scalar and matrix multiplication
bool parentheses_test7() {
  mymatrix<int> M1(1, 2);
  mymatrix<int> M2(2, 1);

  // Assign values to matrices
  M1(0, 0) = -1;
  M1(0, 1) = -1;

  M2(0, 0) = 5;
  M2(1, 0) = 5;

  mymatrix<int> M3 = M1 * 2;
  mymatrix<int> M4 = M1 * M2;

  if (M3(0, 0) == -2 && M4(0, 0) == -10) {
    passed++;
  }
  else {
    cout << "parentheses_test7() failed" << endl;
    failed++;
  } 
}

// -----------------------------------------------------------------------------------------
// Test default constructor. Makes a 4x4 matrix which makes 16 elements
bool size_test1()    
{
  mymatrix<int> M;  // Matrix is 4x4

  if (M.size() == 16) {
    passed++;
  }
  else {
    cout << "size_test1() failed" << endl;
    failed++;
  }
} 

// Test using size() of an invalid mymatrix
bool size_test2()    
{
  try {
    mymatrix<int>  M('0', -1); 
    int s = M.size() + 1;

    cout << "size_test2() failed: expected throw exception" << endl;
    failed++;
  }
  catch (...) {
    passed++;   // Exception was thrown
  }
} 

// Test size() on the parameterized constructor
bool size_test3() {
  mymatrix<int> M(5, 2);

  if (M.size() == 10) {
    passed++;
  }
  else {
    cout << "size_test3() failed" << endl;
    failed++;
  }
}

// Test size() on the copy constructor
bool size_test4() {
  mymatrix<int> M1(5, 2);
  mymatrix<int> M2(M1);   // Should be 5x2

  if (M2.size() == 10) {
    passed++;
  }
  else {
    cout << "size_test4() failed" << endl;
    failed++;
  }
}

// Test size() on a jagged matrix
bool size_test5() {
  mymatrix<int> M;    // 4x4 matrix
  M.growcols(0, 5);   // Row 1 has 5 elements
  M.growcols(1, 6);   // Row 2 has 6 elements
  M.growcols(2, 7);   // Row 3 has 7 elements
  M.growcols(3, 8);   // Row 4 has 8 elements

  if (M.size() == 26) {
    passed++;
  }
  else {
    cout << "size_test6() failed" << endl;
    failed++;
  }
}

// Test size() after multiple grow() calls
bool size_test6() {
  mymatrix<int> M;  // 4x4 matrix
  M.grow(5, 8);     // 5x8 matrix
  M.grow(8, 10);    // 8x10 matrix

  if (M.size() == 80) {
    passed++;
  }
  else {
    cout << "size_test6() failed" << endl;
    failed++;
  }
}

// Test size after scalar multiplication 
bool size_test7() {
  mymatrix<int> M1(5, 2);
  mymatrix<int> M2 = M1 * 2;  // 5x2 matrix

  if (M2.size() == 10) {
    passed++;
  }
  else {
    cout << "size_test7() failed" << endl;
    failed++;
  }
}

// Test scalar multiplication stored into a matrix of different size
bool size_test8() {
  mymatrix<int> M1(2, 2);
  M1(0, 0) = -1;
  M1(0, 1) = -1;
  M1(1, 0) = -1;
  M1(1, 1) = -1;

  mymatrix<int> M2;   // 4x4 matrix
  M2 = M1 * 2;        // Becomes 2x2 matrix 

  if (M2.size() == 4) {
    passed++;
  }
  else {
    cout << "size_test8() failed" << endl;
    failed++;
  }
}

// Test size() after matrix multiplication
bool size_test9() {
  mymatrix<int> M1(1, 2);
  mymatrix<int> M2(2, 3);
  mymatrix<int> M3 = M1 * M2;   // 1x3 matrix

  if (M3.size() == 3) {
    passed++;
  }
  else {
    cout << "size_test9() failed" << endl;
    failed++;
  }
}

// -----------------------------------------------------------------------------------------
// Test numrows() for a default mymatrix
bool numrows_test1() {
  mymatrix<int> M;   // 4x4 matrix

  if (M.numrows() == 4) {
    passed++;
  }
  else {
    cout << "numrows_test1() failed" << endl;
    failed++;
  }
}

// Test numrows() for the parameterized constructor
bool numrows_test2() {
  mymatrix<int> M(5, 2);

  if (M.numrows() == 5) {
    passed++;
  }
  else {
    cout << "numrows_test2() failed" << endl;
    failed++;
  }
}

// Test numrows() for the copy constructor
bool numrows_test3() {
  mymatrix<int> M1(5, 2);
  
  // Assign values
  M1(0, 0) = -1;
  M1(0, 1) = -1;
  M1(1, 0) = -1;
  M1(1, 1) = -1;

  mymatrix<int> M2(M1);   // 5x2 matrix

  if (M2.numrows() == M1.numrows()) {
    passed++;
  }
  else {
    cout << "numrows_test3() failed" << endl;
    failed++;
  }
}

// Test numrows after multiple grow() calls
bool numrows_test4() {
  mymatrix<int> M;  // 4x4 matrix
  M.grow(5, 8);     // 5x8 matrix
  M.grow(2, 2);     // Shouldn't grow
  M.grow(8, 10);    // 8x10 matrix

  if(M.numrows() == 8) {
    passed++;
  } 
  else {
    cout << "numrows_test4() failed" << endl;
    failed++;
  }
}

// -----------------------------------------------------------------------------------------
// Test numcols() for a default mymatrix
bool numcols_test1() {
  mymatrix<int> M;  // 4x4 matrix

  if (M.numcols(0) == 4 && M.numcols(1) == 4 && M.numcols(2) == 4 && M.numcols(3) == 4) {
    passed++;
  }
  else {
    cout << "numcols_test1() failed" << endl;
    failed++;
  }
}

// Test numcols() for the parameterized constructor
bool numcols_test2() {
  mymatrix<int> M(5, 2);

  if (M.numcols(0) == 2 && M.numcols(1) == 2 && M.numcols(2) == 2 && M.numcols(3) == 2 && M.numcols(4) == 2) {
    passed++;
  }
  else {
    cout << "numcols_test2() failed" << endl;
    failed++;
  }
}

// Test numcols() for the copy constructor
bool numcols_test3() {
  mymatrix<int> M1(5, 2);
  // Assign values
  M1(0, 0) = 1;
  M1(0, 1) = 2;
  M1(1, 0) = 3;
  M1(1, 1) = 4;

  mymatrix<int> M2(M1);

  if (M2.numcols(0) == 2 && M2.numcols(1) == 2 && M2.numcols(2) == 2 && M2.numcols(3) == 2 && M2.numcols(4) == 2) {
    passed++;
  }
  else {
    cout << "numcols_test3() failed" << endl;
    failed++;
  }
}

// Test numcols() after multiple growcols() is called for same row
bool numcols_test4() {
  mymatrix<int> M;    // 4x4 matrix
  M.growcols(2, 5);   // Row 2 has 5 elements
  M.growcols(2, 2);   // Shouldn't grow
  M.growcols(2, 8);   // Row 2 has 8 elements

  if (M.numcols(2) == 8) {
    passed++;
  }
  else {
    cout << "numcols_test4() failed" << endl;
    failed++;
  }
}

// Test numcols() after multiple grow() are called
bool numcols_test5() {
  mymatrix<int> M;  // 4x4 matrix
  M.grow(5, 5);     // 5x5 matrix
  M.grow(2, 2);     // Shouldn't grow
  M.grow(6, 4);     // 6x5 matrix
  M.grow(3, 6);     // 6x6 matrix 

  if (M.size() == 36 && M.numrows() == 6 &&
      M.numcols(0) == 6 && M.numcols(0) == 6 && M.numcols(0) == 6 && M.numcols(0) == 6 && M.numcols(0) == 6 && M.numcols(0) == 6) {
    passed++;
  }
  else {
    cout << "numcols_test5() failed" << endl;
    failed++;
  }
}

// Test numcols() with double as argument
bool numcols_test6() {
  mymatrix<int> M;  // 4x4 matrix

  if (M.numcols(3.111) == 4) {  // Converts double to int
    passed++;
  }
  else {
    cout << "numcols_test6() failed" << endl;
    failed++;
  }
}

// -----------------------------------------------------------------------------------------
// Test default constructor works correctly
bool default_constructor_test1() {
  mymatrix<int> M;  // 4x4 matrix

  if (M.size() == 16 && M.numrows() == 4 && 
      M.numcols(0) == 4 && M.numcols(1) == 4 && M.numcols(2) == 4 && M.numcols(3) == 4 &&
      M(0, 0) == 0 && M(0, 1) == 0 && M(0, 1) == 0 && M(0, 1) == 0 &&
      M(1, 0) == 0 && M(1, 1) == 0 && M(1, 2) == 0 && M(1, 2) == 0 &&
      M(2, 0) == 0 && M(2, 1) == 0 && M(2, 2) == 0 && M(2, 2) == 0 &&
      M(3, 0) == 0 && M(3, 1) == 0 && M(3, 2) == 0 && M(3, 2) == 0) {
        passed++;
  }
  else {
    cout << "default_constructor_test1() failed" << endl;
    failed++;
  }
}

// Test changing the values of a default matrix
bool default_constructor_test2() {
  mymatrix<int> M;
  // Assign values
  M(0, 0) = -1;
  M(1, 0) = -1;
  M(2, 0) = -1;
  M(3, 0) = -1;

  if (M(0, 0) == -1 && M(0, 1) == 0 && M(0, 1) == 0 && M(0, 1) == 0 &&
      M(1, 0) == -1 && M(1, 1) == 0 && M(1, 2) == 0 && M(1, 2) == 0 &&
      M(2, 0) == -1 && M(2, 1) == 0 && M(2, 2) == 0 && M(2, 2) == 0 &&
      M(3, 0) == -1 && M(3, 1) == 0 && M(3, 2) == 0 && M(3, 2) == 0) {
        passed++;
  }
  else {
    cout << "default_constructor_test3() failed" << endl;
    failed++;
  }
}

// -----------------------------------------------------------------------------------------
// Test parameterized constructor throw exception for invalid values
bool param_constructor_test1()
{
  try {
    mymatrix<int>  M('0', -1); // Out of bounds

    cout << "param_constructor_test1() failed: expected throw exception" << endl;
    failed++;
  }
  catch (...) {
    passed++;   // Exception was thrown
  }
}

// Test if parameterized constructor allocates correct amount of spaces
bool param_constructor_test2() {
  mymatrix<int> M(5, 2);

  if (M.size() == 10) {
    passed++;
  }
  else {
    cout << "param_constructor_test2() failed" << endl;
    failed++;
  }
}

// Test parameter constructor with doubles as arguments
bool param_constructor_test3() {
  mymatrix<int> M(2.111, 5.999);  // Converts doubles to ints

  if (M.size() == 10) {
    passed++;
  }
  else {
    cout << "param_constructor_test3() failed" << endl;
    failed++;
  }
}
// -----------------------------------------------------------------------------------------
// Test copy constructor given a default matrix
bool copy_constructor_test1() {
  mymatrix<int> M1;
  mymatrix<int> M2(M1);

  if (M2(0, 0) == 0 && M2(0, 1) == 0 && M2(0, 1) == 0 && M2(0, 1) == 0 &&
      M2(1, 0) == 0 && M2(1, 1) == 0 && M2(1, 2) == 0 && M2(1, 2) == 0 &&
      M2(2, 0) == 0 && M2(2, 1) == 0 && M2(2, 2) == 0 && M2(2, 2) == 0 &&
      M2(3, 0) == 0 && M2(3, 1) == 0 && M2(3, 2) == 0 && M2(3, 2) == 0) {
    passed++;
  }
  else {
    cout << "copy_constructor_test1() failed" << endl;
    failed++;
  }
}

// Test copying two matrixes of the same size and initialized values
bool copy_constructor_test2() {
  mymatrix<int> M1(2, 2);
  // Assign values
  M1(0, 0) = -1;
  M1(0, 1) = -1;
  M1(1, 0) = -1;
  M1(1, 1) = -1;

  mymatrix<int> M2(M1); // 2x2 array 

  if (M2(0, 0) == -1 && M2(0, 1) == -1 && M2(1, 0) == -1 && M2(1, 1) == -1) {
    passed++;
  }
  else {
    cout << "copy_constructor_test2() failed" << endl;
    failed++;
  }
}

// Test changing the orignal mymatrix's values doesn't reflect on the copy constructor 
bool copy_constructor_test3() {
  mymatrix<int> M1;
  // Assign values
  M1(0, 0) = -1;
  M1(0, 1) = -1;
  M1(1, 0) = -1;
  M1(1, 1) = -1;

  mymatrix<int> M2(M1);   
  M1(0, 0) = 5;   // Change a M1 value

  if (M2(0, 0) == -1 && M1(0, 0) == 5) {  // M2 should retain -1 value
    passed++;
  }
  else {
    cout << "copy_constructor_test3() failed" << endl;
    // cout << M2(0, 0) << endl;
    // cout << M1(0, 0) << endl;
    failed++;
  }
}

// Test copy constructor on default matrix with assigned values
bool copy_constructor_test4() {
  mymatrix<int> M1;
  // Assign values
  M1(0, 0) = 1;
  M1(0, 1) = 1;
  M1(0, 2) = 1;
  M1(0, 3) = 1;
  M1(1, 0) = 2;
  M1(1, 1) = 2;
  M1(1, 2) = 2;
  M1(1, 3) = 2;
  M1(2, 0) = 3;
  M1(2, 1) = 3;
  M1(2, 2) = 3;
  M1(2, 3) = 3;
  M1(3, 0) = 4;
  M1(3, 1) = 4;
  M1(3, 2) = 4;
  M1(3, 3) = 4;

  mymatrix<int> M2(M1);

  if (M2(0, 0) == 1 && M2(0, 1) == 1 && M2(0, 1) == 1 && M2(0, 1) == 1 &&
      M2(1, 0) == 2 && M2(1, 1) == 2 && M2(1, 2) == 2 && M2(1, 2) == 2 &&
      M2(2, 0) == 3 && M2(2, 1) == 3 && M2(2, 2) == 3 && M2(2, 2) == 3 &&
      M2(3, 0) == 4 && M2(3, 1) == 4 && M2(3, 2) == 4 && M2(3, 2) == 4) {
      passed++;
  }
  else {
    cout << "copy_constructor_test4() failed" << endl;
    failed++;
  }
}

// Test copy constructor on a jagged matrix
bool copy_constructor_test5() {
  mymatrix<int> M1(4, 1); // 4x1 matrix
  M1.growcols(0, 2);      // Row 1 has 2 elements
  M1.growcols(1, 3);      // Row 2 has 3 elements
  M1.growcols(2, 4);      // Row 3 has 4 elements
  M1.growcols(3, 2);      // Row 4 has 2 elements

  M1(0, 0) = 1;
  M1(0, 1) = 1;
  M1(1, 0) = 2;
  M1(1, 1) = 2;
  M1(1, 2) = 2;
  M1(2, 0) = 3;
  M1(2, 1) = 3;
  M1(2, 2) = 3;
  M1(2, 3) = 3;
  M1(3, 0) = 4;
  M1(3, 1) = 4;

  mymatrix<int> M2(M1);

  if (M2(0, 0) == 1 && M2(0, 1) == 1 &&
      M2(1, 0) == 2 && M2(1, 1) == 2 && M2(1, 2) == 2 &&
      M2(2, 0) == 3 && M2(2, 1) == 3 && M1(2, 2) == 3 && M2(2, 3) == 3 &&
      M2(3, 0) == 4 && M2(3, 1) == 4) {
        passed++;
  }
  else {
    cout << "copy_constructor_test6() failed" << endl;
    failed++;
  }
}
// -----------------------------------------------------------------------------------------
// Test growcols() on a default mymatrix
bool growcols_test1() {
  mymatrix<int> M;    // 4x4 matrix
  M.growcols(3, 8);   // Row 4 has 8 elements

  if (M.numcols(3) == 8) {
    passed++;
  }
  else {
    cout << "growcols_test1() failed" << endl;
    failed++;
  }
}

// Test growcols() on parameterized constructor and on mymatrix with more than/equal to C columns
bool growcols_test2() {
  mymatrix<int> M(3, 8);  // 3x8 matrix
  M.growcols(2, 5);       // Shouldn't change
  M.growcols(2, 8);       // Shouldn't change

  if (M.numcols(2) == 8) {
    passed++;
  }
  else {
    cout << "growcols_test2() failed" << endl;
    failed++;
  }
}

// Test that growcols adds empty values to mymatrix
bool growcols_test3() {
  mymatrix<int> M;
  M.growcols(3, 8);   // Row 4 has 3 new values 

  if (M(3, 5) == 0 && M(3, 6) == 0 && M(3, 7) == 0) {
    passed++;
  }
  else {
    cout << "growcol_test3() failed" << endl;
    failed++;
  }
}

// Test growcols() with invalid input
bool growcols_test4() {
  try {
    mymatrix<int> M;
    M.growcols('0', -1);  // Out of bounds

    cout << "growcols_test4() failed: expected throw exception" << endl;
    failed++;
  }
  catch(...) {
    passed++;
  }
}

// Test growcols() with a row that is out bounds
bool growcols_test5() {
  try {
    mymatrix<int> M;    // 4x4 matrix
    M.growcols(8, 3); 

    cout << "growcols_test5() failed: expected throw exception" << endl;
  }
  catch(...) {
    passed++;
  }
}

// Test growcols() on multiple rows
bool growcols_test6() {
  mymatrix<int> M;    // 4x4 matrix
  M.growcols(0, 6);   // Row 1 has 6 elements
  M.growcols(1, 7);   // Row 2 has 7 elements
  M.growcols(2, 2);   // Shouldn't grow
  M.growcols(3, 8);   // Row 4 has 8 elements

  if (M.numcols(0) == 6 && M.numcols(1) == 7 && M.numcols(2) == 4 && M.numcols(3) == 8) {
    passed++;
  }
  else {
    cout << "growcols_test6() failed" << endl;
    failed++;
  }
}

// Test growcols() called more than once for same row
bool growcols_test7() {
  mymatrix<int> M;    // 4x4 matrix
  M.growcols(2, 5);   // Row 2 has 5 elements
  M.growcols(2, 8);   // Row 8 has 8 elements
  M.growcols(2, 2);   // Shouldn't grow

  if (M.numcols(2) == 8) {
    passed++;
  }
  else {
    cout << "growcols_test7() failed" << endl;
    failed++;
  }
}

// Test growcols() retained the orignal column values
bool growcols_test8() {
  mymatrix<int> M(2, 2);
  // Assign values
  M(0, 0) = -1;
  M(0, 1) = -1;
  M(1, 0) = -1;
  M(1, 1) = -1;

  M.growcols(0, 4);   // Each row has 2 new values

  if (M(0, 0) == -1 && M(0, 1) == -1 && M(0, 2) == 0 && M(0, 3) == 0) {
    passed++;
  }
  else {
    cout << "growcols_test8() failed" << endl;
    failed++;
  }
}

// Test growcols() with a double argument
bool growcols_test9() {
  mymatrix<int> M;
  // Turns doubles to ints
  M.growcols(0, 5.999);   // Row 1 has 5 elements
  M.growcols(3.111, 5);   // Row 4 has 5 elements

  if (M.numcols(0) == 5 && M.numcols(3) == 5) {
    passed++;
  }
  else {
    cout << "growcols_test9() failed" << endl;
    failed++;
  }
}
// -----------------------------------------------------------------------------------------
// Test grow() on a default matrix
bool grow_test1() {
  mymatrix<int> M;  // 4x4 matrix
  M.grow(5, 5);     // 5x5 matrix

  if (M.size() == 25 && M.numrows() == 5 && M.numcols(0) == 5 &&
      M.numcols(0) == 5 && M.numcols(1) == 5 && M.numcols(2) == 5 && M.numcols(3) == 5 && M.numcols(4) == 5) {
    passed++;
  }
  else {
    cout << "grow_test1() failed" << endl;
    failed++;
  }
}

// Test grow() on parameterized constructor and on mymatrix with more than C columns
bool grow_test2() {
  mymatrix<int> M(2, 5);  // 2x5 matrix
  M.grow(5, 8);   // 5x8 matrix

  if (M.size() == 40 && M.numrows() == 5 &&
      M.numcols(0) == 8 && M.numcols(0) == 8 && M.numcols(0) == 8 && M.numcols(0) == 8 && M.numcols(0) == 8) {
    passed++;
  }
  else {
    cout << "grow_test2() failed" << endl;
    failed++;
  }
}

// Test that grow() adds empty values to mymatrix
bool grow_test3() {
  mymatrix<int> M;    // 4x4 matrix
  M.grow(5, 8);       // 5x8 matrix

  if (M(4, 0) == 0 && M(4, 1) == 0 && M(4, 2) == 0 && M(4, 3) == 0 && 
      M(4, 4) == 0 && M(4, 5) == 0 && M(4, 6) == 0 && M(4, 7) == 0) {
    passed++;
  }
  else {
    cout << "grow_test3() failed" << endl;
    failed++;
  }
}

// Test grow() with invalid input
bool grow_test4() {
  try {
    mymatrix<int> M;
    M.grow('0', -1);  // Out of bounds

    cout << "growcols_test4() failed: expected throw exception" << endl;
    failed++;
  }
  catch(...) {
    passed++;
  }
}

// Test grow() on a matrix greater than or equal to the grow size
bool grow_test5() {
  mymatrix<int> M(8, 5);  
  M.grow(5, 2);   // Shouldn't change
  M.grow(8, 5);   // Shouldn't change

  if (M.size() == 40) {
    passed++;
  }
  else {
    cout << "grow_test5 failed" << endl;
    failed++;
  }
}

// Test grow() called more than once for same row size and different col size
bool grow_test6() {
  mymatrix<int> M;  // 4x4 matrix
  M.grow(5, 5);     // 5x5 matrix
  M.grow(5, 6);     // 5x6 matrix
  M.grow(5, 2);     // Shouldn't grow

  if (M.size() == 30) {
    passed++;
  }
  else {
    cout << "grow_test6() failed" << endl;
    cout << M.size() << endl;
    failed++;
  }
}

// Test grow() called more than once for same col size and different row size
bool grow_test7() {
  mymatrix<int> M;  // 4x4 matrix
  M.grow(5, 5);     // 5x5 matrix
  M.grow(6, 5);     // 6x5 matrix
  M.grow(2, 5);     // Shouldn't grow

  if (M.size() == 30) {
    passed++;
  }
  else {
    cout << "grow_test7() failed" << endl;
    cout << M.size() << endl;
    failed++;
  }
}

// Test grow() retained the orignal column values
bool grow_test8() {
  mymatrix<int> M(2, 2);  // 2x2 matrix
  // Assign values
  M(0, 0) = -1;
  M(0, 1) = -1;
  M(1, 0) = -1;
  M(1, 1) = -1;

  M.grow(3, 3); // 3x3 matrix

  if (M(0, 0) == -1 && M(0, 1) == -1 && M(0, 2) == 0 &&
      M(1, 0) == -1 && M(1, 1) == -1 && M(1, 2) == 0 &&
      M(2, 0) == 0  && M(2, 1) == 0  && M(2, 2) == 0) {
    passed++;
  }
  else {
    cout << "grow_test8() failed" << endl;
    failed++;
  }
}

// Test grow() for a jagged matrix where only rows changes
bool grow_test9() {
  mymatrix<int> M;    // 4x4 matrix
  M.growcols(0, 5);   // Row 1 has 5 elements
  M.growcols(1, 6);   // Row 2 has 6 elements
  M.growcols(2, 7);   // Row 3 has 7 elements
  M.growcols(3, 8);   // Row 4 has 8 elements
  M.grow(5, 3);       // Row 5 has 3 elements

  if (M.size() == 29 && M.numrows() == 5 &&
      M.numcols(0) == 5 && M.numcols(1) == 6 && M.numcols(2) == 7 && M.numcols(3) == 8 && M.numcols(4) == 3) {
        passed++;
  }
  else {
    cout << "grow_test9() failed" << endl;
    // cout << M.numcols(2) << endl;
    failed++;
  }   
}
 
// Test grow() for a jagged matric where only cols changes
bool grow_test10() {
  mymatrix<int> M(3, 2);  // 3x2 matrix
  M.growcols(0, 3);       // Row 1 has 3 elements
  M.growcols(1, 4);       // Row 2 has 4 elements
  M.growcols(2, 5);       // Row 3 has 5 elements
  M.grow(4, 6);           // 4x6 matrix

  if (M.size() == 24 && M.numrows() == 4 &&
      M.numcols(0) == 6 && M.numcols(1) == 6 && M.numcols(2) == 6 && M.numcols(3) == 6) {
        passed++;
  }
  else {
    cout << "grow_test10() failed" << endl;
    failed++;
  }   
}

// Test grow() with double as argument
bool grow_test11() {
  mymatrix<int> M;    // 4x4 matrix
  M.grow(5.999, 2);   // 5x4 matrix
  M.grow(3.111, 8);   // 5x8 matrix

  if (M.size() == 40) {   // Doubles were converted to ints
    passed++;
  }
  else {
    cout << "grows_test11 failed" << endl;
    failed++;
  }
}

// -----------------------------------------------------------------------------------------
// Test scalar multiplication on default mymatrix
bool scalar_test1() {
  mymatrix<int> M1;
  mymatrix<int> M2 = M1 * 2;  // Default value is 0 * 2 = 0

  if (M2(0, 0) == 0 && M2(0, 1) == 0 && M2(0, 2) == 0 && M2(0, 3) == 0 &&
      M2(1, 0) == 0 && M2(1, 1) == 0 && M2(1, 2) == 0 && M2(1, 3) == 0 &&
      M2(2, 0) == 0 && M2(2, 1) == 0 && M2(2, 2) == 0 && M2(2, 3) == 0 &&
      M2(3, 0) == 0 && M2(3, 1) == 0 && M2(3, 2) == 0 && M2(3, 3) == 0) {
        passed++;
  }
  else {
    cout << "scalar_test1() failed" << endl;
    failed++;
  }
}

// Test scalar multiplication on a default initialized mymatrix
bool scalar_test2() {
  mymatrix<int> M1;
  // Assign some values
  M1(0, 0) = -1;
  M1(0, 1) = -1;
  M1(0, 2) = -1;
  M1(0, 3) = -1;
  M1(1, 0) = -1;
  M1(1, 1) = -1;
  M1(1, 2) = -1;
  M1(1, 3) = -1;

  mymatrix<int> M2 = M1 * 2;

  // Some values are -1 * 2 = -2 and some are 0 * 2 = 0
  if (M2(0, 0) == -2 && M2(0, 1) == -2 && M2(0, 2) == -2 && M2(0, 3) == -2 &&
      M2(1, 0) == -2 && M2(1, 1) == -2 && M2(1, 2) == -2 && M2(1, 3) == -2 &&
      M2(2, 0) == 0 && M2(2, 1) == 0 && M2(2, 2) == 0 && M2(2, 3) == 0 &&
      M2(3, 0) == 0 && M2(3, 1) == 0 && M2(3, 2) == 0 && M2(3, 3) == 0) {
    passed++;
  }
  else {
    cout << "scalar_test2() failed" << endl;
    failed++;
  }
}

// Test scalar multiplication stored to the same mymatrix
bool scalar_test3() {
  mymatrix<int> M;
  M(0, 0) = -1;
  M(0, 1) = -1;
  M(0, 2) = -1;
  M(0, 3) = -1;
  M(1, 0) = -1;
  M(1, 1) = -1;
  M(1, 2) = -1;
  M(1, 3) = -1;

  M = M * 2;

  // M values got updated
  if (M(0, 0) == -2 && M(0, 1) == -2 && M(0, 2) == -2 && M(0, 3) == -2 &&
      M(1, 0) == -2 && M(1, 1) == -2 && M(1, 2) == -2 && M(1, 3) == -2 &&
      M(2, 0) == 0 && M(2, 1) == 0 && M(2, 2) == 0 && M(2, 3) == 0 &&
      M(3, 0) == 0 && M(3, 1) == 0 && M(3, 2) == 0 && M(3, 3) == 0) {
        passed++;
  }
  else {
    cout << "scalar_test3() failed" << endl;
    failed++;
  }
}

// Test scalar multiplication stored into a mymatrix of different size
bool scalar_test4() {
  mymatrix<int> M1(2, 2);
  M1(0, 0) = -1;
  M1(0, 1) = -1;
  M1(1, 0) = -1;
  M1(1, 1) = -1;

  mymatrix<int> M2; // 4x4 matrix
  M2 = M1 * 2;      // 2x2 matrix

  if (M2.size() == 4 && M2(0, 0) == -2 && M2(0, 1) == -2 && M2(1, 0) == -2 && M2(1, 1) == -2) {
    passed++;
  }
  else {
    cout << "scalar_test4() failed" << endl;
    failed++;
  }
}

// Test scalar multiplication stored into a pre-existing mymatrix
bool scalar_test5() {
  mymatrix<int> M1(2, 2);
  M1(0, 0) = -1;
  M1(0, 1) = -1;
  M1(1, 0) = -1;
  M1(1, 1) = -1;

  mymatrix<int> M2(2, 4); // 2x4 matrix
  M2(0, 0) = 5;
  M2(0, 1) = 5;
  M2(0, 2) = 5;
  M2(1, 0) = 5;
  M2(1, 1) = 5;
  M2(1, 2) = 5;
  M2(1, 3) = 5;

  M2 = M1 * 2;  // 2x2 matrix

  if (M2.size() == 4 &&
      M2(0, 0) == -2 && M2(0, 1) == -2 && M2(0, 1) == -2 && M2(0, 1) == -2 &&
      M2(1, 1) == -2 && M2(1, 1) == -2 && M2(1, 1) == -2 && M2(1, 1) == -2) {
        passed++;
  }
  else {
    cout << "scalar_test5() failed" << endl;
    failed++;
  }
}

// Test scalar multiplciation made a deep copy
bool scalar_test6() {
  mymatrix<int> M1;
  mymatrix<int> M2 = M1 * 2;

  M1(0, 0) = -1;  // Change a M1 value

  if (M2(0, 0) == 0) {  // M2 same element is unchanged
    passed++;
  }
  else {
    cout << "scalar_test6() failed" << endl;
    failed++;
  }
}

// Test scalar multiplication involving different types
bool scalar_test7() {
  mymatrix<int> M1(1, 1);
  M1(0, 0) = 1;

  mymatrix<int> M2 = M1 * 5.999;  // Converts values to int
  mymatrix<int> M3 = M1 * 'a';

  if (M2(0, 0) == 5 && M3(0, 0) == 97) {
    passed++;
  }
  else {
    cout << "scalar_test7() failed" << endl;
    failed++;
  }
}

// Test scalar multiplication using a jagged matrix
bool scalar_test8() {
  mymatrix<int> M(4, 1);  // 4x1 matrix
  // Assign values
  M(0, 0) = -1;
  M(1, 0) = -1;
  M(2, 0) = -1;
  M(3, 0) = -1;

  M.growcols(0, 2);       // Row 1 has 2 elements
  M.growcols(1, 3);       // Row 2 has 3 elements
  M.growcols(2, 4);       // Row 3 has 4 elements
  M.growcols(3, 5);       // Row 4 has 5 elements

  M = M * 2;

  if (M.size() == 14 && 
      M(0, 0) == -2 && M(0, 1) == 0 &&
      M(1, 0) == -2 && M(1, 1) == 0 && M(1, 2) == 0 &&
      M(2, 0) == -2 && M(2, 1) == 0 && M(2, 2) == 0 && M(2, 3) == 0 &&
      M(3, 0) == -2 && M(3, 1) == 0 && M(3, 2) == 0 && M(3, 3) == 0 && M(3, 4) == 0) {
        passed++;
  }
  else {
    cout << "scalar_test8() failed" << endl;
    failed++;
    M._output();
  }
}

// -----------------------------------------------------------------------------------------
// Test multiplying 2 default matrices
bool multiply_test1() {
  mymatrix<int> M1;
  mymatrix<int> M2;
  mymatrix<int> M3 = M1 * M2; // 4x4 matrix filled w 0's

  if (M3(0, 0) == 0 && M3(0, 1) == 0 && M3(0, 2) == 0 && M3(0, 3) == 0 &&
      M3(1, 0) == 0 && M3(1, 1) == 0 && M3(1, 2) == 0 && M3(1, 3) == 0 &&
      M3(2, 0) == 0 && M3(2, 1) == 0 && M3(2, 2) == 0 && M3(2, 3) == 0 &&
      M3(3, 0) == 0 && M3(3, 1) == 0 && M3(3, 2) == 0 && M3(3, 3) == 0) {
        passed++;
  }
  else {
    cout << "multiply_test1() failed" << endl;
    failed++;
  }
}

// Test multiplying 2 initilized matrices with parameterized constructor
bool multiply_test2() {
  mymatrix<int> M1(1, 2);
  M1(0, 0) = -1;
  M1(0, 1) = -1;

  mymatrix<int> M2(2, 1);
  M2(0, 0) = -1;
  M2(1, 0) = -1;

  mymatrix<int> M3 = M1 * M2;   // 1x1 matrix with value of 2

  if (M3.size() == 1 && M3(0, 0) == 2) {
    passed++;
  }
  else {
    cout << "multiply_test2() failed" << endl;
    failed++;
  }
}

// Test multiplying with the copy constructor
bool multiply_test3() {
  mymatrix<int> M1(2, 2);
  M1(0, 0) = -1;
  M1(0, 1) = -1;
  M1(1, 0) = -1;
  M1(1, 1) = -1;

  mymatrix<int> M2(M1);
  mymatrix<int> M3 = M1 * M2; // 4x4 matrix with all 2's

  if (M3(0, 0) == 2 && M3(0, 1) == 2 && M3(1, 0) == 2 && M3(1, 1) == 2) {
    passed++;
  }
  else{
    cout << "multiply_test3() failed" << endl;
    failed++;
  }  
}

// Test multiplying incompatible matrices
bool multiply_test4() {
  try {
    mymatrix<int> M1(5, 2);
    mymatrix<int> M2(3, 8);
    mymatrix<int> M3 = M1 * M2; // 2 != 3 

    cout << "multiply_test4() failed: expected throw exception" << endl;
    failed++;
  }
  catch (...) {
    passed++;
  }
}

// Test multiplying into a pre-existing matrix
bool multiply_test5() {
  mymatrix<int> M1(1, 2);
  M1(0, 0) = -1;
  M1(0, 1) = -1;

  mymatrix<int> M2(2, 1);
  M2(0, 0) = -1;
  M2(1, 0) = -1;

  mymatrix<int> M3(2, 4);   // 2x4 matrix
  M3(0, 0) = 5;
  M3(0, 1) = 5;
  M3(0, 2) = 5;
  M3(1, 0) = 5;
  M3(1, 1) = 5;
  M3(1, 2) = 5;
  M3(1, 3) = 5;

  M3 = M1 * M2; // 1x1 matrix with value of 2

  if (M3.size() == 1 && M3(0, 0) == 2) {
    passed++;
  }
  else {
    cout << "multiply_test5() failed" << endl;
    failed++;
  }
}

// Test multiplying with a jagged matrix
bool multiply_test6() {
  try {
    mymatrix<int> M1;
    mymatrix<int> M2;
    M2.growcols(0, 5);
    M2.growcols(1, 6);
    M2.growcols(2, 7);
    M2.growcols(3, 8);

    mymatrix<int> M3 = M1 * M2;   // Matrices are not compatible

    cout << "multiply_test6() failed: expected throw exception" << endl;
    failed++;
  }
  catch(...) {
    passed++;
  }
}

// Test that changing matrix factor values won't change the product matrix
bool multiply_test7() {
  mymatrix<int> M1(2, 2);
  mymatrix<int> M2(2, 2);
  mymatrix<int> M3 = M1 * M2; // 2x2 matrix

  M1(0, 0) = -1;
  M2(0, 0) = -1;

  if (M3(0, 0) == 0 && M3(0, 1) == 0 && M3(1, 0) == 0 && M3(1, 1) == 0) {
    passed++;
  }
  else {
    cout << "multiply_test7() failed" << endl;
    failed++;
  }
}

// Test multiplication stored into one of the factor matrices
bool multiply_test8() {
  mymatrix<int> M1(1, 2); // 1x2 matrix
  mymatrix<int> M2(2, 1);

  M1(0, 0) = -1;
  M1(0, 1) = -1;

  M2(0, 0) = 5;
  M2(1, 0) = 5;

  M1 = M1 * M2; // 1x1 matrix

  if (M1.size() == 1 && M1(0, 0) == -10) {
    passed++;
  }
  else {
    cout << "multiply_test8() failed" << endl;
    failed++;
  }
}

// -----------------------------------------------------------------------------------------
int main()
{
  // at() tests
  at_test1();
  at_test2();
  at_test3();
  at_test4();
  at_test5();
  at_test6();
  at_test7();

  // () operator tests
  parentheses_test1();
  parentheses_test2();
  parentheses_test3();
  parentheses_test4();
  parentheses_test5();
  parentheses_test6();
  parentheses_test7();

  // size() tests
  size_test1();
  size_test2();
  size_test3();
  size_test4();
  size_test5();
  size_test6();
  size_test7();
  size_test8();
  size_test9();

  // numrows() tests
  numrows_test1();
  numrows_test2();
  numrows_test3();
  numrows_test4();

  // numcols() tests
  numcols_test1();
  numcols_test2();
  numcols_test3();
  numcols_test4();
  numcols_test5();
  numcols_test6();

  // Default constructor tests
  default_constructor_test1();
  default_constructor_test2();

  // Parameterized constructor tests
  param_constructor_test1();
  param_constructor_test2();
  param_constructor_test3();

  // Copy constructor tests
  copy_constructor_test1();
  copy_constructor_test2();
  copy_constructor_test3();
  copy_constructor_test4();
  copy_constructor_test5();

  // growcols() tests
  growcols_test1();
  growcols_test2();
  growcols_test3();
  growcols_test4();
  growcols_test5();
  growcols_test6();
  growcols_test7();
  growcols_test8();
  growcols_test9();

  // grow() tests
  grow_test1();
  grow_test2();
  grow_test3();
  grow_test4();
  grow_test5();
  grow_test6();
  grow_test7();
  grow_test8();
  grow_test9();
  grow_test10();
  grow_test11();

  // scalar multiplication tests
  scalar_test1();
  scalar_test2();
  scalar_test3();
  scalar_test4();
  scalar_test5();
  scalar_test6();
  scalar_test7();
  scalar_test8();

  // matrix multiplication tests
  multiply_test1();
  multiply_test2();
  multiply_test3();
  multiply_test4();
  multiply_test5();
  multiply_test6();
  multiply_test7();
  multiply_test8();

  cout << endl;
  cout << "Tests passed: " << passed << endl;
  cout << "Tests failed: " << failed << endl;
  return 0;
}