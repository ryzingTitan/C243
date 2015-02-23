// Adapted from Savitch, 5th ed., pp. 881-882.
/***************************************************
Modified by: Kyle Stoltzfus
Date : 	  February 21, 2013

This program uses a stack and a queue to determine if 
a word is a palindrome. It stores the word entered by 
the user into a stack and a queue. It then compares the 
elements in the stack and queue. If all the elements are
equal, the word is a palindrome.
***************************************************/
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

int main()
{
  stack<char> s;
  queue<char> q;
  char next;
  bool isPalindrome = true;

  cout << "Enter a line of text:\n";
  cin.get(next);

  while (next != '\n') 
  {
    s.push(next);  // for stacks, add new item on top
    q.push(next);  // for queues, add new item at back
    
    cin.get(next);
  }

  while (!s.empty() && isPalindrome != false) 
  {
    // With STL, pop doesn't return the top element,
    // it simply removes it from the stack.
    // So, we need to use the supplied top method
    // to access the top element before removing it.
    if (s.top() != q.front())
    {
      isPalindrome = false;
    }

    else
      {
	s.pop();
	q.pop();
      }
  }

  if (isPalindrome == true)
    cout << "This is a palindrome.";
  
  else
    cout << "This is not a palindrome.";

  cout << endl;

  return 0;
}

