#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

// using namespace std;

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void addAVLNode(AVLNode<Key, Value>* val,const std::pair<const Key, Value> &keyValuePair,AVLNode<Key, Value>* prev);
    void RotateRight(AVLNode<Key,Value>* ptr);
    void RotateLeft(AVLNode<Key,Value>* ptr);
    void InsertFix(AVLNode<Key,Value>* ptr, AVLNode<Key,Value>* ptr1);
    void RemoveFix(AVLNode<Key,Value>* n, int8_t diff);

};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    addAVLNode(static_cast<AVLNode<Key, Value>*>(this->root_),new_item,nullptr);
    
}

template<class Key, class Value>
void AVLTree<Key, Value>::addAVLNode(AVLNode<Key, Value>* val,const std::pair<const Key, Value> &keyValuePair,AVLNode<Key, Value>* prev)
{
    if(val == nullptr)
    {
        AVLNode<Key, Value>* newOne = new AVLNode<Key, Value>(keyValuePair.first,keyValuePair.second,prev);
        this->root_ = newOne;
        return;
    }
    else if(keyValuePair.first < val->getKey())
    {
        if(val->getLeft() == nullptr)
        {
            AVLNode<Key, Value>* newOne = new AVLNode<Key, Value>(keyValuePair.first,keyValuePair.second,prev);
            val->setLeft(newOne);
            newOne->setParent(val);
            if(newOne->getParent()->getBalance() == 1)
            {
                newOne->getParent()->setBalance(0);
                return;
            }
            if(newOne->getParent()->getBalance() == -1)
            {
                newOne->getParent()->setBalance(0);
                return;
            }
            newOne->getParent()->updateBalance(-1);
            InsertFix(newOne->getParent(),newOne);
            return;
        }
        prev = val;
        addAVLNode(val->getLeft(),keyValuePair,prev);

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
            AVLNode<Key, Value>* newOne = new AVLNode<Key, Value>(keyValuePair.first,keyValuePair.second,prev);
            val->setRight(newOne);
            newOne->setParent(val);
            if(newOne->getParent()->getBalance() == 1)
            {
                newOne->getParent()->setBalance(0);
                return;
            }
            if(newOne->getParent()->getBalance() == -1)
            {
                newOne->getParent()->setBalance(0);
                return;
            }
            newOne->getParent()->updateBalance(1);
            InsertFix(newOne->getParent(),newOne);
            return;
        }                          
        prev = val;
        addAVLNode(val->getRight(),keyValuePair,prev);
    }
    else
    {
        val->setValue(keyValuePair.second);
        return;
    }


}


/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    int8_t diff_ = -2;
    Node<Key,Value>* checkptr = this->internalFind(key);
   
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
                Node<Key,Value>* parent = checkptr->getParent();
                if(checkptr == checkptr->getParent()->getLeft())
                {
                    diff_ = 1;
                    // static_cast<AVLNode<Key, Value>*>(parent)->updateBalance(diff_);
                    checkptr->getParent()->setLeft(nullptr);

                    delete checkptr;

                    

                    RemoveFix(static_cast<AVLNode<Key, Value>*>(parent),diff_);

                    return;

                }

                if(checkptr == checkptr->getParent()->getRight())
                {
                    diff_ = -1;

                    // static_cast<AVLNode<Key, Value>*>(parent)->updateBalance(diff_);

                    cout<<"The key "<<static_cast<AVLNode<Key, Value>*>(parent)->getKey()<<" balance "<<(int)(static_cast<AVLNode<Key, Value>*>(parent)->getBalance())<<endl;

                    checkptr->getParent()->setRight(nullptr);

                    delete checkptr;

                    

                    RemoveFix(static_cast<AVLNode<Key, Value>*>(parent),diff_);

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

                this->root_ = nullptr;
                
                delete checkptr;

                return;
            }

        }

        if(checkptr->getLeft() != nullptr && checkptr->getRight() == nullptr)
        {
            // nodeSwap(checkptr,predecessor(checkptr));

            if(checkptr->getParent() != nullptr)
            {
                Node<Key,Value>* parent = checkptr->getParent();
                if(checkptr->getParent()->getRight() == checkptr)
                {
                    diff_ = -1;
                    checkptr->getParent()->setRight(checkptr->getLeft());
                    checkptr->getLeft()->setParent(checkptr->getParent());

                    // static_cast<AVLNode<Key, Value>*>(parent)->updateBalance(diff_);
                }
                else if(checkptr->getParent()->getLeft() == checkptr)
                {
                    diff_ = 1;
                    checkptr->getParent()->setLeft(checkptr->getLeft());
                    checkptr->getLeft()->setParent(checkptr->getParent());

                    // static_cast<AVLNode<Key, Value>*>(parent)->updateBalance(diff_);
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

                delete checkptr;

                RemoveFix(static_cast<AVLNode<Key, Value>*>(parent),diff_);

                return;
            }
            else
            {
                checkptr->getLeft()->setParent(nullptr);
                this->root_ = checkptr->getLeft();

                
                
            }
            delete checkptr;

            return;
        }

        if(checkptr->getRight() != nullptr && checkptr->getLeft() == nullptr)
        {
            // nodeSwap(checkptr,predecessor(checkptr));

            if(checkptr->getParent() != nullptr)
            {
                Node<Key,Value>* parent = checkptr->getParent();
                if(checkptr->getParent()->getRight() == checkptr)
                {
                    diff_ = -1;
                    checkptr->getParent()->setRight(checkptr->getRight());
                    checkptr->getRight()->setParent(checkptr->getParent());

                    // static_cast<AVLNode<Key, Value>*>(parent)->updateBalance(diff_);
                }
                else if(checkptr->getParent()->getLeft() == checkptr)
                {
                    diff_ = 1;
                    checkptr->getParent()->setLeft(checkptr->getRight());
                    checkptr->getRight()->setParent(checkptr->getParent());

                    // static_cast<AVLNode<Key, Value>*>(parent)->updateBalance(diff_);
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
                delete checkptr;

                RemoveFix(static_cast<AVLNode<Key, Value>*>(parent),diff_);

                return;

            }
            else
            {
                checkptr->getRight()->setParent(nullptr);
                this->root_ = checkptr->getRight();

                
                
            }
            delete checkptr;

            return;
            
        }

        if(checkptr->getLeft() != nullptr && checkptr->getRight() != nullptr)
        {
            // nodeSwap(checkptr,predecessor(checkptr));
            if(checkptr->getParent() != nullptr)
            {
                Node<Key,Value>* priorptr = this->predecessor(checkptr);
                nodeSwap(static_cast<AVLNode<Key, Value>*>(checkptr),static_cast<AVLNode<Key, Value>*>(priorptr));

                Node<Key,Value>* parent = checkptr->getParent();

                if(checkptr->getLeft() != nullptr)
                {
                    checkptr->getLeft()->setParent(checkptr->getParent());
                    if(checkptr->getParent()->getRight() == checkptr)
                    {
                        diff_ = -1;
                        checkptr->getParent()->setRight(checkptr->getLeft());
                    }
                    else
                    {
                        diff_ = 1;
                        checkptr->getParent()->setLeft(checkptr->getLeft());
                    }
                    
                }
                else
                {
                    if(checkptr->getParent()->getLeft() == checkptr)
                    {
                        diff_ = 1;
                        checkptr->getParent()->setLeft(nullptr);
                    }
                    else
                    {
                        diff_ = -1;
                        checkptr->getParent()->setRight(nullptr);
                    }

                    
                }

                delete checkptr;

                RemoveFix(static_cast<AVLNode<Key, Value>*>(parent),diff_);

                return;
            }
            else
            {
                // predecessor(checkptr)->setParent(nullptr);
                Node<Key,Value>* priorptr = this->predecessor(checkptr);
                nodeSwap(static_cast<AVLNode<Key, Value>*>(checkptr),static_cast<AVLNode<Key, Value>*>(priorptr));

                Node<Key,Value>* parent = checkptr->getParent();


                if(checkptr->getParent()->getLeft() == checkptr)
                {
                    diff_ = 1;
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
                    diff_ = -1;
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
                
                this->root_ = priorptr;

                // cout<<"the root is ";
                // cout<<root_->getKey()<<" "<<root_->getValue()<<endl;

                delete checkptr;

                RemoveFix(static_cast<AVLNode<Key, Value>*>(parent),diff_);

                return;

            }

            // delete checkptr;

            // return;
        }
    }
}
template<class Key, class Value>
void AVLTree<Key, Value>::InsertFix(AVLNode<Key,Value>* in, AVLNode<Key,Value>* ptr1)
{
    if(in == nullptr || in->getParent() == nullptr)
    {
        return;
    }
    AVLNode<Key,Value>* gparent = in->getParent();
    if(in == in->getParent()->getLeft())
    {
        gparent->updateBalance(-1);

        if(gparent->getBalance() == 0)
        {
            return;

        }
        if(gparent->getBalance() == -1)
        {
            InsertFix(gparent,in);
        }
        if(gparent->getBalance() == -2)
        {
            if(ptr1 == in->getLeft())
            {
                RotateRight(gparent);
                in->setBalance(0);
                gparent->setBalance(0);
            }
            else
            {

                RotateLeft(in);
                RotateRight(gparent);

                if(ptr1->getBalance() == -1)
                {
                    in->setBalance(0);
                    gparent->setBalance(1);
                    ptr1->setBalance(0);
                    return;

                }

                if(ptr1->getBalance() == 0)
                {
                    in->setBalance(0);
                    gparent->setBalance(0);
                    ptr1->setBalance(0);
                    return;

                }

                if(ptr1->getBalance() == 1)
                {
                    in->setBalance(-1);
                    gparent->setBalance(0);
                    ptr1->setBalance(0);
                    return;

                }
            }
        }
    }
    else if(in == in->getParent()->getRight())
    {
        gparent->updateBalance(1);

        if(gparent->getBalance() == 0)
        {
            return;

        }
        if(gparent->getBalance() == 1)
        {
            InsertFix(gparent,in);
        }
        if(gparent->getBalance() == 2)
        {
            if(ptr1 == in->getRight())
            {
                RotateLeft(gparent);
                in->setBalance(0);
                gparent->setBalance(0);
            }
            else
            {

                RotateRight(in);
                RotateLeft(gparent);

                if(ptr1->getBalance() == 1)
                {
                    in->setBalance(0);
                    gparent->setBalance(-1);
                    ptr1->setBalance(0);
                    return;
                }

                if(ptr1->getBalance() == 0)
                {
                    in->setBalance(0);
                    gparent->setBalance(0);
                    ptr1->setBalance(0);
                    return;

                }

                if(ptr1->getBalance() == -1)
                {
                    in->setBalance(1);
                    gparent->setBalance(0);
                    ptr1->setBalance(0);
                    return;

                }
            }
        }
        
    }

    
}

template<class Key, class Value>
void AVLTree<Key, Value>::RemoveFix(AVLNode<Key,Value>* n, int8_t diff)
{
    int8_t ndiff = -2;
    if(n == nullptr)
    {
        return;
    }

    AVLNode<Key,Value>* np = n->getParent();

    if(np != nullptr)
    {
        if(n == np->getLeft())
        {
            ndiff = 1;
        }
        else
        {
            ndiff = -1;
        }
    }
    // else
    // {
    //     n->updateBalance(diff);
    //     return;
    // }

    if(diff == -1)
    {
        if(n->getBalance() + diff == -2)
        {
            AVLNode<Key,Value>* c = n->getLeft();

            if(c->getBalance() == -1)
            {
                RotateRight(n);
                n->setBalance(0);
                c->setBalance(0);
                RemoveFix(np,ndiff);
            }
            else if(c->getBalance() == 0)
            {
                RotateRight(n);
                n->setBalance(-1);
                c->setBalance(1);
                return;
            }
            else if(c->getBalance() == 1)
            {
                AVLNode<Key,Value>* g = c->getRight();
                RotateLeft(c);
                RotateRight(n);

                if(g->getBalance() == 1)
                {
                    n->setBalance(0);
                    c->setBalance(-1);
                    g->setBalance(0);
                }
                else if(g->getBalance() == 0)
                {
                    n->setBalance(0);
                    c->setBalance(0);
                    g->setBalance(0);

                }
                else if(g->getBalance() == -1)
                {
                    n->setBalance(1);
                    c->setBalance(0);
                    g->setBalance(0);

                }
                RemoveFix(np,ndiff);

            }
        }
        else if(n->getBalance() + diff == -1)
        {
            n->setBalance(-1);
            return;
        }
        else if(n->getBalance() + diff == 0)
        {
            n->setBalance(0);
            RemoveFix(np,ndiff);
        }
    }
    if(diff == 1)
    {
        if(n->getBalance() + diff == 2)
        {
            AVLNode<Key,Value>* c = n->getRight();

            if(c->getBalance() == 1)
            {
                RotateLeft(n);
                n->setBalance(0);
                c->setBalance(0);
                RemoveFix(np,ndiff);
            }
            else if(c->getBalance() == 0)
            {
                RotateLeft(n);
                n->setBalance(1);
                c->setBalance(-1);
                return;
            }
            else if(c->getBalance() == -1)
            {
                AVLNode<Key,Value>* g = c->getLeft();
                RotateRight(c);
                RotateLeft(n);

                if(g->getBalance() == -1)
                {
                    n->setBalance(0);
                    c->setBalance(1);
                    g->setBalance(0);

                }
                else if(g->getBalance() == 0)
                {
                    n->setBalance(0);
                    c->setBalance(0);
                    g->setBalance(0);

                }
                else if(g->getBalance() == 1)
                {
                    n->setBalance(-1);
                    c->setBalance(0);
                    g->setBalance(0);

                }

                RemoveFix(np,ndiff);

            }

        }
        else if(n->getBalance() + diff == 1)
        {
            n->setBalance(1);
            return;

        }
        else if(n->getBalance() + diff == 0)
        {
            n->setBalance(0);
            RemoveFix(np,ndiff);
        }


    }


}

template<class Key, class Value>
void AVLTree<Key, Value>:: RotateRight(AVLNode<Key,Value>* ptr)
{
    // cout<<ptr->getKey()<<" "<<ptr->getValue()<<endl;
    
    AVLNode<Key,Value>* temp = ptr->getLeft();
    
    if(ptr->getParent() != nullptr)
    {
        if(ptr == ptr->getParent()->getLeft())
        {
            ptr->getParent()->setLeft(temp);
        }
        else
        {
            ptr->getParent()->setRight(temp);
        }
    }

    if(ptr->getParent() == nullptr)
    {
        this->root_ = temp;
    }

    // ptr->setParent(ptr->getParent()->getParent());

    temp->setParent(ptr->getParent());

    ptr->setParent(temp);

    if(temp->getRight() != nullptr)
    {
        ptr->setLeft(temp->getRight());
        temp->getRight()->setParent(ptr);
    }
    else
    {
        ptr->setLeft(nullptr);
    }

    // if(ptr->getRight() != nullptr)
    // {
    //     temp->setRight(ptr->getRight());
    //     ptr->getRight()->setParent(temp);
    // }
    // temp->setParent(ptr);
    // ptr->setRight(temp);
    temp->setRight(ptr);
    
    
    
}

template<class Key, class Value>
void AVLTree<Key, Value>:: RotateLeft(AVLNode<Key,Value>* ptr)
{
    AVLNode<Key,Value>* temp = ptr->getRight();
    
    if(ptr->getParent() != nullptr)
    {
        if(ptr == ptr->getParent()->getLeft())
        {
            ptr->getParent()->setLeft(temp);
        }
        else
        {
            ptr->getParent()->setRight(temp);
        }
    }
    if(ptr->getParent() == nullptr)
    {
        this->root_ = temp;
    }

    temp->setParent(ptr->getParent());

    ptr->setParent(temp);
    

    if(temp->getLeft() != nullptr)
    {
        ptr->setRight(temp->getLeft());
        temp->getLeft()->setParent(ptr);
    }
    else
    {
        ptr->setRight(nullptr);
    }

    temp->setLeft(ptr);


}



template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
