/*********************************************************************
  Author:        Dana Vrajitoru, IUSB, CS
  Class:         C243 Data Structures
  File name:     word_counter.cc
  Last updated:  October 11, 2007

  Description:   Implementation of the class word_counter.
**********************************************************************/

#include "word_counter.h"

// Constructor with default values for both parameters. By default if
// we don't specify how many occurences of a word we have, we'll
// assume that we have at least one, otherwise we wouldn't need to
// store the word at all.
Word_counter::Word_counter(string s, int n)  
  : word(s), count(n)
{;}

// Constructor with the word specified as a regular array of
// characters (c string).
Word_counter::Word_counter (char *s, int n)
  : word(s), count(n)
{;}

// If we need to reset these values later.
void Word_counter::set_word(string s)
{
  word = s;
}

void Word_counter::set_word(char *s)
{
  word = s;
} 

void Word_counter::set_count(int n)
{
  count = n;
}

// Verify if the word stored in this object is equal to that string.
bool Word_counter::contains(char *s)
{
  return word == string(s);
}

// Verify if the word stored in this object is equal to that string.
bool Word_counter::contains(string s)
{
  return word==s;
}
  
// Add 1 to the count.
void Word_counter::increment()
{
  ++count;
}

// If we want to compare two word counters. These will compare the
// two strings (words) alphabetically.
int Word_counter :: operator< (const Word_counter &y)
{
   return (this->word < y.word);
}

int Word_counter :: operator<= (const Word_counter &y)
{
   return (this->word <= y.word);
}

int Word_counter :: operator> (const Word_counter &y)
{
   return (this->word > y.word);
}

int Word_counter :: operator>= (const Word_counter &y)
{
   return (this->word >= y.word);
}

// To be used in a table.
string key (const Word_counter & x)
{
   return x.word;
}

// Easy output of the word counter.
ostream & operator<< (ostream & output, const Word_counter & x)
{
  output << x.word << " " << x.count;
  return output;
}


// Comparison operators.
bool Word_counter::operator== (const Word_counter &y) const
{
  return (count == y.count &&
	  word == y.word);
}

bool Word_counter::operator!= (const Word_counter &y) const
{
  return !((*this) == y);
}
