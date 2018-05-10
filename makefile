all: tmp tmp/exchanges.o tmp/markets.csv

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

CXX=g++
flags=-g -Werror -Wall -Wextra -pedantic -std=gnu++14

tmp/%.o: %.cpp
	$(CXX) $(flags) -o $@ $<

markets: all
	tmp/exchanges.o


update: clean
	make

format:
	clang-format -i *.cpp

example:
	bin/all_exchanges.py
