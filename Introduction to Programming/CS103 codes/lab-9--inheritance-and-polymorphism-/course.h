#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Complete this header file below
class Course
{
  public:
    Course(string name_1, int credit_1);
    string getName();
    int getNumCredit();
    virtual string getFinalLetterGrade(double grade) = 0;
  protected:
    int credit;
    string name;  
};

