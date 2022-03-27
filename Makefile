.PHONY: all format

# flags
COMPILEFLAGS=-Wall -Werror

all: bin/hangman

bin/hangman: obj/main.o
	$(CXX) $(COMPILEFLAGS) $^ -o $@

obj/main.o: src/main.cpp
	$(CXX) $(COMPILEFLAGS) -c $< -o $@

format:
	find . -type f -name '*.cpp' -o -name '*.h' | xargs clang-format -i
