all: prices.h arbitrage

%.h: %.py
	./$< > $@

CXX=clang++
flags=-g -Werror -Wall -Wextra -pedantic -std=gnu++14
%.o: %.cpp
	$(CXX) $(flags) -o $@ $<

arbitrage: arbitrage.o
	./$<
clean:
	rm -f prices.h *.o

update: clean
	make
