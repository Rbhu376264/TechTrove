#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "rem_dup_lib.h"

using namespace std;

void deleteList(Item* head);
// helper function for debugging
void outputList(ostream& os, Item* head);


// Add implementation of a readlists function such as:
void readLists(const char* filename, Item*& head1, Item*& head2);
// or
// void readLists(char* filename, Item** head1, Item** head2);

void readLists(const char* filename, Item*& head1, Item*& head2)
{
  ifstream ifile(filename);
  string line;
  getline(ifile,line);
  stringstream ss(line);
  int x;
  ss>>x;
  Item* y = new Item(x,nullptr);
  head1 = y;
  Item* prev = y;
  while(ss>>x)
  {
    y = new Item(x,nullptr);

    prev->next = y;
    
    prev = y;
  }

  // for(Item* temp = head1; temp; temp=temp->next){
  //   cout << temp->val << " ";
  // }
  // cout<< endl;

  getline(ifile,line);
  stringstream ss1(line);

  int x1;

  ss1>>x1;

  Item* r = new Item(x1,nullptr);

  head2 = r;

  Item* prev1 = r;

  while(ss1>>x1)
  {
    r = new Item(x1,nullptr);

    prev1->next = r;
    
    prev1 = r;
  }





  
}




// Output function for debug or writing output
void outputList(ostream& os, Item* head)
{
  for(Item* temp = head; temp; temp=temp->next){
    os << temp->val << " ";
  }
  os << endl;
}

// Deallocate memory for a list
void deleteList(Item* head)
{
  if(head==nullptr) return;
  else {
    deleteList(head->next);
    delete head;
  }
}

// Main test driver
int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Usage: ./remdup input_file output_file" << endl;
    return 1;
  }
  Item* head1, *head2;
  readLists(argv[1], head1, head2);

  // Uncomment to verify you read in the right values
  // outputList(cout, head1);
  // outputList(cout, head2);

  ofstream ofile(argv[2]);
  if(ofile.fail()){
    cerr << "Couldn't open output file " << argv[2] << endl;
  }

  removeConsecutive(head1);
  

  // Uncomment to see intermediate results after removeConsecutive
  // outputList(cout, head1);
  
  Item* head3 = concatenate(head1, head2);
  outputList(ofile, head3);
  
  ofile.close();

  // cleanup memory
  deleteList(head1);
  deleteList(head2);
  deleteList(head3);
  return 0;
}
