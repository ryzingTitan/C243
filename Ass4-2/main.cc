/************************************************************
Program: main.cc
Author:  Kyle Stoltzfus
Date:    February 21, 2013

This program is a simple reverse polish notation (postfix) 
calculator. The input is read in from the file name provided as
a command line argument. THIS PROGRAM ONLY WORKS FOR STRINGS LESS
THAN 40 CHARACTERS INCLUDING THE NEWLINE. If longer strings
are being used, the constant MAX_SIZE must be changed.
 ***********************************************************/

#include <fstream>
#include <cctype>
#include <stack>
#include <iostream>
using namespace std;

bool computations (stack <int> &, char, int &);
bool evaluate (char [], int &);

int main(int argc, char *argv[])
{
  const int MAX_SIZE = 40;
  int solution = 0;
  bool valid = true;
  ifstream FileIn;
  char Input[MAX_SIZE]; //array will store 39 elements and null terminator

  FileIn.open(argv[1]);

  if (FileIn.fail())
  {
    cout << "File could not be opened. Program will now exit." << endl;
    return 0;
  }
  
  while (!FileIn.eof() && FileIn.good())
  {
    for(int i = 0; i < MAX_SIZE; ++i)
      Input[i] = NULL;       //makes sure the array is empty

    FileIn.getline(Input, MAX_SIZE);
    
    if (Input[0] != NULL) //makes sure array contains usable data
    {
      valid = evaluate(Input, solution);
    
      if (valid == true)
	cout << "The answer is "<< solution << endl;
    
      else
	cout << "Invalid reverse polish expression." << endl;
    }
  } 

  FileIn.close();

  return 0;
} 

/**********************evaluate********************************
Input: The null terminating char array Input containing a line from the file
being processed.
Output: The final answer from the operations as a reference parameter. 
Returns: A boolean value. It will return true if the input is a valid
reverse polish expression and false if it is invalid.

This function takes a line of data from the file and evaluates it.
All whitespaces are skipped. If a digit is encountered, it is converted
from a char to an int by subtracting the char '0' from it. This int
is then pushed on to the top of the stack data. If an operator is
encountered, the function computations is called to handle it. Before
finishing, this function checks to make sure that no extra digits 
are on the stack that all the digits in the stack have been used.
If either of these conditions is true, the function returns the 
bool value false to indicate the expression being evaluated is 
invalid.
 ***************************************************************/
bool evaluate (char Input[], int & answer)
{
   bool successful = true;
   stack <int> data;

   for (int i = 0; Input[i] != NULL; ++i)
   { 
     while (isspace(Input[i]))
       ++ i;

     if (isdigit(Input[i]))
	data.push( int(Input[i] - '0'));

     if (Input[i] == '+'|| Input[i] == '-'|| Input[i] == '*'|| Input[i] == '/')
     {
       successful = computations(data, Input[i], answer);
       data.push(answer);
     }
   }

   if (data.top() != answer)
     successful = false;  //makes sure there are no extra digits
   
   data.pop(); //takes the answer off the stack
   
   if (!data.empty())  //makes sure there are no unused digits
     successful = false;

   return successful;
}

/******************computations***********************************
Input: The stack data that contains the digits that evaluate has found
in the file.
The char operators containing the operator to be used for the computation.
Output: The result of the computation passed back as a reference parameter.
Returns: A boolean value. This function will return true if the computation
was successful and false if it failed. It will only return false when
the stack data does not contain enough elements to perform the operations
(less than 2 elements).

This function performs mathematical operations on the elements stored
in the stack data. THIS FUNCTION CAN ONLY PROCESS THESE OPERATORS: +,
-, /, *. This function will first check to make sure there are enough
elements in the stack to perform the operation. It will then take the 
top element and place it on the right hand side of the operator. It
pops this element off the stack and then places the next element in 
the stack on the left hand side of the operator. It then stores the 
answer in result and passes it back to the function evaluate.   
 *****************************************************************/
bool computations(stack <int> & data, char operators, int & result)
{
  int first, second;

  if (data.empty())
    return false;

  second = data.top();
  data.pop();

  if (data.empty())
    return false;

  first = data.top();
  data.pop();

  if (operators == '+')
    result = first + second;

  if (operators == '-')
    result = first - second;
  
  if (operators == '*')
    result = first * second;
  
  if (operators == '/')
    result = first / second;

  return true;
}
    
