
CC          = gcc
CLINKER     = gcc
CCC         = g++
CCLINKER    = $(CCC)
INCLUDE_DIR = 
CFLAGS  = $(INCLUDE_DIR)
CCFLAGS = $(CFLAGS)
OPTFLAGS    = -g
LIB_PATH    =
LIB_LIST    = -lm
LIBS = $(LIB_PATH) $(LIB_LIST)

objects = ListNode.o List.o ListIterator.o general.o interface.o main.o

default: testlist

testlist: $(objects)
	g++ -g -o testlist $(objects)

ListNode.o : ListNode.cc ListNode.h
	g++ -c ListNode.cc -o ListNode.o

ListIterator.o : ListIterator.cc ListIterator.h ListNode.h
	g++ -c ListIterator.cc -o ListIterator.o

List.o : List.cc List.h ListNode.h general.h
	g++ -c List.cc -o List.o

interface.o : interface.cc List.h
	g++ -c interface.cc -o interface.o

general.o : general.cc general.h
	g++ -c general.cc -o general.o

main.o : main.cc interface.h
	g++ -c main.cc -o main.o


clean :
	rm *.o
	rm testlist



