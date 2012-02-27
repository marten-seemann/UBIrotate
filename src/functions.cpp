
//
//  functions.cpp
//  UBIrotate
//
//  Created by Marten Seemann on 05.02.12.
//  Copyright (c) 2012 ---. All rights reserved.
//

#include "functions.h"

string& trim(string &str)
{
  int i,j,start,end;
  
  //ltrim
  for (i=0; (str[i]!=0 && str[i]<=32); ) i++;
  start=i;
  
  //rtrim
  for(i=0,j=0; str[i]!=0; i++) j = ((str[i]<=32)? j+1 : 0);
  end=i-j;
  str = str.substr(start,end-start);
  return str;
};