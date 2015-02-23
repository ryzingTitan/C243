/*********************************************************************
  Author:        Dana Vrajitoru, IUSB, CS
  Class:         C243 Data Structures
  File name:     ListIterator.cc
  Last updated:  January 31, 2012
  Updated by:    Kyle Stoltzfus
  Description:   Definition of the list iterator class.
**********************************************************************/

#include "ListIterator.h"
#include <cstdlib>
#include <iostream>
using namespace std;

// Default constructor. We need to make sure the pointer is initialized
// to NULL.
ListIterator::ListIterator()  
 : current(NULL)
{}

// Constructor from a ListNode pointer.
ListIterator::ListIterator(ListNode *link)
{
  current = link;
}

// Assignment operator with a ListNode pointer
ListNode *ListIterator::operator=(ListNode *link)
{
  current = link;
  return current;
}

// Operator to advance the pointer.
ListIterator &ListIterator::operator++()
{
  if (current) 
    current = current->next;
  return *this;
}

// Operator to access the content of the node. If the pointer is null, 
// it exits the program with an error message.
int &ListIterator::operator*()
{
  if (current)
    return current->datum;
  else 
  {
    cerr << "Attempting to dereference an empty iterator" << endl;
    exit(1);
  }
}

// Operator to check if the pointer is not null.
ListIterator::operator bool()
{
  return (current != NULL);
}

// Operator to convert to a ListNode_ptr.
ListIterator::operator ListNodePtr()
{
  return current;
}

// Swaps the content of the target object with the other iterator if
// they are both not null. If one of them is null the function returns
// false, otherwise true.
bool ListIterator::swap(ListIterator &other)
{
  if (current && other) 
  {
    int temp = current->datum;
    current->datum = *other;
    *other = temp;
    return true;
  }
  else
    return false;
}

// Comparison operator.
bool ListIterator::operator==(ListIterator &data)
{
  return (current == data.current);
}

// Functions to be implemented by the student.

// It locates the minimum in the list starting from the target object
// and returns a list iterator containing a pointer to this node.
ListIterator ListIterator::min()
{
  ListIterator min = current, search = current -> next;

  while (search) //search is used so that the pointer in the ListIterator
                //that called this function will not be changed
  {
    if (*min > *search)
      min = search;

    ++ search;
  }

  return min;
}

// This operator should move the iterator forward by a number of nodes
// indicated by the parameter. If there are not enough nodes to skip
// that many steps forward, the current pointer should be made NULL.
ListIterator &ListIterator::moveForward(int steps)
{
  while (current && steps > 0)
  {
    current = current -> next;
    -- steps;
  }

  if (steps != 0)
    current = NULL;

  return *this;
}
