/* 
maze.cpp
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

// main function to read, solve maze, and print result
int main(int argc, char* argv[]) {
   int rows, cols, result;
   char** mymaze=NULL;
   
   if(argc < 2)
   {
       cout << "Please provide a maze input file" << endl;
       return 1;
   }
  
   mymaze = read_maze(argv[1],&rows,&cols); // <---TASK: COMPLETE THIS FOR CHECKPOINT 1
   
     
     
   if (mymaze == NULL) {
      cout << "Error, input format incorrect." << endl;
      return 1;
   }
	 //================================
   // When working on Checkpoint 4, you will call maze_search here.
   // But for Checkpoint 1, just assume we found the path.
  
   result = maze_search(mymaze,rows,cols); // <--- TASK: CHANGE THIS FOR CHECKPOINT 4
	
	
   // examine value returned by maze_search and print appropriate output
   if (result == 1) { // path found!
      print_maze(mymaze, rows, cols);
   }
   else if (result == 0) { // no path :(
      cout << "No path could be found!" << endl;
   }
   else { // result == -1
      cout << "Invalid maze." << endl;
   }

	 //================================
   // ADD CODE BELOW
   // to delete all memory that read_maze allocated: CHECKPOINT 2

    for(int i = 0; i<rows; i++)
    {
      delete[]mymaze[i];
    }

    delete[] mymaze;
  
  
  
   return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if invalid maze (not exactly one S and one F)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 * NOTE: don't forget to deallocate memory in here too!
 *************************************************/
int maze_search(char** maze, int rows, int cols) 
{
  // *** You complete **** CHECKPOINT 4

  Location Start;// Finish;
  Queue q(rows*cols);
  int start_discovered = 0, finish_discovered = 0;

  for(int i = 0; i<rows; i++)
  {
    for(int j = 0; j<cols; j++)
    {
      if(maze[i][j] == 'S')
      {
        Start.row = i;
        Start.col = j;
        start_discovered++; 
      }
      else if (maze[i][j] == 'F')
      {
        // Finish.row = i;
        // Finish.col = j;
        finish_discovered++;
        
      }
    }
  }

  if(start_discovered != 1 || finish_discovered != 1)
  {

    return -1;
  }

  int **traversed = new int*[rows];

  for(int i = 0; i<rows; i++)
  {
    traversed[i] = new int[cols];
  } 
  for(int i = 0; i<rows; i++)
  {
    for(int j = 0; j<cols; j++)
    {
      traversed[i][j] = 0;
    }
  }
  
  Location **prior = new Location*[rows];

  for(int i = 0; i<rows; i++)
  {
    prior[i] = new Location[cols];
  }

  Location N, S, W, E, present;
  bool discovered = false;

  q.add_to_back(Start);

  while(!q.is_empty())
  {
    present = q.remove_from_front();

    N.row = present.row-1;
    N.col = present.col;

    if(N.row>=0 && N.col>=0 && N.row<rows && N.col<cols)
    {

      if(maze[N.row][N.col] == 'F')
      {
        discovered = true;
        break;
      }
      else if (maze[N.row][N.col] == '.' && traversed[N.row][N.col] != 1)
      {
        q.add_to_back(N);
        traversed[N.row][N.col] = 1;
        prior[N.row][N.col] = present;
      }

    }
    S.row = present.row+1;
    S.col = present.col;

    if(S.row>=0 && S.col>=0 && S.row<rows && S.col<cols)
    {

      if(maze[S.row][S.col] == 'F')
      {
        discovered = true;
        break;
      }
      else if (maze[S.row][S.col] == '.' && traversed[S.row][S.col] != 1)
      {
        q.add_to_back(S);
        traversed[S.row][S.col] = 1;
        prior[S.row][S.col] = present;
      }

    }
    E.row = present.row;
    E.col = present.col+1;

    if(E.row>=0 && E.col>=0 && E.row<rows && E.col<cols)
    {

      if(maze[E.row][E.col] == 'F')
      {
        discovered = true;
        break;
      }
      else if (maze[E.row][E.col] == '.' && traversed[E.row][E.col] != 1)
      {
        q.add_to_back(E);
        traversed[E.row][E.col] = 1;
        prior[E.row][E.col] = present;
      }

    }
    W.row = present.row;
    W.col = present.col-1;

    if(W.row>=0 && W.col>=0 && W.row<rows && W.col<cols)
    {

      if(maze[W.row][W.col] == 'F')
      {
        discovered = true;
        break;
      }
      else if (maze[W.row][W.col] == '.' && traversed[W.row][W.col] != 1)
      {
        q.add_to_back(W);
        traversed[W.row][W.col] = 1;
        prior[W.row][W.col] = present;
      }

    }
  }

  for(int i = 0; i<rows; i++)
  {
    delete[]traversed[i];
  }
  delete[]traversed;

  if(!discovered)
  {

    for(int i = 0; i<rows; i++)
    {
      delete[]prior[i];
    }

    delete[]prior;

    return 0;
    
  }

  if(discovered)
  {
    
    while(maze[present.row][present.col] != 'S'){
      maze[present.row][present.col] = '*';   
      present = prior[present.row][present.col];
    }
    for(int i = 0; i<rows; i++)
    {
      delete[]prior[i];
    }

    delete[]prior;

    return 1;
  }


  
  
  
  
  
  
  
  
  return 0; // DELETE this stub, it's just for Checkpoint 1 to compile.
}
