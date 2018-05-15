TMP_DIR=/tmp/curly

all: $(TMP_DIR) $(TMP_DIR)/index.html

# Make working directory, all transient files are written here clean is easy
$(TMP_DIR):
	mkdir -p $@
clean:
	rm -rf $(TMP_DIR)

$(TMP_DIR)/%.csv: bin/%.py
	./$< > $@

JOBS=4
objects = $(patsubst %.cpp, $(TMP_DIR)/%.o, $(wildcard *.cpp))
source: $(TMP_DIR)
	make --jobs $(JOBS) $(objects)

CXX=clang++-4.0
EXTRA=
flags=-g -Werror -Wall -Wextra -pedantic -std=c++14 $(EXTRA)

$(TMP_DIR)/%.o: %.cpp
	$(CXX) $(flags) -o $@ $<

$(TMP_DIR)/index.html: $(TMP_DIR)/curly.o
	$< > $@
	@echo '<p>$(shell TZ=BST-1 date)</p>' >> $@

update: clean
	make

format:
	clang-format -i *.cpp

example:
	bin/all_exchanges.py

gitpull:
	git pull --quiet
