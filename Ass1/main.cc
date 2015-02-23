/********************************************************************
  Author:        Dana Vrajitoru, IUSB, CS
  Class:         C243, Spring 2012
  File name:     main.cc
  Last updated:  August 29, 2012.
  Description:   Testing the class My_array.
*********************************************************************/

#include "my_array.h"
#include <iostream>
using namespace std;
#include <cstdlib>
#include <ctime>

int main()
{
  srand (time(NULL));

  const int RANDOM_LIMIT = 10;
  My_array first, second, third;

  first.input();
  second.randomize(RANDOM_LIMIT, first.get_size());
  third.randomize(RANDOM_LIMIT, first.get_size());

  if (first != second)
    cout << "The first and second arrays are not equal." << endl;
  else
    cout << "The first and second arrays are equal." << endl;

  cout << "The Hamming distance between the second and third arrays is "
       << second.hamming(third) << endl;
   
  return 0;
}
