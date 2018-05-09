all: exchanges.o markets.csv

%.csv: %.py
	./$< > $@

CXX=clang++
flags=-g -Werror -Wall -Wextra -pedantic -std=gnu++14

%.o: %.cpp
	$(CXX) $(flags) -o $@ $<

clean:
	rm -f *.o

update: clean
	make

format:
	clang-format -i *.cpp
