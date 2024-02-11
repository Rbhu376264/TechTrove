#include "bst.h"

#include <stack>
#include <queue>
#include <set>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <climits>

int height(Node* l);
// int rheight(Node* r,int rsum);

bool isBalanced(Node *root) {
	//Get the heights of the left and right subtrees - helper func?
	//Determine if this node is balanced! If not ret false!

	//Check if there are subtrees under us
	//Are they balanced?

	//If all nodes are balanced return true!

	int height_left = height(root->left);
	int height_right = height(root->right);
	if(height_left == -1 || height_right == -1)
	{
		return false;
	}

	if(abs(height_left-height_right) <= 1)
	{
		return true;

	}
	return false;
	

	
}

int height(Node* l)
{
	if(l== nullptr)
	{
		return 0;

	}
	else
	{
		int lheight = height(l->left);
		int rheight = height(l->right);
		if(abs(lheight-rheight) > 1)
		{
			return -1;
		}

		return std::max(lheight,rheight)+1; 
	}
}

