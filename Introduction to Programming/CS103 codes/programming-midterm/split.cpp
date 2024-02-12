#include <iostream>

using namespace std;

int count_delims(char delim, char* str)
{
    int delim_counter = 0;

    int i = 0;

    // for(int i = 0; i<*str.length(); i++)
    // {
    //     if(str[i] == delim)
    //     {
    //         delim_counter++;
    //     }
    // }

    while(str[i]!='\0')
    {
        if(str[i] == delim)
        {
            delim_counter++;
        }

        i++;

    }
    //delim_counter++;
    return delim_counter++;
}

char** split(char delim, char* str, int *size)
{
    *size = count_delims(delim,str) + 1;

    char** W = new char*[*size];

    for(int i = 0; i<*size; i++)
    {
        W[i] = new char[*size];
        if(str[i] != delim)
        {
            W[i] = &str[i];
        }
        if(str[i] == delim)
        {
            str[i] = '\0';
        }



    }

    return W;
    
}

#ifndef TEST
int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        cout << "Please enter a delimter and a string as arguments." << endl;
        return 1;
    }
    //do not make any changes to main! If changes to main are needed to make your code work, you have a bug elsewhere!
    int n;
    char** w = split(argv[1][0], argv[2], &n);
    for(int i=0;i<n;i++)
    {
        cout << i << ":" << w[i] << endl;
    }
    delete[] w;
}
#endif

