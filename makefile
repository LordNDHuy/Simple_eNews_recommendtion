Objs = main.o functionality.o CLI.o
CC   = gcc
Cflag =  -Wall -std=c11 -g -c -lm

Lflag =  -Wall -std=c11 -g -lm

.PHONY: clean

main: $(Objs)
	$(CC) $(Lflag) -o main $(Objs)
main.o: main.c functionality.h CLI.h
	$(CC) $(Cflag) main.c
functionality.o: functionality.c functionality.h CLI.h
	$(CC) $(Cflag) functionality.c
CLI.o: CLI.c CLI.h functionality.h
	$(CC) $(Cflag) CLI.c
clean:
	\rm *.o
