#include <iostream>
#include <string>
#include <vector>
#include "course.h"
#include "scalecourse.h"
#include "passfailcourse.h"
#include "student.h"

using namespace std;

//******************************************
//this file is complete, please don't change anything
//******************************************

int main(int argc, char *argv[]){
  //should produce an error since "Course" is an abstract base class.
  //we can't declare/instantiate this class.
  Course test("CS103L",4);
  return 0;
}
