#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
// for pair
#include <functional>
#include <string>

using namespace std;

// typedef for X,Y pair
typedef std::pair<size_t, size_t> XYPair;

// Utility Prototypes
bool operator==(const XYPair& p1, const XYPair& p2);
void printPaths(const std::vector<std::vector<XYPair> >& results);

// Utility function to compare XY points
bool operator==(const XYPair& p1, const XYPair& p2)
{
  return p1.first == p2.first && p1.second == p2.second;
}


// Primary street grid function prototype
std::vector<std::vector<XYPair> > gridpaths(const XYPair& inter, const XYPair& final);

// Prototype any helper functions here
void gridPathHelper(vector<std::vector<XYPair> >& vec, vector<XYPair>& evec, XYPair start,const XYPair& inter,const XYPair& final,bool isInterpassed);
bool operator<=(const XYPair& p1, const XYPair& p2);
bool operator>=(const XYPair& p1, const XYPair& p2);



// Implement your gridpaths and any helper functions below
std::vector<std::vector<XYPair> > gridpaths(const XYPair& inter, const XYPair& final)
{
  vector<vector<XYPair> >vecs;
  vector<XYPair> vec;
  XYPair initial;
  initial.first = 0;
  initial.second = 0;

  gridPathHelper(vecs,vec,initial,inter,final,false);

  return vecs;

}

bool operator<=(const XYPair& p1, const XYPair& p2)
{
  return p1.first <= p2.first && p1.second <= p2.second;
}

bool operator>=(const XYPair& p1, const XYPair& p2)
{
  return p1.first >= p2.first && p1.second >= p2.second;
}

void gridPathHelper(vector<std::vector<XYPair> >& vec,vector<XYPair>& evec,XYPair start,const XYPair& inter,const XYPair& final,bool isInterpassed)
{
  
  if(evec.size() != 0 && start == final)
  {
    evec.push_back(start);
    vector<XYPair> temp = evec;

    vec.push_back(temp);

    evec.pop_back();

    return;
  }
  if(isInterpassed)
  {
    evec.push_back(start);
    start.second += 1;
    if(start<=final)
    {
      gridPathHelper(vec,evec,start,inter,final,isInterpassed);
      
    }

    
    start.second -= 1;
    start.first += 1;

    if(start<=final)
    {
      gridPathHelper(vec,evec,start,inter,final,isInterpassed);
      
    }

    evec.pop_back();



  }
  
  else
  {
    if(start == inter)
    {
      isInterpassed = true;
      evec.push_back(start);
      start.second += 1;
      gridPathHelper(vec,evec,start,inter,final,isInterpassed);
      start.second -= 1;
      start.first += 1;
      gridPathHelper(vec,evec,start,inter,final,isInterpassed);
      evec.pop_back();


    }
    else if(start <= inter)
    {
      evec.push_back(start);
      start.second += 1;
      gridPathHelper(vec,evec,start,inter,final,isInterpassed);
      
      start.second -= 1;
      start.first += 1;

      gridPathHelper(vec,evec,start,inter,final,isInterpassed);
      evec.pop_back();
      
    }
    else if(start>= inter && start<=final && isInterpassed == false)
    {
      return;

    }
  }



}




// Complete - but can be changed for debugging purposes
int main(int argc, char* argv[])
{
  // Default to intermediate point of 2,3 and final location of 3,4
  size_t ix = 2, iy = 3, fx = 3, fy = 4;
  if(argc >= 5) {
    ix = atoi(argv[1]);
    iy = atoi(argv[2]);
    fx = atoi(argv[3]);
    fy = atoi(argv[4]);
  }
  vector<vector<XYPair> > results;
  results = gridpaths({ix,iy},{fx,fy});  
  printPaths(results);

  return 0;
}

// Prints the results in a clean fashion for human consumption / debugging
void printPaths(const vector<vector<XYPair> >& results)
{
  for( const auto& path : results) {
    for( size_t i = 0; i < path.size()-1; i++ ) 
    {      
      cout << path[i].first << "," << path[i].second << " -> ";
    }
    cout << path.back().first << "," << path.back().second << endl;
  }
  cout << results.size() << " solutions." << endl;

}
