#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "student.h"

using namespace std;


Student::Student(string name){
  //You complete
  
  this->name = name;
  
}


void Student::setMajor(string major){
  //You complete
  
  
  this->major = major;
  
  
  
}

//Add course to the _courses vector
//Add course_grade to the _grades vector
void Student::addCourse(Course* course,double course_grade){
  //You complete
  

  _courses.push_back(course);
  _grades.push_back(course_grade);


  
}

//Compute the overall GPA
double Student::getTotalGPA(){
  //you complete
 double sum = 0.0;
 double num_credit = 0.0; 
  for(size_t i = 0; i < _courses.size(); i++)
  {
    if(_courses[i]->getFinalLetterGrade(_grades[i])  != "P" && _courses[i]->getFinalLetterGrade(_grades[i])  != "NP")
    {
      if(_courses[i]->getFinalLetterGrade(_grades[i])  == "A")
      {
        sum += 4.0*(_courses[i]->getNumCredit());
        num_credit += _courses[i]->getNumCredit();
      }
      else if(_courses[i]->getFinalLetterGrade(_grades[i])  == "B")
      {
        sum += 3.0*(_courses[i]->getNumCredit());
        num_credit += _courses[i]->getNumCredit();
      }
      else if(_courses[i]->getFinalLetterGrade(_grades[i])  == "C")
      {
        sum += 2.0*(_courses[i]->getNumCredit());
        num_credit += _courses[i]->getNumCredit();
      }
      else if(_courses[i]->getFinalLetterGrade(_grades[i])  == "D")
      {
        sum += 1.0*(_courses[i]->getNumCredit());
        num_credit += _courses[i]->getNumCredit();
      }
      else if(_courses[i]->getFinalLetterGrade(_grades[i])  == "F")
      {
        num_credit += _courses[i]->getNumCredit();
      }
    }
    
  }
  
  
  
  
  return sum/num_credit; //to be changed.
}

//Get the total course credits.
int Student::getSemesterCourseCredit(){
  //you complete
  int total_credit = 0;

  for(size_t i = 0; i < _courses.size(); i++)
  {
    if(_courses[i]->getFinalLetterGrade(_grades[i])  != "NP")
    {
      total_credit += _courses[i]->getNumCredit();
    }
  }
  
  
  
  
  
  
  return total_credit; //to be changed.
}


//***********************
//This function is done. 
//do Not change anything
//***********************
void Student::printReport(){
  cout<<"\033[1;36m"<<"Name: "<<"\033[0m"<<name<<endl;
  cout<<"\033[1;36m"<<"Major: "<<"\033[0m"<<major<<endl;
  cout<<"\033[1;36m"<<"Courses Taken: "<<"\033[0m"<<endl;
  cout << '|' << setw(10) <<"Course";
  cout << '|' << setw(10) <<"Credit";
  cout << '|' << setw(10) <<"RawGrade";
  cout << '|' << setw(12) <<"LetterGrade";
  cout <<endl;
  cout << '|' << setw(10) <<"----------";
  cout << '|' << setw(10) <<"----------";
  cout << '|' << setw(10) <<"----------";
  cout << '|' << setw(12) <<"------------";
  cout <<endl;
  for(size_t i = 0; i < _courses.size(); i++){
    cout << '|' << setw(10) << _courses[i]->getName();
    cout << '|' << setw(10) << _courses[i]->getNumCredit();
    cout << '|' << setw(10) << _grades[i];
    cout << '|' << setw(12) << _courses[i]->getFinalLetterGrade(_grades[i]);
    cout << endl;
  }
  cout << '|' << setw(10) <<"----------";
  cout << '|' << setw(10) <<"----------";
  cout << '|' << setw(10) <<"----------";
  cout << '|' << setw(12) <<"------------";
  cout <<endl;
  cout<<"\033[1;36m"<<"Total Credits: "<<"\033[0m"<<getSemesterCourseCredit()<<endl;
  cout<<"\033[1;36m"<<"Overall GPA: "<<"\033[0m"<< setprecision(2) << std::fixed << getTotalGPA()<<endl;
}