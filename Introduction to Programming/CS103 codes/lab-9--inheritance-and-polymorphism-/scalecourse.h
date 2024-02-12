#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "course.h"
using namespace std;


//Complete this header file below
class ScaleCourse:public Course
{
  public:
    ScaleCourse(string name_, int credit_, vector<double> scales_);
    string getFinalLetterGrade(double grade);
  protected:
    vector<double>scales;
};
