#include <iostream>
#include <string>
#include <vector>
#include "scalecourse.h"

using namespace std;

//You complete the cpp file below
ScaleCourse::ScaleCourse(string name_, int credit_, vector<double> scales_):Course(name_,credit_)
{
  // name = name_;
  // credit = credit_;
  scales = scales_;
}
string ScaleCourse::getFinalLetterGrade(double grade)
{
  if(grade>=scales[0])
  {
    return "A";
  }
  else if(grade>=scales[1])
  {
    return "B";
  }
  else if(grade>=scales[2])
  {
    return "C";
  }
  else if(grade>=scales[3])
  {
    return "D";
  }
  else
  {
    return "F";
  }
}
