all: shell.o
	gcc shell.o
run:
	./a.out
shell.o: shell.c 
	gcc -c shell.c
clean:
	rm *.o
	rm a.out
