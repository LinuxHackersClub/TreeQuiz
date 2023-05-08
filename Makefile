CC=gcc
COPTS=-Wall -lm

build:
	${CC} ${COPTS} -o main main.c tree.c

run: build
	@./main
