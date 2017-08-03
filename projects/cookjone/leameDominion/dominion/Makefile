CFLAGS = -Wall -fpic -coverage -lm

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g -std=c99 randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g -std=c99 randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g -std=c99 randomtestcard2.c dominion.o rngs.o $(CFLAGS)

assignment4_test_suite: randomtestadventurer randomtestcard1 randomtestcard2

rta.out: randomtestadventurer
	./randomtestadventurer &> randomtestadventurer.out
	gcov dominion.c -b >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

rtc1.out: randomtestcard1
	./randomtestcard1 >> randomtestcard1.out
	gcov dominion.c -b >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

rtc2.out: randomtestcard2
	./randomtestcard2 >> randomtestcard2.out
	gcov dominion.c -b >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g -std=c99 unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g -std=c99 unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g -std=c99 unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g -std=c99 unittest4.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g -std=c99 cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g -std=c99 cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g -std=c99 cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g -std=c99 cardtest4.c dominion.o rngs.o $(CFLAGS)

assignment3_test_suite: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4

unittestresults.out: assignment3_test_suite
	./unittest1 &> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	./unittest2 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	./cardtest2 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	./cardtest3 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresults.out
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard


assignment5testresults: randomtestadventurer.c randomtestcard1.c randomtestcard2.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c unittest1.c unittest2.c unittest3.c unittest4.c dominion.c rngs.c
	echo "Results for Assignment 5 test suit:" > assignment5testresults.out
	echo "unittest1.c:" >> assignment5testresults.out
	gcc -o unittest1 -g  unittest1.c dominion.c rngs.c $(CFLAGS)
	./unittest1 >> assignment5testresults.out
	gcov unittest1.c >> assignment5testresults.out
	gcov dominion.c >> assignment5testresults.out
	echo "unittest2.c:" >> assignment5testresults.out
	gcc -o unittest2 -g  unittest2.c dominion.c rngs.c $(CFLAGS)
	./unittest2 >> assignment5testresults.out
	gcov unittest2.c >> assignment5testresults.out
	gcov dominion.c >> assignment5testresults.out
	echo "unittest3.c:" >> assignment5testresults.out
	gcc -o unittest3 -g  unittest3.c dominion.c rngs.c $(CFLAGS)
	./unittest3 >> assignment5testresults.out
	gcov unittest3.c >> assignment5testresults.out
	gcov dominion.c >> assignment5testresults.out
	echo "unittest4.c:" >> assignment5testresults.out
	gcc -o unittest4 -g  unittest4.c dominion.c rngs.c $(CFLAGS)
	./unittest4 >> assignment5testresults.out
	gcov unittest4.c >> assignment5testresults.out
	gcov dominion.c >> assignment5testresults.out
	echo "cardtest1.c:" >> assignment5testresults.out
	gcc -o cardtest1 -g  cardtest1.c dominion.c rngs.c $(CFLAGS)
	./cardtest1 >> assignment5testresults.out
	gcov cardtest1.c >> assignment5testresults.out
	gcov dominion.c >> assignment5testresults.out
	echo "cardtest2.c:" >> unittestresults.out
	gcc -o cardtest2 -g  cardtest2.c dominion.c rngs.c $(CFLAGS)
	./cardtest2 >> assignment5testresults.out
	gcov cardtest2.c >> assignment5testresults.out
	gcov dominion.c >> assignment5testresults.out
	echo "cardtest3.c:" >> assignment5testresults.out
	gcc -o cardtest3 -g  cardtest3.c dominion.c rngs.c $(CFLAGS)
	./cardtest3 >> assignment5testresults.out
	gcov cardtest3.c >> assignment5testresults.out
	gcov dominion.c >> assignment5testresults.out
	echo "cardtest4.c:" >> assignment5testresults.out
	gcc -o cardtest4 -g  cardtest4.c dominion.c rngs.c $(CFLAGS)
	./cardtest4 >> assignment5testresults.out
	gcov cardtest4.c >> assignment5testresults.out
	gcov dominion.c >> assignment5testresults.out
	echo "randomtestcard1.c:" >> assignment5testresults.out
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.c rngs.c $(CFLAGS)
	./randomtestcard1 >> assignment5testresults.out
	gcov randomtestcard1.c >> assignment5testresults.out
	gcov dominion.c >> assignment5testresults.out
	echo "randomtestcard2.c:" >> assignment5testresults.out
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.c rngs.c $(CFLAGS)
	./randomtestcard2 >> assignment5testresults.out
	gcov randomtestcard2.c >> assignment5testresults.out
	gcov dominion.c >> assignment5testresults.out
	echo "randomtestadventurer.c:" >> assignment5testresults.out
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.c rngs.c $(CFLAGS)
	./randomtestadventurer >> assignment5testresults.out
	gcov randomtestadventurer.c >> assignment5testresults.out
	gcov dominion.c >> assignment5testresults.out

clean:
	rm -f *.o badTestDrawCard playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestadventurer randomtestcard1 randomtestcard2
	rm -r *.dSYM
