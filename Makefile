# Created by Aiden Hoppe on 4/11/2025
# For use in CS2401 Final Project, Boop Game

CC = g++
CFLAGS = -Wall -std=c++11

make:
	$(CC) -c *.cc && $(CC) $(CFLAGS) *.o -o a.out

gdb:
	$(CC) -c *.cc -g && $(CC) $(CFLAGS) *.o -g -o gdb.out

clean:
	rm -rf *.o *.out