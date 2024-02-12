#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

int main(int argc, char* argv[])
{
  if(argc<2)
  {
    cout<<"Please enter a chart file name as a command line argument."<<endl;
    return 0;
  }

  ifstream ifile(argv[1]);
  if(ifile.fail())
  {
    cout<<"Unable to open input file."<<endl;
    return 0;
  }

  vector<int>num;

  int x;
  int width = 0;
  int max = 0;
  while(true)
  {
    ifile>>x;

    if(!ifile.fail())
    {
      break;
    }
    
    if(x>max)
    {
      max = x;
    }
    num.push_back(x);
  }

  // int max = 0;
  // unsigned int k = 0;
  // // for(unsigned int i = 0; i<num.size(); i++)
  // while(k<num.size())
  // {

  //   cout<<num[k]<<endl;
  //   if(num[k]>max)
  //   {
      
  //     max = num[k];
  //   }
  //   k++;
  // }

  // cout<<max;
  if(max != 0)
  {
    width = log(max) + 1;
  }
  

  for(int i = 0; i<num.size(); i++)
  {
    for(int j = 0; j<max; j++)
    {
      if(num[i] != max)
      {
        if(j>=max-num[i])
        {
          cout<<'*'<<setw(width)<<endl;
        }
        else
        {
          cout<<' '<<setw(width)<<endl;
        }
      }
      else
      {
        cout<<'*'<<setw(width)<<endl;
      }
    }
    

  }
  for(unsigned int i = 0; i<(width-1)*num.size(); i++)
  {
    cout<<'-';
  }
  cout<<endl;

  for(unsigned int i = 0; i<num.size(); i++)
  {
    cout<<num[i]<<setw(width);
  }
  cout<<endl;

  return 0;
    
}