// Name:- Rbhu Gandhi

#include <iostream>

using namespace std;

int main()
{
    int lower_bound , upper_bound , max_achiever = -1, min_achiever = 10000, min_length = 10000, max_length = -1, counter = 0, number_copy;
    
    cout<<"Enter the range that you want to search: ";
    cin>>lower_bound>>upper_bound;
    
    
    if(lower_bound == 1)
    {
        min_length = counter;
        min_achiever = lower_bound;
    }
    
    if(lower_bound == upper_bound)
    {
        number_copy = lower_bound;
        while(number_copy != 1)
        {
            if(number_copy%2==1)
            {
                number_copy = number_copy*3 + 1;
                
                counter++;
            }
            else
            {
                number_copy /= 2;
                
                counter++;
            }
            
        }
        
        max_length = counter;
        min_length = max_length;
        max_achiever = lower_bound;
        min_achiever = lower_bound;
    }
    
    if(lower_bound>upper_bound)
    {
        cout<<"Invalid range"<<endl;
        return 0;
    }
    else if(lower_bound != upper_bound && lower_bound < upper_bound)
    {
        for(int i = lower_bound; i<=upper_bound; i++)
        {
            number_copy = i;
            while(number_copy != 1)
            {
                if(number_copy%2==1)
                {
                    number_copy = number_copy*3 + 1;
                    
                    counter++;
                }
                else
                {
                    number_copy /= 2;
                    
                    counter++;
                }
                
            }
            
            
            if(counter>max_length)
            {
                max_length = counter;
                max_achiever = i;
            }
            else if(counter<min_length)
            {
                min_length = counter;
                min_achiever = i;
            }
            
            counter = 0;
        }
    }
    
    cout<<"Minimum Length: "<<min_length<<endl;
    cout<<"Achieved by: "<<min_achiever<<endl;
    cout<<"Maximum Length: "<<max_length<<endl;
    cout<<"Achieved by: "<<max_achiever<<endl;
    
    return 0;
    
    
}
