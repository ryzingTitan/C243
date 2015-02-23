
#These variables are not used, but are left for future reference
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

sources = my_array.cc main.cc

# objects are the same as the source files with .cc replaced with .o
objects = $(sources:.cc=.o)

default: array

array: my_array.o main.o
	g++ -g -o array my_array.o main.o -lm

my_array.o : my_array.cc my_array.h
	g++ -c my_array.cc -o my_array.o

main.o : main.cc my_array.h
	g++ -c main.cc -o main.o


clean :
	rm *.o
	rm array



