all: shell.o pipes.o redirect.o
	gcc shell.o pipes.o redirect.o
run:
	./a.out

test:
	./test.sh

pipes.o: pipes.c pipes.h
	gcc -c pipes.c

redirect.o: redirect.c redirect.h
	gcc -c redirect.c

shell.o: shell.c shell.h
	gcc -c shell.c
clean:
	rm *.o
	rm a.out
