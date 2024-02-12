#include"delist.h"
#include<iostream>

using namespace std;

DEList::DEList()
{
  head = NULL;
  tail = NULL;
}
DEList::~DEList()
{
  // DEItem* temp = tail;

  while(!empty())
  {
    pop_back();
  }

  // delete tail;
   
}

bool DEList::empty()
{
  if(counter == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
  //return (head == NULL && tail == NULL);
}

int DEList::size()
{
  return counter;
}

int DEList::front()
{
  //cout<<empty()<<endl;
  if(empty())
  {
    return -1;
  }
  
  // int x = head->val;
  return head->val;
  
}

int DEList::back()
{
  //cout<<empty()<<endl;
  if(empty())
  {
    return -1;
  }
  
  return tail->val;
  
}

void DEList::push_front(int new_val)
{
  DEItem* temp = new DEItem;
  temp->val = new_val;
  temp->prev = NULL;
  temp->next = head;

  if(empty())
  {
    head = temp;
    tail = temp;
  }
  else
  {
    head->prev = temp;
    head = temp;
  }
  //head = temp;
  counter++;
}

void DEList::pop_front()
{
  
  if(!empty())
  {
    DEItem* temp = head;
    if(size() == 1)
    {
      //delete head;
      head = NULL;
      tail = NULL;
    }
  
    else
    {
      //temp = head->next;
      temp->next->prev = NULL;
      //delete head;
      head = temp->next;
    } 
    delete temp;
    counter--;
  }
 
}

void DEList::push_back(int new_val)
{

  DEItem* temp = new DEItem;
  temp->val = new_val;
  temp->prev = tail;
  temp->next = NULL;

  if(empty())
  {
    head = temp;
    tail = temp;
  }
  else
  {
    tail->next = temp;
    tail = temp;
  }

  //tail = temp;

  counter++;

}

void DEList::pop_back()
{
 
  if(!empty())
  { 
    DEItem* temp = tail;
    if(size() == 1)
    {
      //delete head;
      head = NULL;
      tail = NULL;
    }
  
    else
    {
      tail->prev->next = NULL;
      //delete tail;
      tail = temp->prev; 
      // tail->next = NULL;
      
    }
    delete temp;
    counter--;
  }

  

}


