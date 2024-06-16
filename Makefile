CC = g++

CFLAGS = -Wall -Wextra -fsanitize=undefined,address -std=c++17

all: sim

sim: driver.o request.o
	$(CC) $(CFLAGS) -o sim driver.o request.o

driver.o: Driver.cpp
	$(CC) $(CFLAGS) -c Driver.cpp

request.o: Request.cpp Request.h
	$(CC) $(CFLAGS) -c Request.cpp

clean:
	rm -f *.o sim

