
CC          = gcc
CLINKER     = gcc
CCC         = g++
CCLINKER    = $(CCC)
INCLUDE_DIR = 
CFLAGS      = $(INCLUDE_DIR)
CCFLAGS     = $(CFLAGS)
OPTFLAGS    = -g
LIB_PATH    =
LIB_LIST    = -lm
LIBS        = $(LIB_PATH) $(LIB_LIST)

EXEC        = hashing
objects     = word_counter.o hash_table.o porter.o main.o

default: $(EXEC)

$(EXEC): $(objects)
	g++ -g -o $(EXEC) $(objects)

word_counter.o : word_counter.cc word_counter.h
	g++ -c word_counter.cc -o word_counter.o

porter.o : porter.cc porter.h
	g++ -c porter.cc -o porter.o

hash_table.o : hash_table.cc hash_table.h word_counter.h
	g++ -c hash_table.cc -o hash_table.o

main.o : main.cc hash_table.h porter.h
	g++ -c main.cc -o main.o

clean :
	rm *.o
	rm $(EXEC)



