CC = g++

CFLAGS = -Wall -Wextra -fsanitize=address,undefined -std=c++17

all: sim

sim: Driver.o Webserver.o Request.o LoadBalancer.o
	$(CC) $(CFLAGS) -o sim Driver.o Webserver.o Request.o LoadBalancer.o

Driver.o: Driver.cpp
	$(CC) $(CFLAGS) -c Driver.cpp -o Driver.o

Request.o: Request.cpp Request.h
	$(CC) $(CFLAGS) -c Request.cpp -o Request.o

LoadBalancer.o: LoadBalancer.cpp LoadBalancer.h
	$(CC) $(CFLAGS) -c LoadBalancer.cpp -o LoadBalancer.o

Webserver.o: Webserver.cpp Webserver.h
	$(CC) $(CFLAGS) -c Webserver.cpp -o Webserver.o

clean:
	rm -f *.o sim log.txt