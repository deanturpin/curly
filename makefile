all: prices.h arbitrage.o

%.h: %.py
	./$< > $@

CXX=clang++
flags=-g -Werror -Wall -Wextra -pedantic -std=gnu++14
%.o: %.cpp
	$(CXX) $(flags) -o $@ $<
clean:
	rm -f prices.h
