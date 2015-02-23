/********************************************************************
  Author:        Dana Vrajitoru, IUSB, CS
  Class:         C243, Spring 2012
  File name:     my_array.cc
  Last updated:  August 29, 2012.
  Description:   Implementation of a class that implements a safe array.
*********************************************************************/

#include "my_array.h"
#include <iostream>
using namespace std;
#include <cstdlib>
#include <ctime>

// Constructor with given size, can be used as default constructor.
My_array::My_array(int the_size)
{
  array = NULL;
  size = 0;
  resize(the_size);
}

// Destructor. If the array is not empty, it must be deallocated.
My_array::~My_array()
{
  empty();
}

// Copy constructor
My_array::My_array(My_array &data)
  : size(data.size)
{
  array = new int[size];
  for (int i=0; i<size; i++)
    array[i] = data.array[i];
}

// Assignment operator
My_array &My_array::operator=(My_array &data)
{
  if (this != &data) 
  {
    resize(data.size);
    for (int i=0; i<size; i++)
      array[i] = data.array[i];
  }
  else 
    cout << "Attempt to copy an object on itself. " 
	 <<"Operation ignored." << endl;
  return *this;
}

void My_array::empty()
{
  if (size != 0 && array != NULL) 
  {
    size = 0;
    delete [] array;
    array = NULL;
  }
}

// Resize the array.
void My_array::resize(int the_size)
{
  if (size >= 0) 
  {
    empty();
    if (the_size != 0) 
    {
      size = the_size;
      array = new int[size];
    }
  }
  else
    cout << "Resize attepmted with a negative size. "
	 << "Operation ignored." << endl;
}

// Access an element of the array. If the index (subscript) is out
// of the array, it prints an error message and exits the program.
int &My_array::operator[](int index)
{
  if (index >= 0 && index < size) 
    return array[index];
  else 
  {
    cerr << "Illegal access to an element of the array." << endl
	 << "The size of the array was " << size 
	 << " and the index was " << index << endl;
    exit(1);
  }
}

// Returns the size of the array.
int My_array::get_size()
{
  return size;
}

// Output the elements of the array.
void My_array::output()
{
  cout << "The array of size " << size 
       << " contains the elements:" << endl;
  for (int i=0; i<size; i++)
    cout << array[i] << ' ';
  cout << endl;
}

// We define this so that we can write "cout << a;" if a is an object
// of this class.
ostream &operator<<(ostream &out, My_array &data)
{
  out << "The array of size " << data.size 
      << " contains the elements:" << endl;
  for (int i=0; i<data.size; i++)
    out << data.array[i] << ' ';
  out << endl;
  return out;
}

//Allows the user to input the size of the array and input one element of the
//array at a time
void My_array::input()
{
  cout << "Enter the size of the array: ";
  cin >> size;
  
  resize(size);

  for (int i = 0; i < size; ++i)
  {
    cout << "Enter an element of the array: ";
    cin >> array[i];
  }
}

//Fills an array with random numbers between 0 and the limit given by the user
void My_array::randomize(int limit, int the_size)
{ 
  if (the_size != 0)
    resize(the_size);

  for (int i = 0; i < the_size; ++i)
    array[i] = rand() % (limit + 1);
}

 //Compares two arrays to see if they are equal
bool My_array::operator==(My_array &data)
{
  if (size != data.size)
    return false;

  for (int i = 0; i < size; ++i)
  {
    if (array[i] != data.array[i])
      return false;
  }

  return true;
}

//Compares two arrays to see if they are unequal
bool My_array::operator!=(My_array &data)
{
  return !(this -> operator==(data));
}

//Computes the Hamming distance between two arrays
int My_array::hamming(My_array &data)
{
  int distance = 0, shortest = size, longest = data.size;

  if (data.size < size)
  {
    shortest = data.size;
    longest = size;
  }

  for (int i = 0; i < shortest; ++i)
  {
    if (array[i] != data.array[i])
      ++ distance;
  }

  distance += (longest - shortest);
  return distance;
}
