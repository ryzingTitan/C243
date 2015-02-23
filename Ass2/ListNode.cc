/*********************************************************************
  Author:        Dana Vrajitoru, IUSB, CS
  Class:         C243 Data Structures
  File name:     ListNode.cc
  Last updated:  September 6, 2012
  Description:   Implementation of a class that implements a list node 
                 containing an integer.
**********************************************************************/

#include <iostream>
using namespace std;

#include "ListNode.h"

// Constructor with the number only; it can be used as a default too.
ListNode::ListNode(const int number) 
  :datum(number), next(NULL)
{}

// Constructor with both the number and the next pointer.
ListNode::ListNode(const int number, ListNode *link)
  :datum(number), next(link)
{}

// Destructor.  We don't delete the entire list here because we may
// want to be able to delete individual nodes without deleting the
// entire list attached to them.
ListNode::~ListNode()
{}

// Copy constructor. It makes a soft copy of the node - the list
// starting from the pointer next is not copied. The next pointer in
// the target object will contain the same value as the pointer next
// in the data object, meaning that this node points into the list
// starting with data.
ListNode::ListNode(const ListNode &data)
  :datum(data.datum), next(data.next)
{}

// Set and get the private attributes.
// Get the value of the datum. Accessor method.
int ListNode::getDatum()
{
  return datum;
}

// Set the value of the datum.
void ListNode::setDatum(const int number)
{
  datum = number;
}

// Get the value of next. Accessor method.
ListNode *ListNode::getNext()
{
  return next;
}

// Set the value of next.
void ListNode::setNext(ListNode *link)
{
  next = link;
}

// Assignment operator. It makes a soft copy of the node - the next
// pointer is not copied.
ListNode &ListNode::operator=(const ListNode &data)
{
  if (&data != this) 
  {
    datum = data.datum;
    next = data.next;
  }
  return *this;
}

// Hard copy of a list starting from the target object.
/* Alternative recursive version
ListNode *ListNode::copy() 
{
  ListNode *new_node = new ListNode(*this);
  if (next)
    new_node->next = next->copy();
  return new_node;
}
*/
ListNode *ListNode::copy() 
{
  ListNode *p, *temp, *tail=NULL, *head = NULL;
  p = this; 
  while (p) 
  {
    temp = new ListNode(p->datum);
    if (head) 
    { 
      tail->next = temp; 
      tail = temp;
    }
    else 
      head = tail = temp;
    p = p->next;
  }
  return head;
}

// Concatenate a whole list at the end of the list starting from the
// target object.
/* Alternative recursive version
void ListNode::concatenate(ListNode *link)
{
  if (!next) // this is the last node in the list
    next = link;
  else
    next->concatenate(link);
}
*/
void ListNode::concatenate(ListNode *link)
{
  if (this == link) 
  {
    cout << "Attempt to concatenate a list to itself; operation aborted."
         << endl;
    return;
  }
  ListNode *p = lastNode(); // calling this from the target object.
  if (p) 
    p->next = link;
}

// Delete the entire list starting from the target object.
void deleteList(ListNode *head)
{
  ListNode *temp;
  while (head) 
  {
    temp = head;
    head = head->next;
    delete temp;
  }
}

// Returns the last node in a list starting from the target object.
ListNode *ListNode::lastNode()
{
  ListNode *p = this;
  while (p && p->next)
    p = p->next;
  return p;
}
