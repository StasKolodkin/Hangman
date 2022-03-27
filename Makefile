.PHONY: all

# flags
COMPILEFLAGS=-Wall -Werror

all: bin/hangman

bin/hangman: obj/main.o
	$(CXX) $(COMPILEFLAGS) $^ -o $@

obj/main.o: src/main.cpp
	$(CXX) $(COMPILEFLAGS) -c $< -o $@
