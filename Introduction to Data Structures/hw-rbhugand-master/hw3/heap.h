#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

private:
  /// Add whatever helper functions and data members you need below
  void Heapify(int idx);
  void Trickleup(int loc);
  std::vector<T>heap_vec;
  int mheap;
  PComparator mcomp;
  
  public:
  int size();

};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c)
{
  mheap = m;
  mcomp = c;

}
template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{

}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  heap_vec.push_back(item);
  Trickleup(heap_vec.size()-1);
}
template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  if(heap_vec.size() == 0)
  {
    return true;
  }
  
  return false;
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("The heap is empty");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return heap_vec[0];


}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("The heap is empty");

  }
  std::swap(heap_vec[0],heap_vec[heap_vec.size()-1]);
  heap_vec.pop_back();
  Heapify(0);


}

template<typename T, typename PComparator>
void Heap<T,PComparator>::Heapify(int idx)
{
  int msize = heap_vec.size()-1;
  if(empty())
  {
    return;
  }
  if(idx > msize)
  {
    return;
  }
  int smaller_child = mheap*idx + 1;
  if(smaller_child >msize)
  {
    return;
  }

  for(int i = 2; i<=mheap; i++)
  {
    int next_child = mheap*idx + i;
    if(next_child>msize)
    {
      break;
    }

    if(mcomp(heap_vec[next_child],heap_vec[smaller_child]))
    {
      smaller_child = next_child;
    }
    
  }

  if(mcomp(heap_vec[smaller_child],heap_vec[idx]))
  {
    std::swap(heap_vec[idx],heap_vec[smaller_child]);
    Heapify(smaller_child);
  }


}

template<typename T, typename PComparator>
void Heap<T,PComparator>::Trickleup(int loc)
{
  int parent = (loc-1)/mheap;

  while(parent>=0 && mcomp(heap_vec[loc],heap_vec[parent]))
  {
    std::swap(heap_vec[loc],heap_vec[parent]);
    loc = parent;
    parent = (loc-1)/mheap;
  }
}
template<typename T, typename PComparator>
int Heap<T,PComparator>::size()
{
  return heap_vec.size();
}


#endif

