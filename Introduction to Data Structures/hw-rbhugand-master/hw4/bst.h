#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

// #include <iostream>
// using namespace std;

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here

    int height(Node<Key,Value>* l) const;
    void addNode(Node<Key, Value>* root_,const std::pair<const Key, Value> &keyValuePair,Node<Key, Value>* prev);
    static Node<Key, Value>* successor(Node<Key, Value>* current);
    void clearhelp(Node<Key,Value>* start);
    // void removeHelp(Node<Key, Value>* present,const Key& key);
protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO

    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_ = nullptr;

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO

    return current_ == rhs.current_;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return current_ != rhs.current_;
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // // TODO
    // Node<Key,Value>* succptr = 
    current_ = successor(current_);
    return *this;
    // if(current_->right_ != nullptr)
    // {
    //     Node<Key, Value>* temp = current_->right_;

    //     while(temp != nullptr)
    //     {
    //         temp = temp->left_;
    //     }

    //     this->current_ = temp;

    //     return *this;
    // }
    // else
    // {
    //     Node<Key, Value>* temp = current_->parent_;
    //     while(temp != nullptr)
    //     {
    //         if(temp == temp->parent_->left_)
    //         {
    //             current_ = temp;

    //             return *this;
    //         }
    //         temp = temp->parent_;

    //     }

    //     this->current_ = temp;

    //     return *this;
    // }

}
// template<class Key, class Value>
// Node<Key, Value>*
// BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
// {
//     if(current->right_ != nullptr)
//     {
//         Node<Key, Value>* temp = current->right_;

//         while(temp != nullptr)
//         {
//             temp = temp->left_;
//         }

//         current = temp;

//         return current;
//     }
//     else
//     {
//         Node<Key, Value>* temp = current->parent_;
//         while(temp != nullptr)
//         {
//             if(temp == temp->parent_->left_)
//             {
//                 current = temp;

//                 return current;
//             }
//             temp = temp->parent_;

//         }

//         current = temp;

//         return current;
//     }

// }

/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    root_ = nullptr;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    clear();

}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO

    
    addNode(root_,keyValuePair,nullptr);


}

template<class Key, class Value>
void BinarySearchTree<Key, Value>::addNode(Node<Key, Value>* val,const std::pair<const Key, Value> &keyValuePair,Node<Key, Value>* prev)
{
    if(empty())
    {

        Node<Key, Value>* newOne = new Node<Key, Value>(keyValuePair.first,keyValuePair.second,prev);
        root_ = newOne;
        return;
    }
    else if(keyValuePair.first < val->getKey())
    {
        if(val->getLeft() == nullptr)
        {
            Node<Key, Value>* newOne = new Node<Key, Value>(keyValuePair.first,keyValuePair.second,prev);
            val->setLeft(newOne);
            newOne->setParent(val);
            return;
        }
        prev = val;
        addNode(val->getLeft(),keyValuePair,prev);

    }
    else if(keyValuePair.first > val->getKey())
    {
        // if(keyValuePair.first == val->getKey())
        // {
        //     val->setValue(keyValuePair.second);
        //     return;
        // }
        if(val->getRight() == nullptr)
        {
            Node<Key, Value>* newOne = new Node<Key, Value>(keyValuePair.first,keyValuePair.second,prev);
            val->setRight(newOne);
            newOne->setParent(val);
            return;
        }                          
        prev = val;
        addNode(val->getRight(),keyValuePair,prev);
    }
    else
    {
        val->setValue(keyValuePair.second);
        return;
    }


}



/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    // removeHelp(root_,key);

    Node<Key,Value>* checkptr = internalFind(key);
   
    if(checkptr == nullptr)
    {
        return;
    }
    else
    { 
        
        if(checkptr->getLeft() == nullptr && checkptr->getRight() == nullptr)
        {
            if(checkptr->getParent() != nullptr)
            {
                if(checkptr == checkptr->getParent()->getLeft())
                {
                    checkptr->getParent()->setLeft(nullptr);

                    delete checkptr;

                    return;

                }

                if(checkptr == checkptr->getParent()->getRight())
                {
                    checkptr->getParent()->setRight(nullptr);

                    delete checkptr;

                    return;
                    
                }
            }
            else
            {
                // nodeSwap(checkptr,predecessor(checkptr));
                
                // if(checkptr->left_ != nullptr)
                // {
                //     checkptr->left_->setParent(checkptr->getParent());

                //     checkptr->getParent()->setRight(checkptr->getLeft());

                // }
                // else if(checkptr->right_ != nullptr)
                // {
                //     checkptr->getParent()->setRight(nullptr);
                
                // }

                root_ = nullptr;
                
                delete checkptr;

                return;
            }

        }

        if(checkptr->getLeft() != nullptr && checkptr->getRight() == nullptr)
        {
            // nodeSwap(checkptr,predecessor(checkptr));

            if(checkptr->getParent() != nullptr)
            {
                if(checkptr->getParent()->getRight() == checkptr)
                {
                    checkptr->getParent()->setRight(checkptr->getLeft());
                    checkptr->getLeft()->setParent(checkptr->getParent());
                }
                else if(checkptr->getParent()->getLeft() == checkptr)
                {
                    checkptr->getParent()->setLeft(checkptr->getLeft());
                    checkptr->getLeft()->setParent(checkptr->getParent());
                }
                // if(checkptr->getLeft() != nullptr)
                // {
                //     checkptr->getParent()->setRight(checkptr->getLeft());
                //     checkptr->getLeft()->setParent(checkptr->getParent());
                // }
                // else
                // {
                //     checkptr->getParent()->setLeft(nullptr);
                // }

                
            }
            else
            {
                checkptr->getLeft()->setParent(nullptr);
                root_ = checkptr->getLeft();

                
                
            }
            delete checkptr;

            return;
        }

        if(checkptr->getRight() != nullptr && checkptr->getLeft() == nullptr)
        {
            // nodeSwap(checkptr,predecessor(checkptr));

            if(checkptr->getParent() != nullptr)
            {
                if(checkptr->getParent()->getRight() == checkptr)
                {
                    checkptr->getParent()->setRight(checkptr->getRight());
                    checkptr->getRight()->setParent(checkptr->getParent());
                }
                else if(checkptr->getParent()->getLeft() == checkptr)
                {
                    checkptr->getParent()->setLeft(checkptr->getRight());
                    checkptr->getRight()->setParent(checkptr->getParent());
                }
                // if(checkptr->getRight() != nullptr)
                // {
                //     checkptr->getParent()->setRight(checkptr->getRight());
                //     checkptr->getRight()->setParent(checkptr->getParent());
                // }
                // else
                // {
                //     checkptr->getParent()->setRight(nullptr);
                // }

            }
            else
            {
                checkptr->getRight()->setParent(nullptr);
                root_ = checkptr->getRight();

                
                
            }
            delete checkptr;

            return;
            
        }

        if(checkptr->getLeft() != nullptr && checkptr->getRight() != nullptr)
        {
            // nodeSwap(checkptr,predecessor(checkptr));
            if(checkptr->getParent() != nullptr)
            {
                Node<Key,Value>* priorptr = predecessor(checkptr);
                nodeSwap(checkptr,priorptr);

                if(checkptr->getLeft() != nullptr)
                {
                    checkptr->getLeft()->setParent(checkptr->getParent());
                    if(checkptr->getParent()->getRight() == checkptr)
                    {
                        checkptr->getParent()->setRight(checkptr->getLeft());
                    }
                    else
                    {
                        checkptr->getParent()->setLeft(checkptr->getLeft());
                    }
                    
                }
                else
                {
                    if(checkptr->getParent()->getLeft() == checkptr)
                    {
                        checkptr->getParent()->setLeft(nullptr);
                    }
                    else
                    {
                        checkptr->getParent()->setRight(nullptr);
                    }

                    
                }
            }
            else
            {
                // predecessor(checkptr)->setParent(nullptr);
                Node<Key,Value>* priorptr = predecessor(checkptr);
                nodeSwap(checkptr,priorptr);


                if(checkptr->getParent()->getLeft() == checkptr)
                {
                    if(checkptr->getLeft() != nullptr)
                    {
                        checkptr->getParent()->setLeft(checkptr->getLeft());
                        checkptr->getLeft()->setParent(checkptr->getParent());
                    }
                    else
                    {
                        checkptr->getParent()->setLeft(nullptr);
                    }
                }
                if(checkptr->getParent()->getRight() == checkptr)
                {
                    if(checkptr->getLeft() != nullptr)
                    {
                        checkptr->getParent()->setRight(checkptr->getLeft());
                        checkptr->getLeft()->setParent(checkptr->getParent());
                    }
                    else
                    {
                        checkptr->getParent()->setRight(nullptr);
                    }
                    
                }
                
                root_ = priorptr;

                // cout<<"the root is ";
                // cout<<root_->getKey()<<" "<<root_->getValue()<<endl;

            }

            delete checkptr;

            return;
        }
    }

}


template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    if(current->getLeft() != nullptr)
    {
        Node<Key, Value>* temp = current->getLeft();

        while(temp->getRight() != nullptr)
        {
            temp = temp->getRight();
        }

        current = temp;

        return current;
    }
    else
    {
        Node<Key, Value>* temp = current->getParent();
        while(temp != nullptr && current == temp->getLeft())
        {
            // if(temp == temp->right_)
            // {
            //     return temp;
            // }
            current = temp;
            temp = temp->getParent();
        }

        current = temp;

        return current;

    }
    

}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    if(current->getRight() != nullptr)
    {
        Node<Key, Value>* temp = current->getRight();

        while(temp->getLeft() != nullptr)
        {
            temp = temp->getLeft();
        }

        current = temp;

        return temp;
    }
    else
    {
        Node<Key, Value>* temp = current->getParent();
        while(temp != nullptr && current == temp->getRight())
        {
            // if(temp == temp->parent_->left_)
            // {
                current = temp;

                // return current;
            // }
            temp = temp->getParent();

        }

        current = temp;

        return current;
    }

}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    clearhelp(root_);
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearhelp(Node<Key,Value>* start)
{
    // TODO
    if(start == nullptr)
    {
        return;
    }

    clearhelp(start->getLeft());
    clearhelp(start->getRight());
    delete start;
    root_ = nullptr;
    return;
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    Node<Key,Value>* start = root_;

    while(start != nullptr)
    {
        if(start->getLeft() == nullptr)
        {
            break;
        }
        start = start->getLeft();
    }

    return start;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    Node<Key,Value>* start = root_;

    while(start != nullptr)
    {
        if(key<start->getKey())
        {
            start = start->getLeft();
            continue;
        }
        if(key>start->getKey())
        {
            start = start->getRight();
            continue;
        }
        if(start->getKey() == key)
        {
            // return start;
            break;
        }
    }

    return start;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO

    if(root_ == nullptr)
    {
        return true;
    }

    int height_left = height(root_->getLeft());
	int height_right = height(root_->getRight());
    // cout<<height_left<< " "<<height_right<<endl;
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
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>:: height(Node<Key,Value>* l) const
{
    if(l== nullptr)
	{
		return 0;

	}
	else
	{
		int lheight = height(l->getLeft());
		int rheight = height(l->getRight());
        if(lheight == -1 || rheight == -1)
        {
            return -1;
        }
		if(abs(lheight-rheight) > 1)
		{
			return -1;
		}

		return std::max(lheight,rheight)+1;
	}
}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
