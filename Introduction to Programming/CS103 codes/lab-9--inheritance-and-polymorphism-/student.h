#include <iostream>
#include <string>
#include <vector>
#include "course.h"

using namespace std;


//==================================================
//This file is complete, do NOT add/remove anything in this file.
//==================================================

class Student{
  public:
    Student(string name);
    void setMajor(string major);
    void addCourse(Course* course, double course_grade);
    double getTotalGPA();
    int getSemesterCourseCredit();
    void printReport();//this function is done for you
  private:
    string name;
    string major;
    vector<Course*> _courses;
    vector<double> _grades;
};