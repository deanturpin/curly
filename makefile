all: prices.h

%.h: %.py
	./$< > $@

clean:
	rm -f prices.h
