//Name:- Rbhu Gandhi
//Email id:- rbhugand@usc.edu

#include<iostream>
#include<cstdlib>
#include <ctime>
using namespace std;

int roll()
{
  return rand()%6 + 1;
}

char cross(int number)
{
  for(int i = 0; i<number; i++)
  {
    cout<<'X';
  }
  return 1;
}

int main()
{
  srand(time(0));

  int testCounts[21], number, sum = 0;

  cout<<"Enter a number: ";
  cin>>number;

  for(int i = 0; i<21; i++)
  {
    testCounts[i] = 0;
  }

  for(int i = 0; i < number; i++)
  {
    sum = roll() + roll() + roll() + roll();
    testCounts[sum-4]++;
    sum = 0;
  }

  for(int i = 0; i<21; i++)
  {
    cout<<i+4<<':'<<cross(testCounts[i])<<endl;
  }


  return 0;
  
}

