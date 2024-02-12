/********************************************************
 * Description:
 *  Displays a 64-bit integer (long long) with
 *   commas for thousands, millions, billions, etc.
 *
 * ** ABSOLUTELY NO ARRAYS, NO `string`, NO `vector` **
 *  usage is allowed.
 *
 * Instead, you may only declare:
 *
 *    bool,
 *    int, or
 *    int64_t (long long)
 *
 *  The only library function allowed is pow(base, exp)
 *    defined in the <cmath> library.
 *
 ********************************************************/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
  long long n;
  cout << "Enter an integer:" << endl;
  /*====================*/
  /* Start of your code */
    cin>>n;
    
    long long number, counter_digits = 0, number_copy,x;
    
    if(n<0)
    {
       number = n*-1; 
       number_copy = n*-1;
    }
    else
    {
      number = n;
      number_copy = n;
    }
    
    while(number!=0)
    {
        number = number/ 10;
        counter_digits += 1;
    }
    
    if(counter_digits<4)
    {
      cout<<n;
      return 0;
    }
    
    if(n<0)
    {
        cout<<'-';
    }
    for(int i = counter_digits-1; i>=0; i--)
    {
        
        
        
        x = pow(10,i);
        cout<<number_copy/x;
        number_copy%=x;
        
        
        if(i%3 == 0 && i != 0)
        {
            cout<<',';
        }
    }
  
  
  

  /* End of your code */
  /*==================*/
  
  return 0;
}
