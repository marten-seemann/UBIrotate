#ifndef UBIrotate_Matrix_h
#define UBIrotate_Matrix_h

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "functions.h"

/** Matrix is a class that handles square matrices of type double and allows some of the basic operations
 *  
 *  Note that only few basic operations are implemented (matrix multiplication and the transposition of the matrix.
 */
class Matrix {
  /// the size of the matrix. matrix will be a @a size x @a size matrix
  int size;
  /// vector containing all matrix elements. size of this vector will be @a size x @a size
  std::vector<double> data;
  
public:
  /** Constructor
  *
  * Creates a new square matrix. All matrix elements are initialized with the value 0.0
  * @param size the size of the matrix. Creates a @a size x @a size matrix
  */
  Matrix(const int size);
  /// returns the size of the matrix. If you have a size x size matrix, the value of size will be returned
  /// @return the size of the matrix
  int getSize() const;
  /// sets the value of a matrix element
  /// @param i row of the matrix
  /// @param j column of the matrix
  /// @param value the value that the matrix element i,j should have
  void setValue(const int i, const int j, const double value);
  /// get the value of matrix element i,j
  /// @return the value of the matrix element i,j
  double getValue(const int i, const int j) const;
  /// get the transpose of the matrix
  /// @return a reference to the transposed matrix
  Matrix& getTranspose() const;
  /// output the matrix
  void print() const;
  
  // overloaded operators
  
  Matrix(const Matrix&);

  Matrix& operator=(Matrix& a);
  /// matrix multiplication
  /** computes the matrix product a*b
   * @param a Matrix a
   * @param b Matrix b
   * @return the matrix a*b
   */
  friend Matrix operator*(const Matrix& a, const Matrix& b);

};

#endif