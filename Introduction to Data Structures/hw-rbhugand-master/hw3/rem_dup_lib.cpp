#include <iostream>
#include "rem_dup_lib.h"
using namespace std;

// Add your implementations below
void removeConsecutive(Item* head)
{
    if(head == nullptr)
    {
        return;
    }
    else if(head->next != nullptr && head->val == head->next->val)
    {
        Item* temp = head->next;
        head->next = head->next->next;
        delete temp;
        removeConsecutive(head);
    }
    else
    {
        removeConsecutive(head->next);
    }
}

Item* concatenate(Item* head1, Item* head2)
{
    if(head1== nullptr && head2 == nullptr)
    {
        return nullptr;

    }
    if(head1 == nullptr)
    {
        return new Item(head2->val,concatenate(nullptr,head2->next));
    }
    else
    {
        return new Item(head1->val,concatenate(head1->next,head2));

    }
}