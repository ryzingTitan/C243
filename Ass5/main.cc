/*************************************************************
  File:         main.cc                             
  Description:  A test program for the Porter transformation. 
                It reads one word at a time from the console 
                and outputs the transformed word until the 
                input ends by an eof - a CTRL-D under a Linux 
                terminal or the end of the file in case or 
                redirection.

                                                         
  Author:       Dana Vrajitoru 
  Organization: IUSB                                    
  Date:         October 5, 2004
***************************************************************/

#include <fstream>
#include <iostream>
using namespace std;
#include "porter.h"
#include "hash_table.h"

void Read_stoplist(HTable &stoplist);
void Index_words(HTable &stoplist, HTable &indexing);
void Increment(HTable &indexing, string word);

int main()
{
  HTable stoplist, indexing;
  Read_stoplist(stoplist);
  stoplist.statistic();
  Index_words(stoplist, indexing);
  cout << "Here is the indexing of your text" << endl;
  indexing.print();
  return 0;
}

// Inputs the stoplist and stores it in the table.
void Read_stoplist(HTable &stoplist)
{
  char word[KEYWORDSIZE];
  ifstream fin("stop_words");
  Word_counter wordc;
  do {
    fin >> word;
    if (!fin.eof()) {
      wordc.set_word(word);
      stoplist.insert(wordc);
    }
  } while (!fin.eof());
  fin.close();
}

// Reads a word at a time from the console, verifies that it's not in
// the stoplist, and if it's not, it applies the Porter transform to
// it, then it indexes it in the table indexing.
void Index_words(HTable &stoplist, HTable &indexing)
{
  char word[KEYWORDSIZE];
  Word_counter wordc;
  cout << "Enter words separated by spaces or new lines.\n"
       << "The program will output the Porter transform of the words.\n"
       << "End the input with Ctrl-D." << endl;
  while (!cin.eof()) {
    cin >> word;
    if (!cin.eof()) {
      to_lower_case(word);
      clean(word);

      if (!stoplist.access(wordc, string(word))) {
	strip_affixes(word);
	Increment(indexing, word);
      }
    }
  }
  cout << endl;
}

// It should increment the indexing of the given word in the
// table. This means that if the word can't be found in the table,
// then it should insert it with a count of 1. Otherwise it should
// remove the word from the table, increment the count of the object
// that has been removed, then insert it back with the new number.
void Increment(HTable &indexing, string word)
{
  Word_counter wordc(word, 0);
  if (indexing.access(wordc, word)) {
    indexing.remove(wordc, word);
  }
  wordc.increment();
  indexing.insert(wordc);
}
