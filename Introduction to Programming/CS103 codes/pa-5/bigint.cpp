#include "bigint.h"
#include <iostream>
#include <string>
#include <climits>
#include <cmath>
using namespace std;

//******************************************************************
//START OF THE CONSTRUCTORS SECTION
//******************************************************************

/*
// Create a default BigInt with base 10.
// This function is complete. You do not have to add anything.
*/
BigInt::BigInt(){
  base = 10;
  isPositive = true;
}

/*
// Create a BigInt with a specified base.
// This function is complete. You do not have to add anything.
*/
BigInt::BigInt(int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    base = setbase;
    isPositive = true;
}

/*
// Destructure. You do not have to add anything.
// This function is complete
*/
BigInt::~BigInt(){}

/*
//  Create a BigInt from string.
//  Don't forget to set the base accordingly
//  The input string will contain
//      - numbers (0-9) and/or 
//      - uppercase letters (A-Z) [A=10, B=11, ... , Z=35]
//  The input string may contain
//      - a negative sign ('-') to signify that the number is negative.
//  Note: char '0' = int 48 (see ASCII table)
//  Note: char 'A' = int 65
*/
BigInt::BigInt(const string &s, int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    /************* You complete *************/
    base = setbase;
    if(s.size()!= 0)
    {
        if(s[0] == '-')
        {
            isPositive = false;
        }
      
      int A = 10;

      for(int i = s.size()-1; i>=0; i--)
      {
          if(s[i] == '-')
          {
              continue;
          }
          else
          {
              if((int)s[i] >=65 && (int)s[i]<=90)
              {
                  vec.push_back(((int)s[i]-(int)'A')+A);
              }
              else if((int)s[i]>=48 && (int)s[i]<=57)
              {
                  vec.push_back((int)s[i]-48);
              }
          }
      }
    }






}


/*
//  Create a BigInt from int (base 10).
//  - Convert the int (base 10) input into a specified base (setbase).
//  - Don't forget to set the base accordingly
//  For example:
//     BigInt k(6,2) <- int 6 base 10 to BigInt base 2
//          - Result:  BigInt k with value 110 (base 2)
//     BigInt k(154,16) <- 154 base 10 to BigInt base 16
//          - Result: BigInt k with value 9A (base 16)
*/
BigInt::BigInt(int input,int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    /************* You complete *************/
    // cout<<"Input: "<<input<<endl;
    
      base = setbase;
      // cout<<"base "<<base<<endl;
      int x = 0, best = 0;
      if(input == 0)
      {
        vec.push_back(0);
      }
      if(input<0)
      {
        best = -1*input;
        // cout<<"best_114 "<<best<<endl;
        isPositive = false;

      }
      else{
        best = input;
        // cout<<"best_120 "<<best<<endl;
      }
      while(best>0)
      {
        x = best%base;
        // cout<<"x "<<x<<endl;
        vec.push_back(x);
        best /= base;
        // cout<<"best_128 "<<best<<endl;

      }
    
    
    // else
    // {
    //   *this = 
    //   base = setbase; 
    // }







}

/*
//  Create a BigInt from another BigInt.
//  This is a copy constructor.
//  Simply call the assignment operator (=) below.
// (You can also think of this function as the same as the assignment operator (=))
// (but without a return statement because you are overriding the current object)
*/
BigInt::BigInt(const BigInt &b){

    /************* You complete *************/
    isPositive = b.isPositive;
    base = b.base;
    vec = b.vec;
    


}

/*
//  Assignment operator. (i.e., BigInt a = b;)
//  OVERRIDING a's data with BigInt b's data
//       - vec
//       - isPositive
//       - base
*/
BigInt & BigInt::operator = (const BigInt &b){

    /************* You complete *************/

    this->base = b.base;
    this->isPositive = b.isPositive;
    this->vec.clear();

    

    for(unsigned int i = 0; i<b.vec.size(); i++)
    {
      this->vec.push_back(b.vec[i]);
    }
    // this->vec[0] = b.vec[0];


    return *this; 
}


//******************************************************************
//END OF THE CONSTRUCTORS SECTION
//******************************************************************

//******************************************************************
//START OF THE DISPLAYS SECTION
//******************************************************************

/*
// Convert to string and return the string
// Display it in its corresponding base
//  Note: char '0' = int 48 (see the ASCII table)
//  Note: char 'A' = int 65
*/
string BigInt::to_string(){

    /************* You complete *************/
    string temp = "";

    for(int i = vec.size()-1; i>=0; i--)
    {
      if(vec[i]<=9)
      {
        temp += (char)(vec[i]+48);
      }
      else
      {
        temp += (char)(vec[i]+55);
        
      }
    }

    if(isPositive == false)
    {
      temp = '-'+temp;
    }
  
  
  
  

  return temp ;//for now
}

/*
//  Convert BigInt to integer base 10 and return that int
//    If BigInt >= INT_MAX, return INT_MAX.
//    If BigInt =< INT_MIN, return INT_MIN.
//  Note: 1. INT_MAX and INT_MIN are already defined for you
//           in the 'climits' library.
//        2. INT_MAX = 2147483647, INT_MIN = -2147483648
//           therefore, INT_MIN does not equal to (-INT_MAX)
*/
int BigInt::to_int() const{

    /************* You complete *************/

    long long int val = 0;

    for(unsigned int i = 0; i<vec.size(); i++)
    {
      val += vec[i]*pow(base,i);
      if(val >= INT_MAX)
      {
        break;
      }
      
    }

    if(this->isPositive == false)
    {
      val = -1*val;

    }
    // cout<<val<<endl;
    if(val >= INT_MAX)
    {
      return INT_MAX;
    }
    else if(val<= INT_MIN)
    {
      return INT_MIN;
    }
  
  
  
  
 
  return val;//for now
}

//******************************************************************
//END OF THE DISPLAYS SECTION
//******************************************************************

//******************************************************************
//START OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

/*
//  Compare a and b.
//     If a = b, return 0.
//     If a < b, return -1.
//     If a > b, return 1.
//  See the HINT below
*/
int BigInt::compare(const BigInt &b) const{
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/

    //HINT:
    //1. do NOT call the to_int() or to_string() function
    //2. do NOT convert bigInt to other datatypes first (e.g., long long, int)
    
    //First let's compare the signs
    //    - if the signs aren't the same,
    //              how do you know which one is larger?

    //If they have the same sign, let's compare their vec sizes 
    //    - what if both are positive, but a's vec is larger (a or b is larger?)
    //    - other cases?
    
    //If they have the same vec size, let's compare their digits one by one
    // Starting from the most-significant digits. --> in what vector position?
    // Remember that the BigInt vectors are in reverse order!
    //    - what if both are positive, but the digit of a is greater than that of b (a or b is larger?)
    //    - other cases?
    
    //If ALL digits are the same, then they MUST be equal!!
    if(this->isPositive != b.isPositive)
    {
      if(this->isPositive == false)
      {
        return -1;
      }
      else{
        return 1;
      }

    }
    else
    {
      if(this->vec.size() != b.vec.size())
      {
        if(this->isPositive == false && b.isPositive == false)
        {
          if(this->vec.size()>b.vec.size())
          {
            return -1;
          }
          else
          {
            return 1;
          }
        }
        else if (this->isPositive == true && b.isPositive == true)
        {
          if(this->vec.size()>b.vec.size())
          {
            return 1;
          }
          else
          {
            return -1;
          }

        }
      }
      else
      {
        
        for(int i = b.vec.size()-1; i>=0; i--)
        {
          if(b.vec[i] != this->vec[i])
          {
            if(b.vec[i]>this->vec[i])
            {
              if(this->isPositive == false && b.isPositive == false)
              {
                return 1;
              }
              else
              {
                return -1;
              }


              
            }
            else
            {
              if(this->isPositive == false && b.isPositive == false)
              {
                return -1;
              }
              else
              {
                return 1;
              }
              
            }
          }
        }

        

      }
    }
    return 0;
}


//Call the compare function above to check if a == b
bool operator == (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
    
  
  
   return a.compare(b) == 0; //for now
}

//Call the compare function above to check if a != b
bool operator != (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
  return a.compare(b) == 1 || a.compare(b) == -1 ;//for now
}

//Call the compare function above to check if a <= b
bool operator <= (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/

  return a.compare(b) == 0 || a.compare(b) == -1;//for now
}

//Call the compare function above to check if a >= b
bool operator >= (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/

  
  
  
  
  return a.compare(b) == 0 || a.compare(b) == 1;//for now
}

//Call the compare function above to check if a > b
bool operator > (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/

  
  
  
  
  return a.compare(b) == 1;//for now
}

//Call the compare function above to check if a < b
bool operator < (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/

  
  
  
  
  return a.compare(b) == -1;//for now
}

//******************************************************************
//END OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

//******************************************************************
//START OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call += operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator + (const  BigInt &a, const BigInt & b){

  /************* You complete *************/
  BigInt temp = a;

  temp += b;


  


  return temp;//for now
}

/*
//==================
// MEMBER function
//==================
//  Addition assignment operator.
//    i.e., a += b
*/
const BigInt & BigInt::operator += (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/
    BigInt zero(0,base);
    if(b.compare(zero) == 0)
    {
      return *this;
    }
    if(this->compare(zero) == 0)
    {
      *this = b;
      return *this;
    }
    if((this->isPositive == false && b.isPositive == true) || (this->isPositive == true && b.isPositive == false))
    {
      BigInt tempA = *this;
      BigInt tempB = b;

      //-a + b = b-a = b - (+a)
      if(this->isPositive == false)
      {
        tempA.isPositive = !tempA.isPositive;
        tempB -= tempA;
        *this = tempB;

        return *this; 
      }

      //a + -b = a - b = a - (+b)
      if(b.isPositive == false)
      {
        tempB.isPositive = !tempB.isPositive;
        tempA -= tempB;
        *this = tempA;

        return *this;
      }
    }
    if((this->isPositive == false && b.isPositive == false) || (this->isPositive == true && b.isPositive == true))
    {


    
      unsigned int size = max(vec.size(),b.vec.size());

      int temp_a, temp_b, carry_forward = 0, sum = 0, delta = 0;

      for(unsigned int i = 0; i<size; i++)
      {
        if(i>=vec.size())
        {
          temp_a = 0;
        }
        else
        {
          temp_a = vec[i];
        }

        if(i>=b.vec.size())
        {
          temp_b = 0;
        }
        else
        {
          temp_b = b.vec[i];
        }

        sum = temp_a + temp_b + carry_forward;

        delta = sum % base;

        carry_forward = sum / base;

        if(i>=vec.size())
        {
          vec.push_back(delta);
        }
        else
        {
          vec[i] = delta;
        }


      }
      if(carry_forward != 0)
      {
        vec.push_back(carry_forward);
      }
    }

    

    

  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call -= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator - (const  BigInt &a, const BigInt & b){

  /************* You complete *************/
  
  BigInt m = a;

  m -= b;
  

  return m;//for now
}


/*
//==================
// MEMBER function
//==================
//  Subtraction assignment operator.
//    i.e., a -= b
//  Note: Think of base cases (e.g., subtract by itself)
*/
const BigInt & BigInt::operator -= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/

    
    BigInt tempA, tempB, differ;

    tempA = *this;
    tempB = b;

    

    bool sign = false;
    //-a - b = - (a+b)
    if(tempA.isPositive == false && tempB.isPositive == true)
      {
        tempA.isPositive = true;
        tempA += tempB;
        tempA.isPositive = false;
        *this = tempA;
        return *this;
      }
      //a - -b = a+b
      if(tempA.isPositive == true && tempB.isPositive == false)
      {
        tempB.isPositive = true;
        tempA += tempB;
        *this = tempA;
        return *this;
      }

      if(this->isPositive == false && b.isPositive == false)
      {
        tempA.isPositive = true;
        tempB.isPositive = true;
      }
    
    
    BigInt zero(0,base);



    if(this->isPositive == false)
    {
      if(this->compare(b) == -1 || this->compare(b) == 0)
      {
        tempA = *this;
        tempB = b;
        sign = false;

        if(this->compare(b) == 0)
        {
          sign = true;
        }
      }
      else
      {
        tempA = b;
        tempB = *this;
        sign = true;
      }
        
      
      
    }
      //-a - b = - (a+b) 
      // if(tempA.isPositive == false && tempB.isPositive == true)
      // {
      //   tempA.isPositive = true;
      //   tempA += tempB;
      //   tempA.isPositive = false;
      //   *this = tempA;
      // }
      // //a - -b = a+b
      // if(tempA.isPositive == true && tempB.isPositive == false)
      // {
      //   tempB.isPositive = true;
      //   tempA += tempB;
      //   *this = tempA;
      // }

      // return *this;
    
    if(this->isPositive == true)
    {
      if(this->compare(b) == 1 || this->compare(b) == 0)
      {
        tempA = *this;
        tempB = b;
        sign = true;
      }
      else
      {
        tempA = b;
        tempB = *this;
        sign = false;
      }
      // this->isPositive = false;

    }
    
    // else
    // {
    //   *this = zero;
      
    //   return *this;
      
    // }

    // determine max size

    // BigInt tempA = *this // bigger
    // BigInt tempB = b // smaller
    int temp_a, temp_b, diff = 0;

    // bool sign = false;

    unsigned int size = max(tempA.vec.size(),tempB.vec.size());

    // a = 5 , b =3
    // 5-3 = 2
    // if(tempA>tempB)
    // {
    //   if(tempA.isPositive == true)
    //   {
    //     sign = true;
    //   }

      
      

    // }
    // if(tempB>tempA)
    // {
    //   //a = -4, b == -2
    //   // a -b = -4 + 2 = -2
    //   if(tempB.isPositive == false)
    //   {
    //     sign = false ;
    //   }
    //   else
    //   {
    //     sign = true;
    //   }
    //     tempA = b;
    //     tempB = *this;
    // }

    for(unsigned int i = 0; i<size; i++)
    {

      if(i>=tempA.vec.size())
      {
        temp_a = 0;
      }
      else
      {
        temp_a = tempA.vec[i];
      }
      
      // if a is longer than b


      // if b is longer than a
      
      if(i>=tempB.vec.size())
      {
        temp_b = 0;
      }
      else
      {
        temp_b = tempB.vec[i];
      }


//.          15.        7  = 8
      diff = temp_a - temp_b;

      if(diff<=-1)
      {
        diff += base;

        tempA.vec[i] = diff;

        unsigned int m = i+1;
        
        while(m<tempA.vec.size())
        {
          if(tempA.vec[m] != 0)
          {
            tempA.vec[m] = tempA.vec[m] - 1;
            break;
          }
          else
          {
            tempA.vec[m] = base-1;
          }
          m++;
        }

        if(tempA.vec[m-1] == 0)
        {

          tempA.vec[m] = tempA.vec[m]-1;
        }



      }
      else
      {
        tempA.vec[i] = diff;
      }


  
      // tempA.isPositive = sign;



    }
    unsigned int x = tempA.vec.size()-1;
    while(x>0)
    {
      if(tempA.vec[x] == 0)
      {
        tempA.vec.pop_back();
      }
      else{
        break;
      }

      x--;
    }
    if(tempA.isPositive != this->isPositive)
    {
      tempA.isPositive = !tempA.isPositive;
    }
    tempA.isPositive = sign;
   *this = tempA; 
    
    
  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call *= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator * (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
  BigInt temp = a;
  temp *= b; 
    
    

  return temp;//for now
}



/*
//==================
// MEMBER function
//==================
//  Multiplication assignment operator.
//    i.e., a *= b
//  Implement Long Multiplication
//  Note: What are the base cases?? (e.g., multiply by 0)
*/
const BigInt & BigInt::operator *= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/
    bool sign = false;
    BigInt total(0,base);

    if((this->vec.size() == 1 && this->vec[0] == 0) || (b.vec.size() == 1 && b.vec[0] == 0))
    {
      *this = total;

      return *this;
    }
    if((this->vec.size() == 1 && this->vec[0] == 1) || (b.vec.size() == 1 && b.vec[0] == 1))
    {
      //-1101 * 1 
      //b == [1] where b.vec.size()== 1
      //And state size is 1
      if(this->vec[0] == 1 && vec.size() == 1)
      {
        if(this->isPositive == b.isPositive)
        {
          sign = true;
        }
        
        total = b;
        total.isPositive = sign;
        *this = total;
        return *this;
      }
      if(b.vec[0] == 1)
      {
        /// /cout <<"\n\nMultiplying a by B: "<<b.to_int()<<endl;
        if(b.isPositive == this->isPositive)
        {
          sign = true;
        }
        else
        {

          sign = false;

        }

        this->isPositive = sign;
        return *this;
      }

    }

    if(this->isPositive == b.isPositive)
    {
      sign = true;
    }
    

    

    total.isPositive = sign;
    

    int carry = 0;

    int product = 0;

    

    for(unsigned int i = 0; i<b.vec.size(); i++)
    {
      BigInt temp;
      temp.base = this->base;
      temp.isPositive = sign;

      for(unsigned int q = 0; q<i; q++)
      {
        temp.vec.push_back(0);
      }

      for(unsigned int j = 0; j<this->vec.size(); j++)
      {

        product = vec[j]*b.vec[i] + carry;
        
        carry = product/base;

        temp.vec.push_back(product%base);

      }

      if(carry>=1)
      {
        temp.vec.push_back(carry);
      }

      carry = 0;

      total += temp;



    }

    *this = total;
    

  
    return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call /= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator / (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
  
    BigInt temp = a;

    temp /= b;
    


    return temp;//for now
}


/*
//==================
// MEMBER function
//==================
//  Division assignment operator.
//    - Call 'divisionMain' to get the quotient;
*/
const BigInt & BigInt::operator /= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();
    }
    /************* You complete *************/

    BigInt quotient,remainder;

    divisionMain(b,quotient,remainder);

    *this = quotient;
  
  
  
    return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call %= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator % (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
    BigInt temp = a;

    temp %= b;
  

    
    
    return temp;//for now
}


/*
//==================
// MEMBER function
//==================
//  Modulus assignment operator.
//    - Call 'divisionMain' to get the remainder;
//    - Note: remainder takes the sign of the dividend.
*/
const BigInt & BigInt::operator %= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();//divide by zero.
    }
    /************* You complete *************/

    BigInt quotient,remainder;

    divisionMain(b,quotient,remainder);

    this->isPositive = remainder.isPositive;

    *this = remainder;


  
  
  
  
    return *this;
}

/*
//  Main function for the Division (/=) and Modulus (%=) operators.
//     - Compute (q)uotient and (r)emainder
//     - Implement Long Division
//  Note: 1. This should behave like integer division
//        2. What are the base cases?? (e.g., div by itself)
*/
void BigInt::divisionMain(const BigInt &b, BigInt &quotient, BigInt &remainder){

    /************* You complete *************/
    BigInt zero(0,base);
    BigInt one(1,base);
    BigInt tempA = *this;
    BigInt tempB = b;

    



    // cout << "This: " << (*this).to_string() << endl;
    // cout << "B: " << tempB.to_string() << endl;
    tempA.isPositive = true;
    tempB.isPositive = true;

    if(tempA.vec.size()<tempB.vec.size())
    {
      quotient = zero;
      remainder = *this;
      return;
    }

  

  if(tempA<tempB)
  {
    quotient = zero;
    remainder = *this;
    return;
  }

  if(tempA == tempB)
  {
    
    if(this->isPositive == false && b.isPositive == true)
    {
      one.isPositive = false;
    }
    if(this->isPositive == true && b.isPositive == false)
    {
      one.isPositive = false;
    }

    quotient = one;

    remainder = zero;
    return;
  }

  

  BigInt positive_divisor = tempB;
  positive_divisor.isPositive = true;

   int pos = vec.size()-1;
//Initalize div_seq(vec[pos], base)
  BigInt dividend_seq(0,base);
  //accessing a position in vec that doesnt exist
  //  dividend_seq.vec.push_back(vec[pos]);
  //cout << "DIVIDEND SEQUENCE" << dividend_seq.to_int() << endl;
  //cout << "POSITIVE DIVISOR" << positive_divisor.to_int() << endl;
  //dividend sequence = 1
  //positive divisor = 3
  //pos = 2
  //times = 1 
  //quotient = 1
  dividend_seq.vec.clear();
  quotient.vec.clear();
  while(dividend_seq < positive_divisor)
  
  {
    //cout << "DIVIDEND SEQUENCE" << dividend_seq.to_int() << endl;
    //cout << "POSITIVE DIVISOR" << positive_divisor.to_int() << endl;
    //
    dividend_seq.vec.insert(dividend_seq.vec.begin(),vec[pos]);
    pos--;
    //make cout statements in each loop testing all variables 
    //See which loop your stuck in and why
  }
  while(pos>=-1)
  {

    int times = 0;

    while(dividend_seq >= positive_divisor)
    {
      dividend_seq -= positive_divisor;
      times += 1;
    }

    quotient.vec.insert(quotient.vec.begin(),times);

    if(dividend_seq.vec.size()==1 && dividend_seq.vec[0] == 0)
    {
      dividend_seq.vec.clear();
    }
    if(pos>=0)
    {
      dividend_seq.vec.insert(dividend_seq.vec.begin(),vec[pos]);
    }
    pos--;



  }
  

  if(this->isPositive == false || b.isPositive == false)
  {

    // isPositive = false;
    if(this->isPositive == false && b.isPositive == true)
    {
      quotient.isPositive = isPositive;
      remainder.isPositive = isPositive;
    }
    if(this->isPositive == true && b.isPositive == false)
    {
      quotient.isPositive = !isPositive;
      remainder.isPositive = isPositive;
    }

    
  }
  if(this->isPositive == false && b.isPositive == false)
  {
    // isPositive = true;
    remainder.isPositive = !isPositive;
    quotient.isPositive = !isPositive;
  }
  if(this->isPositive == true && b.isPositive == true)
  {
    // isPositive = true;
    remainder.isPositive = isPositive;
    quotient.isPositive = isPositive;
  }

  if(dividend_seq>zero)
  {
    remainder = dividend_seq;
    // remainder.isPositive = dividend_seq.isPositive;
    if(this->isPositive == false || b.isPositive == false)
    {
      remainder.isPositive = this->isPositive;
    }
    if(this->isPositive == false && b.isPositive == false)
    {
      remainder.isPositive = this->isPositive;
    }
    if(this->isPositive == true && b.isPositive == true)
    {
      remainder.isPositive = this->isPositive;
    }

    // else
    // {
    //   remainder.isPositive = true;
    // }
    
  }
  else{

    remainder = zero;
    remainder.isPositive = true;
    return;

  }

  

  

  

  
  

}



/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'exponentiation' function on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt pow(const  BigInt &a, const BigInt & b){

    /************* You complete *************/
  
    BigInt temp = a;

    temp.exponentiation(b);


  
  
  
  
    return temp;//for now
}

/*
//==================
// MEMBER function
//==================
//  Exponentiation assignment function.
//     - i.e., a.exponentiation(b);
// Note: 1. implement Exponentiation by Squaring (see the writeup)
//       2. b should be treated as BigInt, not int or other data type.
*/
const BigInt & BigInt::exponentiation(const BigInt &b){
  // cout<<this->base<<endl;
  // cout<<b.base<<endl;
    if(base != b.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
    /************* You complete *************/
    BigInt zero(0,base);
    zero.base = base;
    BigInt one(1,base);
    one.base = base;
    BigInt two(2,base);
    two.base = base;
    if(b.vec.size() == 1)
    {
      if(b.vec[0] == 0)
      {
        *this = one;

        return *this;
        
      }
      if(b.vec[0] == 1)
      {
        
        return *this;
      }
    }
    if(vec.size() == 1)
    {
      if(vec[0] == 0)
      {
        
        *this = zero;
        return *this;
        
      }
      if(vec[0] == 1)
      {
        if(this->isPositive == false)
        {
          if(b % two == zero)
          {
            this->isPositive = true;
            return *this;
          }
          else
          {
            
            return *this;
          }
        }
        
        
        return *this;
      }
    }

    BigInt tempA = *this;
    tempA.base = base;
    BigInt tempB = b;
    tempB.base = base;
    BigInt small_x(1,base);
    small_x.base = base;
    // int iter = 0;
    while(tempB>one)
    {
      

      if(tempB  % two == zero)
      {

        tempA *= tempA;

        


        
      }

      if(tempB % two == one)
      {
        small_x *= tempA;

        tempB = (tempB-one);

        

        tempA *= tempA;
        
      }

      tempB /= two;

      // iter++;

      // if(tempB.base != one.base)
      // {

      //   cout<<this->base<<endl;
      //   cout<<b.base<<endl;
      //   cout<<iter<<endl;
      // }

      tempB.base = base;
      one.base = base;

    }

    tempA *= small_x;

    *this = tempA;




  
  
  
    return *this;
   
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'modulusExp' function on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt modPow(const BigInt &a, const BigInt &b, const BigInt &m){

    /************* You complete *************/


    BigInt temp = a;

    temp.modulusExp(b,m);
  

  
  
    return temp;//for now
}


/*
//==================
// MEMBER function
//==================
//  Modulus Exponentiation assignment function.
//     - i.e., a.modulusExp(b)
// Note: 1. implement Modulus Exponentiation (see the writeup)
//       2. b should be treated as BigInt, not int or other data type.
// Hint: same implementation as exponentiation, but take modulus 
//          after every call to the *= operator.
*/
const BigInt & BigInt::modulusExp(const BigInt &b, const BigInt &m){
    if(base != b.base || base != m.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
    /************* You complete *************/
     BigInt zero(0,base);
    zero.base = base;
    BigInt one(1,base);
    one.base = base;
    BigInt two(2,base);
    two.base = base;
    if(b.vec.size() == 1)
    {
      if(b.vec[0] == 0)
      {
        *this = one;

        return *this;
        
      }
      if(b.vec[0] == 1)
      {
        
        return *this;
      }
    }
    if(vec.size() == 1)
    {
      if(vec[0] == 0)
      {
        
        *this = zero;
        return *this;
        
      }
      if(vec[0] == 1)
      {
        if(this->isPositive == false)
        {
          if(b % two == zero)
          {
            this->isPositive = true;
            return *this;
          }
          else
          {
            
            return *this;
          }
        }
        
        
        return *this;
      }
    }

    BigInt tempA = *this;
    tempA.base = base;
    BigInt tempB = b;
    tempB.base = base;
    BigInt small_x(1,base);
    small_x.base = base;
    // int iter = 0;
    while(tempB>one)
    {

      if(tempB  % two == zero)
      {

        tempA *= tempA;

        tempA %= m;


        
      }

      if(tempB % two == one)
      {

        small_x *= (tempA % m);

        tempA *= tempA;

        tempA %= m;
        
        small_x %= m;

        tempB = (tempB-one);

        

        
        
        
      }

      tempB /= two;

      
      
      tempB.base = base;
      one.base = base;

    }


    tempA *= small_x;

    tempA %= m;

    *this = tempA;


  
  
    return *this;
}

//******************************************************************
//END OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************

//******************************************************************
//START OF SANITY CHECK FUNCTIONS
//YOU CAN USE THEM, BUT DO NOT CHANGE ANYTHING
//THESE FUNCTIONS ARE COMPLETE.
//******************************************************************
void BigInt::printVecItems(){
  cout<<"[";
  for(size_t i = 0;i<vec.size();i++){
    cout<<vec[i];
    if(i < vec.size()-1){
      cout<<",";
    }
  }
  cout<<"]"<<endl;
}

bool BigInt::getSign(){
	return isPositive;
}

int BigInt::getBase(){
	return base;
}
//******************************************************************
//END OF SANITY CHECKS SECTION
//******************************************************************