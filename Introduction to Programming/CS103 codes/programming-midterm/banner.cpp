#include <iostream>
#include <fstream>
#include <string>
#include "banner.h"

using namespace std;

#ifdef RF
Letter* read_font(const char* fname)
{
    ifstream ifile(fname);
    if(ifile.fail())
    {
        return NULL;
    }

    Letter* font = new Letter[95];

    int m = 32;

    int r = 0;

    while(r<95)
    {
        font[r].c = (char)m;

        r++;
        m++;
    }

    char myline[8];

    ifile.getline(myline,8);

    while(!ifile.fail())
    {
        for(int j = 0; j<8; j++)
        {
            for(int i = 0; i<95; i++)
            {
                if(myline[j] == font[i].c)
                {
                    font[i].lines[j] = myline[j];
                }

            }
        }
        ifile.getline(myline,8);


        

    }
    
}
#endif

#ifdef MB
Banner make_banner(string message, Letter* font)
{
    Banner M;
    M.message = message;
   for(int i = 0; i<95; i++)
   {
       for(int j = 0; j<8; j++)
       {
           M.output[i] = font[i].line[j];

       }
   } 
    return M;
}
#endif

#ifdef PB
void print_banner(Banner b)
{
    for(int i=0;i<8;i++)
    {
        cout << b.output[i] << endl;
    }
}
#endif

#ifdef MAIN
int main(int argc, char* argv[])
{
    if(argc<2)
    {
        cout<<"No font file given."<<endl;
        return 1;
    }
    if(read_font(argv[1]) == NULL)
    {
        cout<<"Unable to read font file."<<endl;
        return 2;
    }
    Letter*font_1 = read_font(argv[1]);

    string str;

    cout<<"Enter your message:"<<endl;
    getline(cin,str);

    //make_banner(str,font_1);
    print_banner(make_banner(str,font_1));

    delete[] font_1;
    
    
}
#endif
