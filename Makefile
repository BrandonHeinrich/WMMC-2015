schedule: main.c functions.h poss.c data.h testdata.h
	gcc main.c
	./a.out
	
possibilities:
	./possibilities.out

test:
	./testdata.out
	
full:
	./fulldata.out
