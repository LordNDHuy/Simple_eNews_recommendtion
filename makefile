Objs = main.o functionality.o CLI.o
CC   = gcc
Cflag =  -Wall -std=c11 -g -c 

Lflag =  -Wall -std=c11 -g 
Lm = -lm -lc -lgcc

.PHONY: clean

main: $(Objs)
	$(CC) $(Lflag) -o main $(Objs) $(Lm)
main.o: main.c functionality.h CLI.h
	$(CC) $(Cflag) main.c $(Lm)
functionality.o: functionality.c functionality.h CLI.h
	$(CC) $(Cflag) functionality.c $(Lm)
CLI.o: CLI.c CLI.h functionality.h
	$(CC) $(Cflag) CLI.c $(Lm)
clean:
	\rm *.o
