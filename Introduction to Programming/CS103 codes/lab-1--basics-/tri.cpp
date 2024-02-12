/* Author: Rbhu Gandhi
 */
#include <iostream>
#include <algorithm>
#include<cmath>
using namespace std;

int main()
{
    
    double angle;
    cout<<"Enter an angle"<<endl;
    cin>>angle;
    angle = angle*(M_PI/180.0);
  
   for(int i = 0; i<31; i++)
   {
       if(floor(i*tan(angle))>=20 && floor(i*tan(angle))<=30)
       {
           for(int j = 0; j<20; j++)
           {
               cout<<'*';
           }
            cout<<endl;
       }
       else{
           for(int j = 0; j<floor(i*tan(angle)); j++)
           {
               cout<<'*';
           }
           cout<<endl;
       }
   }
   return 0;
}