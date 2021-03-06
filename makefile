#
#
#
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline

all: ticker

ticker: driver.c  avlTicker.o ticker.o ticker.h avlTicker.h
	gcc $(CFLAGS) -o ticker driver.c ticker.o avlTicker.o 

ticker.o: ticker.c 
	gcc -c -o ticker.o ticker.c

avlTicker.o: avlTicker.c avlTicker.h
	gcc -c -o avlTicker.o avlTicker.c

profile: ticker.o avlTicker.o driver.c
	gcc $(CFLAGS) -pg -o ticker driver.c ticker.o avlTicker.o

debug: ticker.o avlTicker.o driver.c
	gcc $(CFLAGS) -g -o ticker driver.c ticker.o avlTicker.o

test: 
	./ticker TickerTestFiles/companies.txt < TickerTestFiles/stock_changes.dat 

clean:
	rm -f *.o ticker


