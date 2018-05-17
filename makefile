all: tmp generate

tmp:
	mkdir -p $@
clean:
	rm -rf tmp

objects = $(patsubst %.cpp, tmp/%.o, $(wildcard *.cpp))
source: tmp
	make $(objects)

CXX=clang++-4.0
EXTRA=
flags=-g -Werror -Wall -Wextra -pedantic -std=c++14 $(EXTRA)

tmp/%.o: %.cpp
	$(CXX) $(flags) -o $@ $<

generate: tmp/results.md

tmp/results.md: tmp/curly.o
	$< | tee $@
	@echo Generated $(shell TZ=BST-1 date) >> $@
	cat template.md $@ > readme.md

format:
	clang-format -i *.cpp

lint:
	cppcheck --enable=all .
