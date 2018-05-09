all: prices.h arbitrage2.o

%.h: %.py
	./$< > $@

%.csv: %.py
	./$< > $@

CXX=clang++
flags=-g -Werror -Wall -Wextra -pedantic -std=gnu++14
%.o: %.cpp
	$(CXX) $(flags) -o $@ $<

clean:
	rm -f prices.h *.o

update: clean
	make

format:
	clang-format -i *.cpp
