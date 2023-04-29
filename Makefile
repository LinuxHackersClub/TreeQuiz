CC=gcc
COPTS=-Wall -lm

all:
	${CC} ${COPTS} -o main main.c tree.c

run: all
	@./main
