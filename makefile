all: source
	
results:
	tmp/results.md

CXX ?= clang++
CXXFLAGS ?= -g -pedantic -pedantic-errors -std=c++14 --coverage

tmp:
	mkdir -p $@
clean:
	rm -rf tmp
	rm -f *.gcda *.gcno

objects = $(patsubst %.cpp, tmp/%.o, $(wildcard *.cpp))
source: tmp $(objects)

tmp/%.o: %.cpp
	echo Using compiler $(CXX)
	$(CXX) $(CXXFLAGS) -o $@ $<

tmp/results.md: tmp/curly.o
	$< | tee $@
	cat template.md > readme.md
	echo Generated $(shell TZ=BST-1 date) >> readme.md
	cat $@ >> readme.md
