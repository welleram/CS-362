CFLAGS = -Wall -fpic -coverage -lm

runtest: testme.c
	gcc -o testme -g  testme.c $(CFLAGS)
	./testme

clean:
	-rm -f *.gcda *.gcno testme
	-rm -r testme.dSYM
