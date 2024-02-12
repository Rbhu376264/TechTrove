#include <iostream>
#include <cstring>

using namespace std;

char* pack(char* in[], int n, char delim)
{
  char*arr = new char[n];
  int i = 0;
  while(i<n)
  {
    // for(int j = 0; j<in[i].size(); ++)
    // {
    //   if(in[i][j] == '\0')
    //   {
    //     arr[i][j] = delim;
    //   }
    //   else{
    //     arr[i][j] = in[i][j];
    //   }
    // }
    int j = 0;
    while(in[i][j] != '\0')
    {
      arr[i][j] = in[i][j];
      j++;
    }
    arr[i][j+1] = delim;
    i++;
    in++;
  }
  return arr;
}

int main(int argc, char* argv[])
{
  if(argc < 3)
  {
    cout << "Not enough arguments." << endl;
    return 1;
  }
  char* str = NULL;
  str = pack(argv+1, argc-2, argv[argc-1][0]);
  if(str)
  {
    cout << str << endl;
    delete [] str;
  }
  else
  {
    cout << "Error packing strings." << endl;
  }
}
