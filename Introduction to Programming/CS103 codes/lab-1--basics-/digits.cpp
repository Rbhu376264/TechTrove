#include<iostream>

using namespace std;

int main(int argc, char *argv[])
{
  int num, ones_digit, tens_digit, hundred_digit;

  cout<<"Enter an integer between 0 and 999: ";
  cin>>num;

  ones_digit = num%10;
  tens_digit = (num/10)%10;
  hundred_digit = num/100;

  cout<<"1's digit is "<<ones_digit<<endl;
  cout<<"10's digit is "<<tens_digit<<endl;
  cout<<"100's digit is "<<hundred_digit<<endl;

  return 0;


}