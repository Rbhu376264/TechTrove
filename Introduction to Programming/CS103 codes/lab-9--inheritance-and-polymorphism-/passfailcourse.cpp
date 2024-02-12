#include <iostream>
#include <string>
#include <vector>
#include "passfailcourse.h"

using namespace std;

//You complete the cpp file below

PassFailCourse::PassFailCourse(string name_2,int credit_2, double threshold_2):Course(name_2,credit_2)
{
  // name = name_2;
  // credit = credit_2;
  threshold = threshold_2;
}
string PassFailCourse::getFinalLetterGrade(double grade)
{
  if(grade>=threshold)
  {
    return "P";
  }
  else{
    return "NP";
  }
}