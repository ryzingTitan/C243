/**********************************************************
  File:          porter.h                             
  Description:   Functions for applying the Porter 
                 transformation to a word.

                                                         
  Author:        Dana Vrajitoru  and Stuart J. Barr                      
  Organization:  IUSB                                    
  Date:          October 5, 2004
***********************************************************/

#ifndef PORTER_H
#define PORTER_H

#define KEYWORDSIZE 25
#define PREFIXES 1

#define BIG_KEYWORDSIZE (KEYWORDSIZE+20)

void to_lower_case(char *kwd);
void clean(char *kwd);

// The main porter function. It converts the word to lowercase and
// removes all non-alphabetic characters from the string. Next it
// removes prefixes like "kilo" and suffixes like "s" and "ing".
void strip_affixes (char *string);

// Removes prefixes like "kilo".
void strip_prefixes (char *string);

// Strips suffixes like "s" and "ing" to retain only the root of the
// word.
void strip_suffixes (char *string);

// Five steps done in this order by the previous function.
void step_1 (char *string);
void step_2 (char *string);
void step_3 (char *string);
void step_4 (char *string);
void step_5 (char *string);

// Other internal functions.
int isvalid(char l);
bool has_suffix ( char *word, char *suffix, char *stem );
int measure ( char *stem );
bool contains_vowel ( char *word );
bool cvc ( char *string );
bool vowel ( char ch, char prev );

#endif
