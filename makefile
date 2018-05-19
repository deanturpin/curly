all: source generate tmp/results.md

CXX=clong++
flags=-g -pedantic -pedantic-errors -std=c++14 --coverage

tmp:
	mkdir -p $@
clean:
	rm -rf tmp

objects = $(patsubst %.cpp, tmp/%.o, $(wildcard *.cpp))
source: tmp $(objects)

tmp/%.o: %.cpp
	echo Using compiler $(CXX)
	$(CXX) $(flags) -o $@ $<

tmp/results.md: tmp/curly.o
	$< | tee $@
	@echo Generated $(shell TZ=BST-1 date) >> $@
	cat template.md $@ > readme.md

format:
	clang-format -i *.cpp
