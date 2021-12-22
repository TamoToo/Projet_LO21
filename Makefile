main: main.o main_functions.o
	gcc -o main main.o main_functions.o -lm

main_functions.o: main_functions.c
	gcc -c -o main_functions.o main_functions.c 

main.o: main.c
	gcc -c -o main.o main.c