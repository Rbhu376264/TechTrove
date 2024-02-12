#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "course.h"
using namespace std;

//Complete this header file below

class PassFailCourse:public Course
{
  public:
    PassFailCourse(string name_2,int credit_2, double threshold_2);
    string getFinalLetterGrade(double grade);
  protected:
    double threshold;  
};
