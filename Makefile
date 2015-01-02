all:
	gcc -o dcttest -O2 -ansi -pedantic -Wall main.c dct.c snd.c -lm -lsndfile
 
