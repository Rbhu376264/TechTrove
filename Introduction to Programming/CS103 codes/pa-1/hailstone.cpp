//Name:- Rbhu Gandhi

#include <iostream>

using namespace std;

int main()
{
    int number, counter = 0;
    
    cout<<"Enter a number: ";
    cin>>number;
    
    while(number != 1)
    {
        if(number%2==1)
        {
            number = number*3 + 1;
            
            cout<<number<<" ";
            
            counter++;
        }
        else
        {
            number /= 2;
            
            cout<<number<<" ";
            
            counter++;
        }
        
    }
    cout<<endl;
    cout<<"Length: "<<counter<<endl;
    return 0;
    
    
}
