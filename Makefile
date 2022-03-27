.PHONY: all format clean run test

#directories
OBJ=obj
SRC=src
TEST=test

# flags
COMPILEFLAGS=-Wall -Werror

#sources
TEST_SOURCES=$(shell find $(TEST)/ -type f -name '*.cpp')

#objects
TEST_OBJECTS=$(addprefix $(OBJ)/, $(patsubst %.cpp, %.o, $(TEST_SOURCES)))

all: format bin/hangman bin/test_hangman

bin/hangman: obj/src/main.o
	$(CXX) $(COMPILEFLAGS) $^ -o $@

obj/src/main.o: src/main.cpp
	$(CXX) $(COMPILEFLAGS) -c $< -o $@

bin/test_hangman: $(TEST_OBJECTS)
	$(CXX) $(COMPILEFLAGS) $^ -o $@

obj/test/%.o: test/%.cpp
	$(CXX) $(COMPILEFLAGS) -I src -I thirdparty -c $< -o $@

format:
	find . -type f -name '*.cpp' -o -name '*.h' | xargs clang-format -i

clean:
	cd obj && find . ! -name '.keep' -type f | xargs rm -rf
	cd obj && find . -type d -empty | xargs rm -rf
	cd bin && find . ! -name '.keep' -type f | xargs rm -rf
	cd bin && find . -type d -empty | xargs rm -rf

run:
	cd bin && ./hangman

test:
	cd bin && ./test_hangman