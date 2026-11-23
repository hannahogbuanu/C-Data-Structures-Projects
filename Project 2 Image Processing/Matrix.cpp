#include <cassert>
#include "Matrix.hpp"
#include <vector>
#include <iostream>
using namespace std;

// REQUIRES: mat points to a Matrix
//           0 < width && 0 < height
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height,
//           with all elements initialized to 0.
void Matrix_init(Matrix* mat, int width, int height) {
  mat->width = width;
  mat->height = height;
  mat->data.assign(width * height, 0);
  //vector<vector<int>> Matrix(width, vector<int>(height, 0));
   // TODO Replace with your implementation!
}

 
// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
  os << mat->width << " " << mat->height << endl;
  for (int row = 0; row < mat->height; ++row){
    for (int col = 0; col < mat->width; ++ col){
      os << mat->data[row * mat->width + col] << " ";
    }
    os << endl;
  }

   // TODO Replace with your implementation!
}


// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
  return mat->width;
   // TODO Replace with your implementation!
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
  return mat->height; // TODO Replace with your implementation!
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
  return 
  &(mat->data[row * mat->width + column]); 
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
// 
}         
const int* Matrix_at(const Matrix* mat, int row, int column) {

  return &(mat->data[row * mat->width + column]);
   // TODO Replace with your implementation!
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {

  int *end = mat->data.data() + mat->width * mat->height;

  for (int* ptr = mat->data.data(); ptr < end; ++ptr) {
    *ptr = value;
  }
  
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the 
              //first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {
  
  for (int row = 0; row < mat->height; ++row){
    if ((row == 0) | (row == mat->height - 1)){
      for (int col = 0; col < mat->width; ++ col){
        mat->data[row * mat->width + col] = value;
      }
    }
  }
  for (int col = 0; col < mat->width; ++col){
    if ((col == 0) | (col == mat->width - 1)){
      for (int row = 0; row < mat->height; ++ row){
        mat->data[row * mat->width + col] = value;
      }
    }
  }

   // TODO Replace with your implementation!
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
  int maximum = mat->data[0];
  for (int r = 0; r < mat->height; ++r){
    for(int c = 0; c < mat->width; ++c){
      if (maximum < (mat->data[r * mat->width + c])) {
        maximum = (mat->data[r * mat->width + c]);
      }
      else {
        maximum = maximum;
      }
    }
  }
  return maximum; 
   // TODO Replace with your implementation!
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end) {
  
  int minimum = *Matrix_at(mat, row, column_start);    
  int c = column_start;  
  int mcol = c;


  for(; c < column_end; ++c){
    if (minimum > (*Matrix_at(mat,row,c))) {
      minimum = (*Matrix_at(mat, row, c));
      mcol = c;

    }

  }
  
  return mcol;
  //return maximum;
   //run through matrix if minimum = minimum. colnumber = colnumber
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {
  
  int minimum = *Matrix_at(mat, row, column_start);
  int c = column_start;

  for(; c < column_end; ++c){
    if (minimum > (*Matrix_at(mat,row,c))) {
      minimum = (*Matrix_at(mat, row, c));
    }

  }
  
  return minimum;
   // TODO Replace with your implementation!
}
