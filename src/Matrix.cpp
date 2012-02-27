//
//  Matrix.cpp
//  UBIrotate
//
//  Created by Marten Seemann on 05.02.12.
//  Copyright (c) 2012 ---. All rights reserved.
//

#define MATHEMATICA 1
#include "Matrix.h"

using namespace std;

Matrix::Matrix(const int size) {
  this->size=size;
  data.resize(size*size);
  test=new double(1.01);
}

int Matrix::getSize() const {
  return size;
}

double Matrix::getValue(const int i, const int j) const {
  return data.at(i*size+j);
}

void Matrix::setValue(const int i, const int j, const double value) {
  data.at(i*size+j)=value;
};

Matrix& Matrix::getTranspose() const {
  Matrix *tmp=new Matrix(3);
  for(int i=0;i<3;i++) {
    for(int j=0;j<3;j++) {
      tmp->setValue(j,i,getValue(i,j));
    }
  }
  return *tmp;
};

void Matrix::print() const {
  if(MATHEMATICA) cout << "{ ";
  for(int i=0;i<size;i++) {
    if(MATHEMATICA) cout << "{ ";
    for(int j=0;j<size;j++) {
      printf("%14.10f ",getValue(i,j));
      if(MATHEMATICA && j<size-1) printf(",");
    }
    if(MATHEMATICA) cout << " }";
    else cout << endl;
    if(MATHEMATICA && i<size-1) printf(",\n");
    
  }
  if(MATHEMATICA) cout << " }" << endl;
  else cout << endl;
};

Matrix& Matrix::operator=(Matrix& a) {
  if(this==&a) return *this;
  else {
    size=a.size;
    data=a.data;
    return *this;
  }
};

Matrix::Matrix(const Matrix& a) {
  cout << "Copy" << endl;
  size=a.size;
  data=a.data;
  test=new double(*(a.test));
}


Matrix operator*(const Matrix& a, const Matrix& b) {
  if(a.getSize()!=b.getSize()) abort();
  int size=a.getSize();
    
  Matrix tmp(size);
  for(int i=0;i<size;i++) {
    for(int j=0;j<size;j++) {
      double value=0;
      for(int k=0;k<size;k++) {
        value+=a.getValue(i,k)*b.getValue(k,j);
      }
      tmp.setValue(i, j, value);
    }
  }
  return tmp;
};