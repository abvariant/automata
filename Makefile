CC = g++
#CFLAGS = -std=c99 -pedantic -Wall
CFLAGS = -pedantic -g -Wall
OBJECTS = subset_construct.o nfa.o dfa.o regex_parse.o

all: regex2nfa

subset_construct.o: subset_construct.cpp
	$(CC) $(CFLAGS) -c subset_construct.cpp

regex_parse.o: regex_parse.cpp
	$(CC) $(CFLAGS) -c regex_parse.cpp

nfa.o: nfa.cpp
	$(CC) $(CFLAGS) -c nfa.cpp

dfa.o: dfa.cpp
	$(CC) $(CFLAGS) -c dfa.cpp

regex2nfa: $(OBJECTS)
	$(CC) $(OBJECTS) -o regex2nfa

clean:
	rm -f *.o regex2nfa
