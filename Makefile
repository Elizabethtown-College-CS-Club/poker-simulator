poker: poker.c poker.h deck.o evaluator.o
	gcc poker.c arrays.c deck.o evaluator.o -o poker -std=c99

test: test.c deck.o evaluator.o
	gcc test.c arrays.c deck.o evaluator.o -o test -std=c99

evaluator.o: evaluator.c evaluator.h deck.h
	gcc -c evaluator.c arrays.c -std=c99

deck.o: deck.c deck.h
	gcc -c deck.c -std=c99

clean:
	rm -rf *.o main
