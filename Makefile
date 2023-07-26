CC = g++
CFLAGS = -pedantic -Wall
OBJECTS = nfaTest.o nfa.o

all: nfaTest.exe

nfa.o: nfa.cpp
	$(CC) $(CFLAGS) -c nfa.cpp

nfaTest.o: nfaTest.cpp
	$(CC) $(CFLAGS) -c nfaTest.cpp

nfaTest.exe: $(OBJECTS)
	$(CC) $(OBJECTS) -o nfaTest.exe

clean:
	rm -f *.o nfaTest.exe