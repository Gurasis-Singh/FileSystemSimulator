all: main

main: main.c file_system.c
	gcc -o fs main.c file_system.c

clean:
	rm -f fs