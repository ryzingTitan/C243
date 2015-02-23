
/*** M A N I P U L A T E   B I N A R Y   T R E E S   R E C U R S I V E L Y ***

FILE NAME      :  bin-trees-A.cc

FIRST COMPLETED:  by W. Knight, July 5, 1993
MODIFIED       :  by W. Knight, Jan. 17, 1994 (converted it from Pascal to C++)
                  by W. Knight, Sept. 1, 1997 (revised documentation)
                  by W. Knight, Oct. 7, 1998  (adapted it for C243)
                  by W. Knight, Aug. 20, 2000 (added a function)
                  by W. Knight, Feb. 16, 2003 (changed a function)
                  by D. Vrajitoru, March 14, 2004 (new header style)
                  by D. Vrajitoru and C. George (added a print function)
                                                Nov 3, 2004

LANGUAGE :  GNU C++ for Linux

ACTION   :  The program allows an interactive user to build binary
            trees with integer labels on the nodes, to get information
            about these trees, and to modify or destroy them.

INPUT    :  All input consists of commands entered by an interactive user.

OUTPUT   :  All output is sent to the screen, including the prompts
            and menus provided to the interactive user and the results
            of the commands entered by the user.  The commands entered
            by the user are echoed by the program to the screen.

COMMENTS :  This program is intended to be given to C243 students as
            a programming assignment.  They are to supply missing code.

******************************************************************************/

#include <iostream>
using namespace std;
#include <cstdlib>

#include <vector>
#include <string>
#include <sstream>

#define A(x)   cout << x << endl;       // Debugging macro
#define B(x,y) cout << x << y << endl;  // Debugging macro


/**************************  D A T A   T Y P E S  ****************************/

struct node
{
  node *left;
  int  datum;
  node *right;
};
typedef node * node_ptr;      // Define a new pointer data type.


/*****************  F U N C T I O N   P R O T O T Y P E S  *******************/

void  build_a_binary_tree (node_ptr &rootp);
int   count_of_zero_data_values (node_ptr rootp);
void  destroy_a_binary_tree (node_ptr &rootp);
int   height (node_ptr rootp);
void  increment_each_datum (node_ptr rootp);
void  pretty_print (node_ptr rootp, int margin = 0);
void graph_print(node_ptr rootp);
int graph_print_walk(node_ptr rootp, int &pos, int level, 
		     vector<string>& output);
ostream &operator<<(ostream &out, node_ptr rootp);
void  reverse (node_ptr &rootp);
int   sum_of_negative_data (node_ptr rootp);

void  print_menu_and_get_action (char & response);
void  print_explanatory_message();
void  read_and_echo_char_response (char & response);
void  read_and_echo_int_response (int & response);
void  test_dynamic_allocation (void * pointer_value);



/************************  M A I N   F U N C T I O N  **********************/

int main()
{
  node_ptr  treep  = NULL;     // "treep" stands for "tree pointer";  will be
  char      response;          // used to point to the root of a binary tree
  int       data_value;

  void  print_explanatory_message();

  do  // until interactive user signals to quit
    {
      print_menu_and_get_action (response);  // Insists on a valid response
      switch (response)  // Response is necessarily one of the following.
        {
          case 'B' :
	  case 'b' : build_a_binary_tree (treep);
                     break;
          case 'C' :
          case 'c' : cout << "\nThere are " 
                          << count_of_zero_data_values (treep)
                          << " zero data values in the current tree.\n";
                     break;
          case 'D' :
          case 'd' : cout << endl;
                     destroy_a_binary_tree (treep);
		     cout << "\nThe tree should now be empty.\n";
                     break;
	  case 'H' :
	  case 'h' : cout << "\nThe height of the tree is " << height(treep)
                          << ".\n";
	             break;
	  case 'I' :
	  case 'i' : increment_each_datum (treep);
                     cout << "\nEvery data value should have been "
			  << "incremented.\n";
	             break;
          case 'P' : 
          case 'p' : if (!treep)
	               cout << "\nThe tree is empty." << endl;
	             else
                       graph_print (treep);
                     break;
          case 'Q' :
          case 'q' : break; // Do nothing.  The program will quit.
          case 'R' :
          case 'r' : cout << endl;
                     reverse(treep);
                     cout << "\nThe tree should now be the mirror image "
			  << "of what it was.\n";
                     break;
          case 'S' :
  	  case 's' : cout << "\nThe sum of the negative data values is "
			  << sum_of_negative_data (treep) << endl;
	             break;
       }
   }while (response != 'Q' && response != 'q');

  cout << "\n\n";
  return 0; // Indicate normal termination.
}


/*************  P R I N T   E X P L A N A T O R Y   M E S S A G E  ***********

This function prints a message to the interactive user explaining briefly
what the program is going to do.  Documented and coded by W. Knight. */

void  print_explanatory_message()
{
  cout << "\n\nThis program allows an interactive user to create, modify,\n";
  cout << "display, and destroy binary trees.  The program is menu driven.\n";
  cout << "Press the Enter key to continue.";
  while (cin.get() != '\n');  // Clear the input stream up through newline.
}                             // Note the empty loop body.


/************  R E A D   A N D   E C H O   C H A R   R E S P O N S E  *********

This utility function assumes that an interactive user has been prompted
to enter a one-character response, followed by a newline character.
It reads the first non-white-space response character and then clears all 
other characters from the input stream, up through the first newline character.
It also echoes the character back to the user.  Documented and coded by  
W.Knight. */

void read_and_echo_char_response (char & response)
{
  char junk;  // Holds chars that trail the desired response char.

  cin >> response;
  while (cin.get() != '\n'); // Clear the line.
    cout << response << endl;
}


/************  R E A D   A N D   E C H O   I N T   R E S P O N S E  *********

This utility function assumes that an interactive user has been prompted
to enter an integer value, followed by a newline character.
It reads the first integer on the line and then clears all 
other characters from the input stream, up through the first newline character.
It also echoes the integer back to the user.  Documented and coded by 
W.Knight. */

void read_and_echo_int_response (int & response)
{
  cin >> response;
  while (cin.get() != '\n');  // Clear the line.
    cout << response << endl;
}


/**********  P R I N T   M E N U   A N D   G E T   A C T I O N  *************

This function displays a menu of actions and asks an interactive user to 
select one.  It will not return until it has read an acceptable response. 
Documented and coded by W.Knight. */

void print_menu_and_get_action (char & response)
{
  cout << "\n\n";
  cout << "Which of the following actions do you wish to take?\n";
  cout << "   B)uild or modify the current tree interactively.\n";
  cout << "   C)ount and report number of zero data values in "
              "current tree\n";
  cout << "   D)estroy the current tree.\n";
  cout << "   H)eight of the tree -- determine it.\n";
  cout << "   I)ncrement every data value in the current tree by 1.\n";
  cout << "   P)rint the current tree on the screen.\n";
  cout << "   Q)uit.\n";
  cout << "   R)eplace the current tree by its mirror image.\n";
  cout << "   S)um the negative data values in the current tree.\n";
  cout << "\n";
  cout << "Your choice:  ";
    
  read_and_echo_char_response (response);

  while (1) // loop will continue until user gives an appropriate response
    {
      switch (response)
	{
          case 'B': case 'b': case 'C': case 'c': 
          case 'D': case 'd': case 'H': case 'h': 
	  case 'I': case 'i': case 'P': case 'p': 
          case 'Q': case 'q': case 'R': case 'r': 
	  case 'S': case 's' :
            return;  // EXIT FROM THE FUNCTION WITH PARAMETER HAVING OK VALUE 
          default : cout << "Improper Response  "
                            "Please type an appropriate letter.   ";
	}
      read_and_echo_char_response (response);
    }
}

  
/*******************  T E S T   D Y N A M I C   A L L O C A T I O N  *********

This utility function assumes that the value of the parameter "pointer" 
has been obtained by a call to the "new" function.  If that function
was unable to dynamically allocate the required amount of memory space,
then it returned the value NULL.  This function tests to see whether
the value returned was NULL, and if it was, it terminates the program.
The parameter type is "pointer-to-void" so that any pointer data type
can be passed to this function.   Documented and coded by W. Knight. */

void test_dynamic_allocation (void * pointer)
{
  if (!pointer)  // if "pointer" is NULL
    {
      cout << "\nDynamic allocation failure.  Program being terminated."
           << endl;
      exit(1);  // EXIT FROM THE ENTIRE PROGRAM
    }
}

/******************  P R I N T   T R E E   V E R T I C A L L Y  *************

The following function prints a binary tree vertically graphically
showing the connections between parent and child nodes The function
and support functions were written by C. George, C423, Fall 2004. */

void graph_print(node_ptr rootp)
{
  if(rootp == NULL) return;
	
  // create an array to hold the output as is it generated
  vector<string> output;
  int pos = 0;
  pos = graph_print_walk(rootp, pos, 0, output);

  // print the root node
  cout << string(pos,' ') << rootp << endl;

  // print the other levels from top to bottom
  for(int i=0;i<output.size();i++)
    {
      cout << output[i] << endl;
    }
}

// This function walks through the tree in-order to calculate the x
// position of each node in the tree. It then prints any child nodes
// to the appropriate output string and also prints innerconnecting
// links

int graph_print_walk(node_ptr rootp, int &pos, int level, 
		     vector<string>& output)
{
  if(rootp == NULL) pos;
  else
    {
      // Expand the size of the ouput array if this is the first
      // node on a new level
      if(output.size() <= (level*2))
	{
	  output.push_back("");
	  output.push_back("");
	}
		
      // Calculate the x position of both child nodes and the current node
      int left_pos = graph_print_walk(rootp->left, pos, level+1, output);
		
      int curr_pos = pos;

      ostringstream curr_datum;
      curr_datum << rootp;
      pos += curr_datum.str().length()+1;

      int right_pos = graph_print_walk(rootp->right, pos, level+1, output);
		
      // initialize the output streams with the current output for the level

      ostringstream link_line, node_line;

      link_line << output[level*2];
      node_line << output[level*2+1];

      // calculate the center of the current node
      int curr_offset = curr_pos + (curr_datum.str().length() / 2) - 1;

      // add the left node and its link to the current output for the level
      if(rootp->left != NULL)
	{
	  // calculate the center of the left child node
	  ostringstream left_datum;
	  left_datum << rootp->left;
	  int left_offset = left_pos + (left_datum.str().length() / 2) - 1;

	  node_line << string(left_pos - node_line.str().length(), ' ') <<
	    rootp->left;

			
	  // draw a link from this node to the left child node
	  link_line << string((left_offset+1) - link_line.str().length(), ' ') <<
	    string((curr_offset)-(left_offset+1), '_') << "/";
			
	}

      // add the right node and its link to the current output for the level
      if(rootp->right != NULL)
	{
	  // calculate the center of the right child node
	  ostringstream right_datum;
	  right_datum << rootp->right;
	  int right_offset = right_pos + (right_datum.str().length() / 2) - 1;


	  node_line << string(right_pos - node_line.str().length(),' ') <<
	    rootp->right;

			
	  // draw a link from this node to the right child node
	  link_line << string((curr_offset+1) - link_line.str().length(),' ') 
		    << "\\" <<	string((right_offset-1) - (curr_offset), '_') 
		    << " ";
	}

      // save the results for the current level
      output[level*2]   = link_line.str();
      output[level*2+1] = node_line.str();

      return curr_pos;
    }
}

// This stream formatter outputs the contents of a node with a leading digit
// for datum values 0-9

ostream &operator<<(ostream &out, node_ptr rootp)
{
  out << ((rootp->datum >= 0 && rootp->datum < 10)?"0":"")
      << rootp->datum;
  return out;
}

/**************************  P R E T T Y   P R I N T  *************************
                                                                           
The following function sends to standard output a list of the integer data
values of the nodes in the binary tree pointed to by "rootp".  The values
are written in such a way as to show the logical structure of the tree.
The parameter "margin" should have a non-negative value, which determines 
the number of blank spaces that will be printed to the left of the root 
of the tree.  If no second argument is used when this function is called,
then the default value 0 will be used (see the function prototype).  
The function is recursive.   Documented and coded by W.Knight. */

void pretty_print (node_ptr rootp, int margin) // 
{
  const int INDENTATION = 4;

  if (!rootp)
    return;

  else
    {
      pretty_print(rootp->right, margin + INDENTATION);

      for (int i = 1; i <= margin; ++i)
	cout << " ";

      cout << rootp->datum << endl;

      pretty_print(rootp->left, margin + INDENTATION);
    }
}


/*****************  B U I L D   A   B I N A R Y   T R E E  ******************
                                                                           
The following function allows an interactive user to construct a binary   
tree whose nodes hold integer data values.  The function is recursive. 
Documented and coded by W.Knight. */

void build_a_binary_tree (node_ptr &rootp) // Paremeter passed by REFERENCE!
{
  char action;

  while(1)  // Endless loop; there are two "return" statements in the loop.
            // They are executed whenever the user wants to move up the tree.
    {
      if (rootp == NULL)  // The tree or subtree pointed to by rootp is empty.
        {
          do  // This loop continues until the user responds with 'U' or 'C'.
            {
              cout << "\nYou are currently at an empty tree. If you wish to ";
	      cout << "create\na new node at this position, type C and press";
	      cout << " Enter.\nOtherwise ";
	      cout << "type U to go up to the parent node (if any).  ";
	      read_and_echo_char_response (action);
	    } while (action != 'C' && action!= 'c' && action!= 'U' 
		                                   && action!= 'u');
	  if (action == 'U' || action == 'u')
            return; // Return control to the calling function
	  else
	    {
	      rootp = new node;
	      test_dynamic_allocation (rootp);
	      rootp->left  = rootp->right = NULL;
	      cout << "Enter an integer for the new node:  ";
	      read_and_echo_int_response (rootp->datum);
	    }	
	}
      else  // tree is not NULL
	{
	  do  // This loop continues until user gives a suitable response.
	    {      
	      cout << "\nThe datum of the node at which you have arrived is\n";
	      cout << "         ";
	      cout << rootp->datum << endl;
	      cout << "Enter  U  to go up to the parent node,\n";
	      cout << "       L  to go down to the left,\n";
	      cout << "       R  to go down to the right,\n";
	      cout << "       M  to modify value of the datum stored here.\n";
	      read_and_echo_char_response (action);
	    }
         while (action != 'U' && action !='u' && action !='L' && action !='l' 
            && action != 'R' && action !='r' && action !='M' && action !='m');

	 switch (action)
	   { 
             case 'U': case 'u': return;   // Go back to the calling function.
             case 'L': case 'l': build_a_binary_tree (rootp->left);  break;
             case 'R': case 'r': build_a_binary_tree (rootp->right); break;
             case 'M': case 'm': cout << "Enter a new datum value to replace"
				         " the current value.  ";
	                         read_and_echo_int_response (rootp->datum);
	   } // end of "switch"
	}   // end of "else"     
    }     // end of "while(1)" 
}       // end of function 


/*************  C O U N T   O F   Z E R O   D A T A   V A L U E S  **********

The following function traverses the binary tree pointed to by "rootp"
and counts every node whose datum value is zero.  The function
returns that count as its value.  The function is recursive.  The function
documentation and heading were written by W. Knight.  */

int count_of_zero_data_values (node_ptr rootp)
{
  int count = 0;

  if (rootp)
  {
    if (rootp -> datum == 0)
      ++ count;

    count += count_of_zero_data_values(rootp -> left);
    count += count_of_zero_data_values(rootp -> right);
  }
  
  return count;
}


/****************  D E S T R O Y   A   B I N A R Y   T R E E  ***************
                                                                           
The following function deallocates all the nodes in the binary tree 
pointed to by "rootp", and it makes the tree empty (i.e., it changes to 
NULL the value of the pointer passed to it).  The function is recursive.  
The function documentation and heading were written by W. Knight.  */

void destroy_a_binary_tree (node_ptr &rootp)
{
  if (rootp)
  {
    destroy_a_binary_tree(rootp -> left);
    destroy_a_binary_tree(rootp -> right);

    delete rootp;
    rootp = NULL;
  }
} 


/***************************  H E I G H T  ********************************

The following function calculates and returns the height of the binary
tree pointed to by "rootp".  The function is recursive.  The function
documentation and heading were written by W. Knight.  */

int height (node_ptr rootp)
{
  int left_height, right_height;

  if (!rootp)
    return -1;

  else
  {
    left_height = height(rootp -> left);
    right_height = height(rootp -> right);

    if (left_height >= right_height)
      return 1 + left_height;
    
    else
      return 1 + right_height;
  }
}


/********************  I N C R E M E N T   E A C H   D A T U M  **************

The following function traverses the binary tree pointed to by "rootp"
and replaces the datum value in each node by the number that's greater
by  1  in value.  The function is recursive.  The function documentation 
and heading were written by W. Knight.  */

void increment_each_datum (node_ptr rootp)
{
  if (rootp)
  {
    ++ rootp -> datum;
    
    increment_each_datum(rootp -> left);
    increment_each_datum(rootp -> right);
  }
}


/****************************  R E V E R S E  ******************************
                                                                          
This function replaces the binary tree pointed to by "rootp" with its     
mirror image.  The function is recursive.  The function documentation and
heading were written by W. Knight.                              */

void reverse (node_ptr &rootp)
{
  node_ptr temp;

  if (rootp)
  {
    reverse(rootp -> left);
    reverse(rootp -> right);
    
    temp = rootp -> right;
    rootp -> right = rootp -> left;
    rootp -> left = temp;
  }
}


/*****************  S U M   O F   N E G A T I V E   D A T A ****************

The following function traverses the binary tree pointed to by "rootp",
sums the data values that are negative, and returns that sum.  For example,
if the tree contains nodes with data values  -2 , -6 , and -1 , and no
other nodes contain negative data, then the function will return the 
number  -9 .  If the tree contains no node with negative data value,
then the function returns zero .  The function is recursive.  The function
documentation and heading were written by W. Knight.  */

int sum_of_negative_data (node_ptr rootp)
{
  int sum = 0;
  
  if (rootp)
  {
    if (rootp -> datum < 0)
      sum += rootp -> datum;

    sum += sum_of_negative_data(rootp -> left);
    sum += sum_of_negative_data(rootp -> right);
  }
  
  return sum;
}
