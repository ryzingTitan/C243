/*********************************************************************
  Author:        Dana Vrajitoru, IUSB, CS
  Class:         C243 Data Structures
  File name:     hash_table.h
  Last updated:  October 11, 2007
  Description:   Definition of a hash table.
**********************************************************************/

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <list>
#include <string>

#include "word_counter.h"

const int M=200;

typedef list<Word_counter> List_wordc;
typedef List_wordc::iterator List_iter;

class HTable {
 private:
  vector<List_wordc> storage;
  int size;
  int nr_objects;

  // Checks if the access to a given position is safe in the
  // storage. This means if the position is smaller than the size and
  // non negative.
  bool is_safe(int position);
  // Increases the size of the array up to the given position.
  bool increase(int position);

  // This function inserts an object in the table when we already know
  // what position we want it to be inserted at. It is declared as
  // private because the user should not be able to call it. It is
  // designed to be called internally by the public insertion function
  // after getting the position from the hashing function.
  bool insert(Word_counter &wordc, int position);

  // This function removes the word counter object from the list at
  // the given position. The key k is a separate parameter from the
  // object because we don't know what the object is yet. It is also
  // intended to be called internally because public remove function
  // should determine the position based on the hash function before
  // it calls this one.
  bool remove(Word_counter &wordc, string k, int position);

  // Private functions to be implemented by the student.

  // This function should find if the string k has been used as a key
  // to insert an object in the list at the given position. If yes,
  // then it should copy that object into the object wordc and return
  // true. If not, it should return false.
  bool find(Word_counter &wordc, string k, int position);

  // The most important function of the class. This function takes a
  // string (a key) and determines the index in the storage array
  // where a object with that key should go.
  int hashing(string k);

 public:
  // Constructor with given initial capacity.
  HTable(int capacity = M);
  // Destructor.
  ~HTable();
  // Delete all the objects without deleting the storage array.
  void make_empty();

  // Prints all the objects in the table.
  void print();

  // Public functions to be implemented by the student.

  // This function should first get the hash index for the key of that
  // object, then find out if the key has been inserted in the list at
  // that index, and if not, then it should insert the object in that
  // list and return true. If the key has already been used in the
  // table, it should return false.
  bool insert(Word_counter &wordc);

  // This function should first get the hash index for the string,
  // then find out if the string has been used as a key to insert an
  // object in the list at that index. If yes, it should copy that
  // object into the wordc and return true, and if not, it should just
  // return false.
  bool access(Word_counter &wordc, string k);

  // This function should first get the hash index for the string k,
  // then find out if the string has already been used as a key to
  // insert an object in the list at that index. If yes, it should
  // copy that object into the wordc, remove the object from that
  // list, and return true. If not, it should just return false.
  bool remove(Word_counter &wordc, string k);

  // This function should print a statistic of usage of each index in
  // the table (number of objects stored at each index).
  void statistic();
};

#endif
