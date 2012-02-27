//
//  main.cpp
//  UBIrotate
//
//  Created by Marten Seemann on 05.02.12.
//  Copyright (c) 2012 ---. All rights reserved.
//
#define _USE_MATH_DEFINES 


#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include "Matrix.h"
#include "functions.h"
#include <boost/program_options.hpp>

namespace po = boost::program_options;
using namespace std;

int main (int argc, const char * argv[])
{
  po::options_description cmdline_options;
  po::options_description generic("Generic options");
  generic.add_options()
  ("help", "produce this help message")
  ("version", "show version information")
  ;
  
  po::options_description rotate("Rotate a given UBI matrix");
  rotate.add_options()
  ("axis", po::value< string >(), "the UBI-axis to rotate about, possible values: x, y, z")
  ("angle", po::value< double >(), "size of the angle of rotation, in degrees")
  ("file", po::value< string >(), "the file containing the UBI matrix")
  ;
  
  cmdline_options.add(generic);
  cmdline_options.add(rotate);
  
  po::variables_map vm;
  po::positional_options_description p;
  
  po::store(po::parse_command_line(argc, argv, cmdline_options), vm);
  po::notify(vm);  
  
  // non-valid command line options (or help) => show usage
  if (vm.size()==0 || vm.count("help") || !(vm.count("axis") && vm.count("angle") && vm.count("file"))) {
    cout << cmdline_options << "\n";
    exit(1);
  }
  
  //read the 3 necessary values
  string axis=vm["axis"].as<string>();
  int dir_index;
  if(axis=="x") dir_index=0;
  else if(axis=="y") dir_index=1;
  else if(axis=="z") dir_index=2;
  else {
    cerr << "Invalid axis to rotate about.";
    cout << cmdline_options << "\n";
    exit(1);
  }
  double angle=vm["angle"].as<double>();
  string filename=vm["file"].as<string>();
  cout << axis << " " << angle << endl;
  

  // read the UBI matrix from the given file
  ifstream file;
  file.open(filename.c_str(),ios::in);
  if(!file.is_open()) {
    cerr << "UBI file " << filename << " could not be opened." << endl;
    exit(1);
  }
  
  string line, a, b ,c;
  Matrix ubi_orig(3);
  int counter=0;
  while(file.good()) {
    getline(file,line);
    line=trim(line);
    if(line.length()==0) continue;
    if(line.substr(0,1)=="#") continue;
    istringstream line_stream(line);
    line_stream >> a >> b >> c;
    ubi_orig.setValue(counter,0,atof(a.c_str()));
    ubi_orig.setValue(counter,1,atof(b.c_str()));
    ubi_orig.setValue(counter,2,atof(c.c_str()));
    counter++;
  }
  cout << "Original UBI" << endl;
  ubi_orig.print();
  
  // calc the normalized vector n to rotate about
  vector<double> n(3);
  double n_length=0;
  for(int i=0;i<3;i++) {
    n.at(i)=ubi_orig.getValue(dir_index,i);
    n_length+=n.at(i)*n.at(i);  
  }
  n_length=sqrt(n_length);
  for(int i=0;i<3;i++) n.at(i)/=n_length;
  
  angle*=M_PI/180;
  
  Matrix rot(3);
  rot.setValue(0,0,cos(angle)+n.at(0)*n.at(0)*(1-cos(angle)));
  rot.setValue(0,1,n.at(0)*n.at(1)*(1-cos(angle))-n.at(2)*sin(angle));
  rot.setValue(0,2,n.at(0)*n.at(2)*(1-cos(angle))+n.at(1)*sin(angle));
  rot.setValue(1,0,n.at(1)*n.at(0)*(1-cos(angle))+n.at(2)*sin(angle));
  rot.setValue(1,1,cos(angle)+n.at(1)*n.at(1)*(1-cos(angle)));
  rot.setValue(1,2,n.at(1)*n.at(2)*(1-cos(angle))-n.at(0)*sin(angle));
  rot.setValue(2,0,n.at(2)*n.at(0)*(1-cos(angle))-n.at(1)*sin(angle));
  rot.setValue(2,1,n.at(2)*n.at(1)*(1-cos(angle))+n.at(0)*sin(angle));
  rot.setValue(2,2,cos(angle)+n.at(2)*n.at(2)*(1-cos(angle)));
  cout << "Rotation matrix" << endl;
  rot.print();

  
  Matrix ubi_new=(rot*ubi_orig.getTranspose()).getTranspose();
  ubi_new.print();
  

  
  
  
  
  /*
  Matrix a(3);
  Matrix b(3);
  int counter=1;
  for(int i=0;i<3;i++) {
    for(int j=0;j<3;j++) {
      a.setValue(i,j,counter);
      b.setValue(i,j,10-counter);
      counter++;
    }
  }
  
  Matrix d=a*b;
  d.print();
}
*/
  
  return 0;
}

