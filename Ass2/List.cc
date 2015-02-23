/*********************************************************************
  Author:        Dana Vrajitoru, IUSB, CS
  Class:         C243 Data Structures
  File name:     List.cc
  Last updated:  January 31, 2013
  Updated by:    Kyle Stoltzfus
  Description:   Implementation of a container class for a list.

**********************************************************************/

#include <iostream>
using namespace std;

#include "general.h"
#include "List.h"

// Default constructor.
List::List()
  : head(NULL), tail(NULL), size(0)
{}

// Copy constructor. The target object should be assigned a hard copy
// of the list contained in the data object.
List::List(const List &data)
  : head(NULL), tail(NULL), size(0)
{
  *this = data;
}

// Destructor.
List::~List()
{
  makeEmpty();
}

// Assignment operator. It must also make a hard copy of the
// list. Make sure that the tail of the target object is also set
// correctly.
List &List::operator=(const List &data)
{
  if (this != &data) 
  {
    size = data.size;
    head = data.head->copy();
    tail = head->lastNode();
  }
  return *this; 
}

// Returns the size of the list.
int List::getSize()
{
  return size;
}

// Inserts a new node with the specified content at the front of the
// list. It must make sure to update both the head and the tail of the
// list if need be.
void List::insertFront(int number)
{
  ListNodePtr newNode = new ListNode(number, head);
  testAllocation(newNode);
  size++;
  head = newNode;
  if (size == 1)
    tail = newNode;
}

// Checks if the list is empty.
bool List::isEmpty()
{
  return (size == 0);
}

// Converts to boolean. It must return true if the list is not empty,
// and false if it is.
List::operator bool()
{
  return !isEmpty();
}

// Deletes the entire list and reset all the data.
void List::makeEmpty()
{
  if (size) 
  {
    deleteList(head);
    head = NULL;
    tail = NULL;
    size = 0;
  }
}

// Difference operator - it must compare the content of the two lists
// and not just the pointers to them.
bool List::operator!=(const List &data)
{
  return !(*this == data);
}

// Concatenates the second list to the first and empties the second
// list.
void List::concatenate(List &data)
{
  if (head != data.head) 
  {
    if (head) 
    {
      tail->concatenate(data.head);
      size += data.size;
      if (data.tail)
        tail = data.tail;
    }
    else 
    {
      head = data.head;
      size = data.size;
      tail = data.tail;
    }
    if (data) 
    {
      data.size = 0;
      data.head=NULL;
      data.tail=NULL;
    }
  }
  else
    cout << "Attepmt to concatenate a list to itself. "
	 << "Operation ignored." << endl;
}
  
// Prints the last node in the list: the tail.
void List::printLast()
{
  if (tail) 
    cout << "The last node in the list contains " 
	 << tail->datum << endl;
  else
    cout << "The list is empty, it has no last node" << endl;
}

/*******************************************************************/
// Functions using list iterators.

// Begining of the list returned as a list iterator.
ListIterator List::begin()
{
  return ListIterator(head); 
}

// End of the list returned as a list iterator.
ListIterator List::end()
{
  return ListIterator(tail);
}

// Prints the list. We also want to know how many node are there in
// the list and if the list is empty.  I have rewriten this function
// using list iterators.
void List::print()
{
  cout << "The list has " << size << " nodes." << endl;
  if (size) 
  {
    cout << "Here are the nodes of the list:" << endl;
    ListIterator iter(head);
    while (iter) 
    {
      cout << *iter << ' ';
      ++iter;
    }
    cout << endl;
  }
}

// Finds the given number in the list and return a list iterator
// containing a pointer to the node containing the number in
// question. If the number is not in the list, it returns an iterator   
// where the pointer current is NULL.
ListIterator List::locate(int number)
{
  ListIterator locator = begin();
  while (locator && *locator != number)
    ++locator;
  return locator;
}

// The bubble sort using list iterators.
void List::bubbleSort()
{
  if (head) 
  {
    bool ordered = false;
    ListIterator iter1, iter2;
    while (!ordered) 
    {
      ordered = true;
      iter1 = head;
      iter2 = head->next;
      while (iter2) 
      {
	if (*iter1 > *iter2) 
        {
	  iter1.swap(iter2);
	  ordered = false;
	}
	++iter1;
	++iter2;
      }
    }
  }
}

/*******************************************************************/
// Functions to be written by the student. 


// Comparison operator - it must compare the content of the two
// lists and not just the pointers to them.
bool List::operator==(const List &data)
{
  if (size != data.size)
    return false;
 
  if (size == 0 && data.size == 0)
    return true;

  ListIterator iter1 = head, iter2 = data.head;

  while (iter1)
  {
    if (*iter1 == *iter2)
    {
      ++ iter1;
      ++ iter2;
    }
    
    else
      return false;
  }

  return true;
}


// Inserts a new node with the specified content at the back of the
// list. The code must be supplied by the student.
void List::insertBack(int number)
{
  ListNodePtr newNode = new ListNode(number);
  testAllocation(newNode);
  ++size;

  if (size == 1)
  {
    head = newNode;
    tail = newNode;
  }

  else
  {
    tail -> next = newNode;
    tail = newNode;
  }
}

// Checks if the list is in ascending order.
bool List::isOrdered()
{
  if (size == 0)
    return false;

  if (size == 1)
    return true;

  ListIterator iter1 = head, iter2 = head -> next;

  while (iter2)
  {
    if (*iter1 < *iter2)
    {
      ++ iter1;
      ++ iter2;
    }

    else 
      return false;
  }

  return true;
}

// Counts the number of negative values in the list. If the list is
// empty, just return 0.
int List::countNegative()
{
  ListIterator search = head;
  int negatives = 0;

  while (search)
  {
    if (*search < 0)
      ++ negatives;
 
    ++ search;
  }

  return negatives;
}  

// Removes the front node from the list and delete the memory for the
// node to be removed. The function should return true if the list is
// not empty, and false if the list is already empty. The head and the
// tail (!) of the list should be updated correctly.  THIS DOES NOT
// NEED TO USE ITERATORS.
bool List::removeFront()
{
  if (size == 0)
    return false;

  ListNodePtr nodeToDelete = head;

  -- size;
  
  if (size == 0)
  {
    head = NULL;
    tail = NULL;
  }

  else
    head = nodeToDelete -> next;

  delete nodeToDelete;
  return true;
}

// This function computes the sum of all the numbers stored in the
// list. It should be implemented using list iterators.
int List::sum()
{
  ListIterator iter = head;
  int sum = 0;

  while (iter)
  {
    sum += *iter;
    ++ iter;
  }

  return sum;  
}

// Returns the element i of the list in the form of a list iterator,
// where i=0 returns the first node of the list. If the list has less
// than i+1 nodes, then it should return a null iterator. Use the
// function move_forward from the class ListIterator.
ListIterator List::nodeAtPosition(int location)
{
  // This is what the function will return if location is 0. 
  ListIterator start = begin();
  -- location;

  if (location == 0)
    return start;

  start.moveForward(location);
  return start;
}

// This function should implement the selection sort on a list using
// list iterators.It should have an iterator scanning the list but
// stopping before the last node. For every position in the list, it
// would have to find the location of the minimal number in the list
// using a call to the appropriate function from the
// list_iterator. Then if the location of the minimum is not the same
// as the current node, swap the value of the current node with the
// minimum.
void List::selectionSort()
{
  if (head)
  {
    ListIterator min, sorted = head;
    
    while (sorted != tail)
    {  
      min = sorted.min();
     
     if (*sorted > *min)
       sorted.swap(min);

     ++ sorted;
    }
  }
}
