/* Author: YOUR NAME HERE
 * Program: color_conv
 * Description: Converts RGB -> CMYK color representation
 */
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
   int red, green, blue;
   double cyan,magenta,yellow,black;
   double red_1, green_1, blue_1;
   cout << "Enter 3 integers (red, green, and blue), in that order:";
   // Enter your code here
   cin>>red>>green>>blue;

   red_1 = red/255.0;

   green_1 = green/255.0;

   blue_1 = blue/255.0;

   double x = max(red_1,green_1);
   
   double white = max(blue_1,x);

   cyan = (white-red_1)/white;

   magenta = (white-green_1)/white;

   yellow = (white-blue_1)/white;

   black = 1-white;

   cout<<"cyan: "<<cyan<<endl;
   cout<<"magenta: "<<magenta<<endl;
   cout<<"yellow: "<<yellow<<endl;
   cout<<"black: "<<black<<endl;


   
   
   
   return 0;
}