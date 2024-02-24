CC = g++
#CFLAGS = -std=c99 -pedantic -Wall
CFLAGS = -pedantic -Wall
OBJECTS = regex_parse.o nfa.o

all: regex2nfa

nfa.o: nfa.cpp
	$(CC) $(CFLAGS) -c nfa.cpp

regex_parse.o: regex_parse.cpp
	$(CC) $(CFLAGS) -c regex_parse.cpp

regex2nfa: $(OBJECTS)
	$(CC) $(OBJECTS) -o regex2nfa

clean:
	rm -f *.o regex2nfa
