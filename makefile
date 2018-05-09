all: tmp tmp/exchanges.o tmp/markets.csv

# Make working directory
tmp:
	mkdir -p $@

tmp/%.csv: bin/%.py
	./$< > $@

CXX=clang++
flags=-g -Werror -Wall -Wextra -pedantic -std=gnu++14

tmp/%.o: %.cpp
	$(CXX) $(flags) -o $@ $<

markets: all
	tmp/exchanges.o

# All transient files written to tmp
clean:
	rm -rf tmp

update: clean
	make

format:
	clang-format -i *.cpp
