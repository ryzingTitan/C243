/*********************************************************************
  Author:        Dana Vrajitoru, IUSB, CS
  Class:         C243 Data Structures
  File name:     interface.h
  Last updated:  January 31, 2013
  Updated by:    Kyle Stoltzfus
  Description:   The functions that handle the communication with the
                 user.
**********************************************************************/

#ifndef INTERFACE_H
#define INTERFACE_H

#include "List.h"

// The main loop of the program: print the menu, input the user's
// choice, perform some action based on it.
void runTheActionsLoop ();

// Prints all the options in the program's menu.
void printMenu ();

// Reads the user's choice and asks for it again if the choice is not
// a valid one.
int actionFromUser ();

// Execute the action determined by the user's entry.
bool carryOutTheAction (int choice, List & first, List & second);

// Concatenate the lists and write appropriate messages.
void concatenateAction(List & first, List & second);
// Replace action: destroy the first list and then copy the second one
// to it.
void replaceAction(List & first, List & second);
// Empty the first list action.
void destroyAction(List &first);
// Inputs a number and inserts it at the front of the given list.
void insertFrontAction(List &first);
// Inputs a number and inserts it at the back of the given list.
void insertBackAction(List &first);
// Checks if the list is ordered and prints the appropriate message.
void isOrderedAction(List &first);
// Compares the two lists and prints the appropriate message.
void compareAction(List & first, List & second);
//Checks if a list element exists at the location entered by the user.
void findElement(List &first);
//Searches a list to see if the number entered by the user is in it.
void findNumber(List &first);

#endif
