#define _USE_MATH_DEFINES
#define DEBUG 0


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
  
  if(vm.count("version")) {
    cout << "UBIrotate, version 0.1.0" << endl;    
    exit(1);
  }
  
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
  if(DEBUG) cout << "Axis: " << axis << ", angle: " << angle << endl;
  

  // read the UBI matrix from the given file
  ifstream file;
  file.open(filename.c_str(),ios::in);
  if(!file.is_open()) {
    cerr << "UBI file " << filename << " could not be opened." << endl;
    exit(1);
  }
  
  // read the original UBI from the given file
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
  
  if(DEBUG) {
    cout << "Original UBI" << endl;
    ubi_orig.print();
  }
  
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
  if(DEBUG) {
    cout << "Rotation matrix" << endl;
    rot.print();
  }

  
  Matrix ubi_new=(rot*ubi_orig.getTranspose()).getTranspose();
  if(DEBUG) {
    cout << "This is the new UBI:" << endl;
    ubi_new.print();
  }
  
  // save the matrix to a file
  string output_filename=filename+".rot";
  ofstream myfile;
  myfile.open (output_filename.c_str());
  for(int i=0;i<3;i++) {
    for(int j=0;j<3;j++) {
      myfile << ubi_new.getValue(i,j);
      myfile << " ";
    }
    myfile << endl;
  }
  myfile.close();
  
  return 0;
}
