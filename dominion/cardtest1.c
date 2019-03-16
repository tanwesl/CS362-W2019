#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TEST_DECK	10

int main(){
	long passFailFlags = 0;
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int r;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState* testState = malloc(sizeof(struct gameState));	
	srand(time(NULL));
	
	r = initializeGame(numPlayer, k, seed, testState);
	assert(!r);
	testState->whoseTurn=0;
	testState->deckCount[0]=TEST_DECK;
	testState->handCount[0]=0;
	for(i=0; i < MAX_HAND; i++)
	{
		testState->hand[0][i] = curse;
	}
	for(i=0; i < TEST_DECK; i++)
	{
		testState->deck[0][i] = curse;
	}
	testState->deck[0][0]=copper;
	testState->deck[0][TEST_DECK-1]=copper;
	r = cardEffect(adventurer, 0, 0, 0, testState, 0, 0);
	assert(!r);
	if(testState->handCount[0] == 2)
	{
		printf("Adventurer correctly counts copper from deck\n");
	}
	else
	{
		printf("Adventurer does not correctly count copper from deck\n");
		passFailFlags |= 1 << 0;
	}
	if((testState->hand[0][0] == copper) && (testState->hand[0][1] == copper))
	{
		printf("Adventurer correctly adds copper to hand\n");
	}
	else
	{
		printf("Adventurer does not correctly add copper to hand\n");
		passFailFlags |= 1 << 1;
	}
	
	r = initializeGame(numPlayer, k, seed, testState);
	assert(!r);
	testState->whoseTurn=0;
	testState->deckCount[0]=TEST_DECK;
	testState->handCount[0]=0;
	for(i=0; i < MAX_HAND; i++)
	{
		testState->hand[0][i] = curse;
	}
	for(i=0; i < TEST_DECK; i++)
	{
		testState->deck[0][i] = curse;
	}
	testState->deck[0][0]=silver;
	testState->deck[0][TEST_DECK-1]=silver;
	r = cardEffect(adventurer, 0, 0, 0, testState, 0, 0);
	assert(!r);
	if(testState->handCount[0] == 2)
	{
		printf("Adventurer correctly counts silver from deck\n");
	}
	else
	{
		printf("Adventurer does not correctly count silver from deck\n");
		passFailFlags |= 1 << 2;
	}
	if((testState->hand[0][0] == silver) && (testState->hand[0][1] == silver))
	{
		printf("Adventurer correctly adds silver to hand\n");
	}
	else
	{
		printf("Adventurer does not correctly add silver to hand\n");
		passFailFlags |= 1 << 3;
	}
	
	r = initializeGame(numPlayer, k, seed, testState);
	assert(!r);
	testState->whoseTurn=0;
	testState->deckCount[0]=TEST_DECK;
	testState->handCount[0]=0;
	for(i=0; i < MAX_HAND; i++)
	{
		testState->hand[0][i] = curse;
	}
	for(i=0; i < TEST_DECK; i++)
	{
		testState->deck[0][i] = curse;
	}
	testState->deck[0][0]=gold;
	testState->deck[0][TEST_DECK-1]=gold;
	r = cardEffect(adventurer, 0, 0, 0, testState, 0, 0);
	assert(!r);
	if(testState->handCount[0] == 2)
	{
		printf("Adventurer correctly counts gold from deck\n");
	}
	else
	{
		printf("Adventurer does not correctly count gold from deck\n");
		passFailFlags |= 1 << 4;
	}
	if((testState->hand[0][0] == gold) && (testState->hand[0][1] == gold))
	{
		printf("Adventurer correctly adds gold to hand\n");
	}
	else
	{
		printf("Adventurer does not correctly add gold to hand\n");
		passFailFlags |= 1 << 5;
	}
	
	r = initializeGame(numPlayer, k, seed, testState);
	assert(!r);
	testState->whoseTurn=0;
	testState->deckCount[0]=TEST_DECK;
	testState->handCount[0]=0;
	for(i=0; i < MAX_HAND; i++)
	{
		testState->hand[0][i] = curse;
	}
	for(i=0; i < TEST_DECK; i++)
	{
		testState->deck[0][i] = curse;
	}
	testState->deck[0][0]=copper;
	testState->discardCount[0]=1;
	testState->discard[0][0]=copper;
	r = cardEffect(adventurer, 0, 0, 0, testState, 0, 0);
	assert(!r);
	if(testState->handCount[0] == 2)
	{
		printf("Adventurer correctly counts from discard and deck\n");
	}
	else
	{
		printf("Adventurer does not correctly count from discard and deck\n");
		passFailFlags |= 1 << 6;
	}
	if((testState->hand[0][0] == copper) && (testState->hand[0][1] == copper))
	{
		printf("Adventurer correctly adds to hand from discard and deck\n");
	}
	else
	{
		printf("Adventurer does not correctly add to hand from discard and deck\n");
		passFailFlags |= 1 << 7;
	}
	
	r = initializeGame(numPlayer, k, seed, testState);
	assert(!r);
	testState->whoseTurn=0;
	testState->deckCount[0]=TEST_DECK;
	testState->handCount[0]=0;
	for(i=0; i < MAX_HAND; i++)
	{
		testState->hand[0][i] = curse;
	}
	for(i=0; i < TEST_DECK; i++)
	{
		testState->deck[0][i] = curse;
	}
	testState->deck[0][0]=copper;
	r = cardEffect(adventurer, 0, 0, 0, testState, 0, 0);
	assert(!r);
	if(testState->handCount[0] == 1)
	{
		printf("Adventurer correctly counts single treasure when two not available\n");
	}
	else
	{
		printf("Adventurer does not correctly count single treasure when two not available\n");
		passFailFlags |= 1 << 8;
	}
	if((testState->hand[0][0] == copper) && (testState->hand[0][1] != copper))
	{
		printf("Adventurer correctly adds single treasure to hand when two not available\n");
	}
	else
	{
		printf("Adventurer does not correctly add single treasure to hand when two not available\n");
		passFailFlags |= 1 << 9;
	}
	
	printf("\n");
	if(passFailFlags)
	{
		printf("Test Failed with Code 0x%08X\n\n", (int)passFailFlags);
	}
	else
	{
		printf("Test Successful!\n\n");
	}
	
	return 0;
}
