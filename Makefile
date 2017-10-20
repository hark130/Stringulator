CFLAGS = -O -std=c++11

CC = g++ 

ALL:  
		$(CC) $(CFLAGS) -o main.exe main.cpp Stringulator.cpp 

CLEAN: 
		rm -f *.o *.exe