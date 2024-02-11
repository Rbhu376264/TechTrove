#include <iostream>
#include <fstream>
#include "stack.h"

using namespace std;

int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Please provide the input and output filenames" << endl;
    return 1;
  }
  // Add your code here
  ofstream outfile(argv[2]);
  ifstream infile(argv[1]);
  Stack<int> inStage;
  int x ;
  while(infile>>x)
  {
    if(x == 0 || x == -1)
    {
      inStage.push(x);
    }
    else
    {
      int inc = 0;

      while(inStage.size() != 0 && inc != x)
      {
        int num = inStage.top();

        if(num == 0)
        {
          outfile<<"black ";
        }
        else
        {
          outfile<<"gray ";
        }

        inc++;

        inStage.pop();
      }
      outfile<<endl;
    }

  }


  return 0;
}
