Objs = main.o functionality.o
CC   = g++
Cflag =  -Wall -std=c++11 -g -c

Lflag =  -Wall -std=c++11 -g

.PHONY: clean

main: $(Objs)
	$(CC) $(Lflag) -o main $(Objs)
main.o: main.c functionality.h
	$(CC) $(Cflag) main.c
functionality.o: functionality.c functionality.h
	$(CC) $(Cflag) functionality.c

clean:
	\rm *.o
