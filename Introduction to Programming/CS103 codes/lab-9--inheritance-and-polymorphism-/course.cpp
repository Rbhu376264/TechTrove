#include <iostream>
#include <string>
#include <vector>
#include "course.h"

using namespace std;

//You complete the cpp file below

Course::Course(string name_1, int credit_1)
{
  name = name_1;
  credit = credit_1;
}
string Course::getName()
{
  return name;
}
int Course::getNumCredit()
{
  return credit;
}


