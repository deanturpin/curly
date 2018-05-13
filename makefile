all: tmp/index.html

# Make working directory, all transient files are written here clean is easy
tmp:
	mkdir -p $@
clean:
	rm -rf tmp

tmp/%.csv: bin/%.py
	./$< > $@

JOBS=4
objects = $(patsubst %.cpp, tmp/%.o, $(wildcard *.cpp))
source: tmp
	make --jobs $(JOBS) $(objects)

CXX=clang++-4.0
flags=-g -Werror -Wall -Wextra -pedantic -std=gnu++14

tmp/%.o: %.cpp
	$(CXX) $(flags) -o $@ $<

tmp/index.html: tmp/curly.o
	$< > $@

update: clean
	make

format:
	clang-format -i *.cpp

example:
	bin/all_exchanges.py
