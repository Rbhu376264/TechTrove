#include "bigint.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

BigInt::BigInt(string s)
{
  for(int i = s.size()-1; i>=0; i--)
  {
    int temp = ((int)s[i])-48;
    numbers.push_back(temp);
  }
}
BigInt::BigInt(string s, int base)
{
  B = base;
  
  
  for(int i = s.size()-1; i>=0; i--)
  {
    
    int temp = ((int)s[i]);
    if(temp<=57)
    {
      numbers.push_back(temp-48);
    }
    else
    {
      numbers.push_back(temp-55);
    }

    
  }
  
}

string BigInt::to_string()
{
  string temp = "";

  

  for(int i = numbers.size()-1; i>=0; i--)
  {

    if(numbers[i]<=9)
    {
      temp += (char)(numbers[i]+48);
    }
    else{

      temp += (char)(numbers[i]+55);
    }
    
  }

  return temp;
}

void BigInt::add(BigInt b)
{

  int summation = 0;
  int carry_forward = 0;

  //cout<<numbers.base<<endl;

  if(B != b.B)
  {
    throw runtime_error("The two numbers don't have same base!");
  }
  else
  {
    if(numbers.size()!=b.numbers.size())
    {
      while(numbers.size()!=b.numbers.size())
      {
        if(numbers.size()>b.numbers.size())
        {
          b.numbers.push_back(0);
        }
        else if(numbers.size()<b.numbers.size())
        {
          numbers.push_back(0);
        }
      }
    }

    for(unsigned int i = 0; i<numbers.size(); i++)
    {
      summation = b.numbers[i]+numbers[i]+carry_forward;
      
      carry_forward = summation/B;

      numbers[i] = summation%B;
    }

    if(carry_forward>0)
    {
      numbers.push_back(carry_forward);
    }

  }



}