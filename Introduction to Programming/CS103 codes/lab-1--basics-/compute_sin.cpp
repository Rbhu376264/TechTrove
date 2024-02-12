/* Author: YOUR NAME HERE
 * Program: compute_sin
 * Description: Reads a number x from input, an angle in radians. 
 *    Computes an approximation to sin(x) using an 4th-order Taylor series.
 */
#include <iostream>
#include <cmath>

using namespace std;

int fact(int); // declares a function the skeleton defines for you.

int main(int argc, char *argv[])
{
   // Declare any variables you need here
   double x, output;
   
   // Prompt the user
   cout << "Enter x in radians:  ";
   
   
   // get input
   cin>>x;
   
   
   // Do some operations

   output = x - pow(x,3)/fact(3) + pow(x,5)/fact(5) - pow(x,7)/fact(7);
   
   // Print the result to the user

   cout<<output<<endl;
   
   
   // You're done
   return 0;
   
}

// here's the actual definition of fact, declared earlier.
int fact(int n)
{
   int result = 1;
   for (int i = 1; i <= n; i++) {
      result = result * i;
   }
   return result;
}

