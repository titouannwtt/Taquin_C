
but: main

OFILES = main.o \
	log.o \
	quit.o \
	run_interface.o \
	run_game.o \
	run_animation.o \
	wait.o

CC = gcc

CFLAGS = -Wall -ansi -pedantic

.c.o:


main : $(OFILES)
	$(CC) $(CFLAGS) -o main $(OFILES) -lgraph



clean :
	-rm -f $(OFILES) main

.PHONY : but clean
