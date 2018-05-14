all: tmp tmp/index.html

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
EXTRA=
flags=-g -Werror -Wall -Wextra -pedantic -std=c++14 $(EXTRA)

tmp/%.o: %.cpp
	$(CXX) $(flags) -o $@ $<

tmp/index.html: tmp/curly.o
	$< > $@
	@echo '<p>$(shell TZ=BST-1 date --utc)</p>' >> $@

update: clean
	make

format:
	clang-format -i *.cpp

example:
	bin/all_exchanges.py

gitpull:
	git pull --quiet
