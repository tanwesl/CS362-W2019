CFLAGS= -Wall -fpic -coverage -lm -std=c99
COVERAGE= -fprofile-arcs -ftest-coverage -O0

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

tests: dominion.o rngs.o randTestUtils.o
	gcc -o unittest1 unittest1.c dominion.o rngs.o $(CFLAGS) $(COVERAGE)
	gcc -o unittest2 unittest2.c dominion.o rngs.o $(CFLAGS) $(COVERAGE)
	gcc -o unittest3 unittest3.c dominion.o rngs.o $(CFLAGS) $(COVERAGE)
	gcc -o unittest4 unittest4.c dominion.o rngs.o $(CFLAGS) $(COVERAGE)
	gcc -o cardtest1 cardtest1.c dominion.o rngs.o $(CFLAGS) $(COVERAGE)
	gcc -o cardtest2 cardtest2.c dominion.o rngs.o $(CFLAGS) $(COVERAGE)
	gcc -o cardtest3 cardtest3.c dominion.o rngs.o $(CFLAGS) $(COVERAGE)
	gcc -o cardtest4 cardtest4.c dominion.o rngs.o $(CFLAGS) $(COVERAGE)
	gcc -o randomtestcard1 randomtestcard1.c dominion.o rngs.o randTestUtils.o $(CFLAGS) $(COVERAGE)
	gcc -o randomtestcard2 randomtestcard2.c dominion.o rngs.o randTestUtils.o $(CFLAGS) $(COVERAGE)
	gcc -o randomtestadventurer randomtestadventurer.c dominion.o rngs.o randTestUtils.o $(CFLAGS) $(COVERAGE)

unittestresults: dominion.o rngs.o
	gcc -o unittest1 unittest1.c dominion.o rngs.o $(CFLAGS) $(COVERAGE)
	./unittest1 &>unittestresults.out
	gcov -f dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	gcc -o unittest2 unittest2.c dominion.o rngs.o $(CFLAGS) $(COVERAGE)
	./unittest2 >> unittestresults.out
	gcov -f dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	gcc -o unittest3 unittest3.c dominion.o rngs.o $(CFLAGS) $(COVERAGE)
	./unittest3 >> unittestresults.out
	gcov -f dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	gcc -o unittest4 unittest4.c dominion.o rngs.o $(CFLAGS) $(COVERAGE)
	./unittest4 >> unittestresults.out
	gcov -f dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	gcc -o cardtest1 cardtest1.c dominion.o rngs.o $(CFLAGS) $(COVERAGE)
	./cardtest1 >> unittestresults.out
	gcov -f dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	gcc -o cardtest2 cardtest2.c dominion.o rngs.o $(CFLAGS) $(COVERAGE)
	./cardtest2 >> unittestresults.out
	gcov -f dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	gcc -o cardtest3 cardtest3.c dominion.o rngs.o $(CFLAGS) $(COVERAGE)
	./cardtest3 >> unittestresults.out
	gcov -f dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	gcc -o cardtest4 cardtest4.c dominion.o rngs.o $(CFLAGS) $(COVERAGE)
	./cardtest4 >> unittestresults.out
	gcov -f dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out


randTestUtils.o: randTestUtils.h randTestUtils.c
	gcc -c randTestUtils.c $(CFLAGS)

randomTest: dominion.o rngs.o randTestUtils.o
	gcc -o randomtestcard1 randomtestcard1.c dominion.o rngs.o randTestUtils.o $(CFLAGS) $(COVERAGE)
	./randomtestcard1 &> randomtestresults.out
	gcov -f dominion.c >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out
	gcc -o randomtestcard2 randomtestcard2.c dominion.o rngs.o randTestUtils.o $(CFLAGS) $(COVERAGE)
	./randomtestcard2 >> randomtestresults.out
	gcov -f dominion.c >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out
	gcc -o randomtestadventurer randomtestadventurer.c dominion.o rngs.o randTestUtils.o $(CFLAGS) $(COVERAGE)
	./randomtestadventurer >> randomtestresults.out
	gcov -f dominion.c >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
