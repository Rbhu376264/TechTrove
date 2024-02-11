#include "internal-range.h"
using namespace std;


// You may add any prototypes of helper functions here

// int sum(Node * root, int depth, int min, int max, int total,int depth_tracker)
// {
//     if(root == nullptr || depth_tracker == depth)
//     {
//         return total;
//     }
//     else if(min<=root->key && root->key<=max)
//     {
//         total += 1;
//         depth_tracker += 1;
//         int val_left = sum(root->left,depth,min,max,total,depth_tracker);
//         int val_right = sum(root->right,depth,min,max,val_left,depth_tracker);

//         return val_right;
//     }
//     else
//     {
//         int val_left = sum(root->left,depth,min,max,total,depth_tracker+1);
//         int val_right = sum(root->right,depth,min,max,val_left,depth_tracker+1);

//         return val_right;
//     }
// }

void sum(Node * root, int depth, int min, int max, int& total,int depth_tracker)
{
    if(root == nullptr || depth_tracker == depth)
    {
        return;
    }
    else if(min<=root->key && root->key<=max)
    {
        total += 1;
        depth_tracker += 1;
        sum(root->left,depth,min,max,total,depth_tracker);
        sum(root->right,depth,min,max,total,depth_tracker);

        
    }
    else if(max<root->key)
    {
        sum(root->left,depth,min,max,total,depth_tracker+1);

       
    }
    else if(root->key<min)
    {
        sum(root->right,depth,min,max,total,depth_tracker+1);
    }
}
// Now implement the sumInternalRange function and any necessary helpers

// int sumInternalRange(Node * root, int depth, int min, int max)
// {
//     int total = 0;
//     int evaluation = sum(root,depth,min,max,total,0);

//     return evaluation;


// }

int sumInternalRange(Node * root, int depth, int min, int max)
{
    int total = 0;
    sum(root,depth,min,max,total,0);

    return total;


}