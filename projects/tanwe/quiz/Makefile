FLAGS= -g -Wall -fpic -coverage -lm -std=c99 -fprofile-arcs -ftest-coverage -O0

testme:
	gcc testme.c -o testme $(FLAGS)

run: 
	./testme
	gcov testme.c -f
