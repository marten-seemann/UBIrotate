#ifndef UBIrotate_Matrix_h
#define UBIrotate_Matrix_h

#include <iostream>
#include <vector>
#include "functions.h"


class Matrix {
  int size;
  std::vector<double> data;
  double* test;
  
public:
  Matrix(const int size);
  int getSize() const;
  void setValue(const int i, const int j, const double value);
  double getValue(const int i, const int j) const;
  Matrix& getTranspose() const;
  void print() const;
  
  // overloaded operators
  Matrix(const Matrix&);

  Matrix& operator=(Matrix& a);
  friend Matrix operator*(const Matrix& a, const Matrix& b);

};

#endif
