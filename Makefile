all:
	gcc -o dcttest -O3 -ansi -pedantic -Wall main.c dct.c snd.c -lm -lsndfile -fopenmp
 
