#include<iostream>

using namespace std;

int main(int argc, char *argv[])
{
  int num = -1, counter_two = 0, counter_three = 0;
  bool divisibility = false;

  cout<<"Enter a positive integer:"<<endl;
  cin>>num;

  while(num != 1)
  {
    if(num%2 == 0)
    {
      counter_two += 1;
      num /= 2;
    }
    else if(num%3 == 0)
    {
      counter_three += 1;
      num /= 3;
    }
    else
    {
      divisibility = true;
      num = 1;
    }
  }
  
  if(divisibility)
  {
    cout<<"No"<<endl;
  }
  else
  {
    cout<<"Yes"<<endl;
    cout<<"Twos="<<counter_two<<" "<<"Threes="<<counter_three<<endl;
  }
  
  return 0;
}