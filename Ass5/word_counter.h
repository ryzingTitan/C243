/*********************************************************************
  Author:        Dana Vrajitoru, IUSB, CS
  Class:         C243 Data Structures
  File name:     word_counter.h
  Last updated:  October 11, 2007

  Description:   Definition of the class word_counter.
**********************************************************************/

#ifndef  WORD_COUNTER_H
#define  WORD_COUNTER_H

#include <string> // contains a definition of a "string" data type that's
                  // easier to use than standard C/C++ strings
                  // It requires the namespace std.
#include <iostream>
using namespace std;

class Word_counter
{
 private:
  
  string word;
  int  count;

 public:
  // Constructor with default values for both parameters. By default
  // if we don't specify how many occurences of a word we have, we'll
  // assume that we have at least one, otherwise we wouldn't need to
  // store the word at all.
  Word_counter (string s = "", int n = 1); 

  // Constructor with the word specified as a regular array of
  // characters (c string).
  Word_counter (char *s, int n = 1); 

  // Verify if the word stored in this object is equal to that string.
  bool contains(char *s);

  // Verify if the word stored in this object is equal to that string.
  bool contains(string s);
  
  // If we need to reset these values later.
  void set_word(string s);  
  void set_word(char *s);  
  void set_count(int n = 1);
  
  // Add 1 to the count.
  void increment();

  // If we want to compare two word counters. These will compare the
  // two strings (words) alphabetically.
  int operator<  (const Word_counter &y);
  int operator<= (const Word_counter &y);
  int operator>  (const Word_counter &y);
  int operator>= (const Word_counter &y);
  
  // Comparison operators.
  bool operator== (const Word_counter &y) const;
  bool operator!= (const Word_counter &y) const;

  // To be used in a table.
  friend string key (const Word_counter & x);
  
  // Easy output of the word counter.
  friend ostream & operator<< (ostream & output, 
			       const Word_counter & x);
};


#endif
