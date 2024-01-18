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

#pragma once
#include <iostream>
#include <exception>
#include <stdexcept>
using namespace std;

template<typename T>
class mymatrix {
private:
  struct ROW {
    T*  Cols;     // dynamic array of column elements
    int NumCols;  // total # of columns (0..NumCols-1)
  };

  ROW* Rows;     // dynamic array of ROWs
  int  NumRows;  // total # of rows (0..NumRows-1)

public:
  //
  // default constructor:
  //
  // Called automatically by C++ to construct a  4x4 matrix.  All 
  // elements are initialized to the default value of T.
  //
  mymatrix()
  {
    Rows = new ROW[4];  // an array with 4 ROW structs:
    NumRows = 4;

    // initialize each row to have 4 columns:
    for (int r = 0; r < NumRows; ++r)
    {
      Rows[r].Cols = new T[4];  // an array with 4 elements of type T:
      Rows[r].NumCols = 4;

      // initialize the elements to their default value:
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        Rows[r].Cols[c] = T{};  // default value for type T:
      }
    }
  }
  //
  // parameterized constructor:
  //
  // Called automatically by C++ to construct a matrix with R rows, 
  // where each row has C columns. All elements are initialized to 
  // the default value of T.
  //
  mymatrix(int R, int C)
  {
    if (R < 1)
      throw invalid_argument("mymatrix::constructor: # of rows");
    if (C < 1)
      throw invalid_argument("mymatrix::constructor: # of cols");

    Rows = new ROW[R];  // an array with R ROW structs:
    NumRows = R;

    // initialize each row to have 4 columns:
    for (int r = 0; r < NumRows; ++r) {
      Rows[r].Cols = new T[C];  // an array with C elements of type T
      Rows[r].NumCols = C;

      // initialize the elements to their default value:
      for (int c = 0; c < Rows[r].NumCols; ++c) {
        Rows[r].Cols[c] = T{};  // default value for type T
      }
    }
  }


  //
  // copy constructor:
  //
  // Called automatically by C++ to construct a matrix that contains a 
  // copy of an existing matrix.  Example: this occurs when passing 
  // mymatrix as a parameter by value
  //
  //   void somefunction(mymatrix<int> M2)  <--- M2 is a copy:
  //   { ... }
  //
  mymatrix(const mymatrix<T>& other)
  {      
    Rows = new ROW[other.NumRows];   // Allocate new memory address
    NumRows = other.NumRows;         

    // Make new cols and copy array data
    for (int r = 0; r < NumRows; r++) {
      Rows[r].NumCols = other.Rows[r].NumCols;  
      Rows[r].Cols = new T[Rows[r].NumCols];  // Make new Cols for that row

      // Copy each value 
      for (int c = 0; c < Rows[r].NumCols; c++) {
        Rows[r].Cols[c] = other.Rows[r].Cols[c];
      }      
    }
  }


  //
  // numrows
  //
  // Returns the # of rows in the matrix.  The indices for these rows
  // are 0..numrows-1.
  //
  int numrows() const
  {
    return NumRows;
  }
  

  //
  // numcols
  //
  // Returns the # of columns in row r.  The indices for these columns
  // are 0..numcols-1.  Note that the # of columns can be different 
  // row-by-row since "jagged" rows are supported --- matrices are not
  // necessarily rectangular.
  //
  int numcols(int r) const
  {
    if (r < 0 || r >= NumRows)  // Out of bounds
      throw invalid_argument("mymatrix::numcols: row");

    return Rows[r].NumCols;
  }


  //
  // growcols
  //
  // Grows the # of columns in row r to at least C.  If row r contains 
  // fewer than C columns, then columns are added; the existing elements
  // are retained and new locations are initialized to the default value 
  // for T.  If row r has C or more columns, then all existing columns
  // are retained -- we never reduce the # of columns.
  //
  // Jagged rows are supported, i.e. different rows may have different
  // column capacities -- matrices are not necessarily rectangular.
  //
  void growcols(int r, int C)
  {
    // Out of bounds
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::growcols: row");
    if (C < 1)
      throw invalid_argument("mymatrix::growcols: columns");

    // We only change the size if there is less than C columns
    if (Rows[r].NumCols < C) {
      T* temp = new T[C];      // Allocate a new array with more space

      // Copy all the values from Cols to temp
      int c = 0;
      while (c < Rows[r].NumCols) {  
        temp[c] = Rows[r].Cols[c];
        c++;
      }
      
      // Initialize the new empty spaces
      while (c < C) {    
        temp[c] = T{};
        c++;
      }

      delete Rows[r].Cols;    // Delete the old Cols
      Rows[r].Cols = temp;    // Update Cols 
      Rows[r].NumCols = C;    // Update NumCols
    }
  }


  //
  // grow
  //
  // Grows the size of the matrix so that it contains at least R rows,
  // and every row contains at least C columns.
  // 
  // If the matrix contains fewer than R rows, then rows are added
  // to the matrix; each new row will have C columns initialized to 
  // the default value of T.  If R <= numrows(), then all existing
  // rows are retained -- we never reduce the # of rows.
  //
  // If any row contains fewer than C columns, then columns are added
  // to increase the # of columns to C; existing values are retained
  // and additional columns are initialized to the default value of T.
  // If C <= numcols(r) for any row r, then all existing columns are
  // retained -- we never reduce the # of columns.
  
  void grow(int R, int C)
  {
    // Out of bounds
    if (R < 1)
      throw invalid_argument("mymatrix::grow: # of rows");
    if (C < 1)
      throw invalid_argument("mymatrix::grow: # of cols");

    // Grow existing columns
    for (int r = 0; r < NumRows; r++) {
      growcols(r, C);
    }

    // Grow rows if there are not enough
    if (NumRows < R) {
      ROW* temp = new ROW[R];

      // Update and copy over the existing Cols values 
      int r = 0;
      while (r < NumRows) {
        temp[r].Cols = new T[Rows[r].NumCols];  // Cols already been grown. Use that size just in case NumCols > C

        // Copy existing values over
        for (int c = 0; c < Rows[r].NumCols; c++) {
          temp[r].Cols[c] = Rows[r].Cols[c];
        }

        temp[r].NumCols = Rows[r].NumCols;    // Update NumCols for this row
        r++;
      }

      // Create and initialize values for the new rows/cols
      while (r < R) {
        temp[r].Cols = new T[C];

        for (int c = 0; c < C; c++) {
          temp[r].Cols[c] = T{};  // Set to default value
        }

        temp[r].NumCols = C;
        r++;
      }

      delete Rows;
      Rows = temp;
      NumRows = R;
    }
  }


  //
  // size
  //
  // Returns the total # of elements in the matrix.
  //
  int size() const
  {
    int numElements = 0;

    for (int r = 0; r < NumRows; ++r) {
      numElements += Rows[r].NumCols;
    }

    return numElements;
  }


  //
  // at
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M.at(r, c) = ...
  //    cout << M.at(r, c) << endl;
  //
  T& at(int r, int c) const
  {
    // Out of bounds
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::at: row");
    if (c < 0 || c >= Rows[r].NumCols)
      throw invalid_argument("mymatrix::at: col");

    return Rows[r].Cols[c];
  }


  //
  // ()
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M(r, c) = ...
  //    cout << M(r, c) << endl;
  //
  T& operator()(int r, int c) const
  {
    // Out of bounds
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::(): row");
    if (c < 0 || c >= Rows[r].NumCols)
      throw invalid_argument("mymatrix::(): col");

    return Rows[r].Cols[c];
  }

  //
  // scalar multiplication
  //
  // Multiplies every element of this matrix by the given scalar value,
  // producing a new matrix that is returned.  "This" matrix is not
  // changed.
  //
  // Example:  M2 = M1 * 2;
  //
  mymatrix<T> operator*(T scalar)
  {
    // Copy current matrix values to the matrix we will return
    mymatrix<T> result(*this);
    
    for (int r = 0; r < NumRows; ++r) {
      for (int c = 0; c < Rows[r].NumCols; ++c) {
        result(r, c) = Rows[r].Cols[c] * scalar;  // Set element values
      }
    }

    return result;
  }


  //
  // matrix multiplication
  //
  // Performs matrix multiplication M1 * M2, where M1 is "this" matrix and
  // M2 is the "other" matrix.  This produces a new matrix, which is returned.
  // "This" matrix is not changed, and neither is the "other" matrix.
  //
  // Example:  M3 = M1 * M2;
  //
  // NOTE: M1 and M2 must be rectangular, if not an exception is thrown.  In
  // addition, the sizes of M1 and M2 must be compatible in the following sense:
  // M1 must be of size RxN and M2 must be of size NxC.  In this case, matrix
  // multiplication can be performed, and the resulting matrix is of size RxC.
  //
  mymatrix<T> operator*(const mymatrix<T>& other)
  {
    // Check if M1 is rectangular
    if (NumRows > 1) {  // Matrix with 1 row is automatically rectangular
      for (int r = 1; r < NumRows; r++) {
        if (Rows[r].NumCols != Rows[r - 1].NumCols) {
          throw invalid_argument("mymatrix::*: mymatrix not rectangular");
        }
      }
    }

    // Check if M2 is rectangular
    if (other.NumRows > 1) {  // Matrix with 1 row is automatically rectangular
      for (int r = 1; r < other.NumRows; r++) {
        if (other.Rows[r].NumCols != other.Rows[r - 1].NumCols) {
          throw invalid_argument("mymatrix::*: other matrix not rectangular");
        }
      }
    }

    // Check if M1 and M2 are compatible
    for (int r = 0; r < NumRows; r++) {
      if (Rows[r].NumCols != other.NumRows) {
        throw invalid_argument("mymatrix::*: matrixes not compatible");
      }
    }
   
    // Given RxN and NxC, RxC gives the new matrix's size
    // The order will me M1 (this) * M2 (other), so new matrix's will have M1's numrows and M2's numcols
    int OtherCols = other.Rows[0].NumCols;
    mymatrix<T> result(NumRows, OtherCols);   // All other rows have the same # cols

    // Multiply matrices values and add it to result matrix
    for (int r = 0; r < NumRows; ++r) {
      for (int c = 0; c < OtherCols; ++c) {
        for (int i = 0; i < Rows[r].NumCols; ++i) {
          result.Rows[r].Cols[c] += Rows[r].Cols[i] * other.Rows[i].Cols[c];
        }
      }
    }
    
    return result;
  }


  //
  // _output
  //
  // Outputs the contents of the matrix; for debugging purposes.
  //
  void _output()
  {
    for (int r = 0; r < this->NumRows; ++r)
    {
      for (int c = 0; c < this->Rows[r].NumCols; ++c)
      {
        cout << this->Rows[r].Cols[c] << " ";
      }
      cout << endl;
    }
  }

};