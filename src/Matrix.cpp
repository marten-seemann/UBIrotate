#define MATHEMATICA 0 /** <output the matrix in Mathematica format? */
#include "Matrix.h"

using namespace std;



Matrix::Matrix(const int size) {
  this->size=size;
  data.resize(size*size);
  for(int i=0;i<size*size;i++) {
    data.at(i)=0;
  }
}

int Matrix::getSize() const {
  return size;
}

// returns the value of matrix element M_ij
double Matrix::getValue(const int i, const int j) const {
  return data.at(i*size+j);
}

// set the value of matrix element M_ij
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

// print the Matrix. Either human-readable or in Mathematica format
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
  size=a.size;
  data=a.data;
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