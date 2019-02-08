#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main()
{
	srand(time(NULL));
	struct gameState* testState = malloc(sizeof(struct gameState));
	int seed = 1000;
    int numPlayer = 2;
    int r;
	int i, j;
	long passFailFlags = 0;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	r = initializeGame(numPlayer, k, seed, testState);
	assert(!r);
	testState->deckCount[0]=0;

	if(!shuffle(0, testState))
	{
		printf("Function shuffle failed to detect invalid deck size\n");
		passFailFlags |= 1 << 0;
	}
	else
	{
		printf("\nFunction shuffle successfully detected invalid deck size\n");	
	}
	for(i = 0; i < MAX_DECK; i++){
		testState->deck[0][i] = rand()%17;
	}
	testState->deckCount[0]=MAX_DECK;
	printf("Deck Populated:\n");
	for(i = 0; i < MAX_DECK/20; i++){
		for(j = 0; j < 20; j++){
			printf("%d\t", testState->deck[0][j + (20*i)]);
		}
		printf("\n");
	}
	if(!shuffle(0, testState))
	{
		printf("Function shuffle successfully shuffled the deck:\n");
		for(i = 0; i < MAX_DECK/20; i++){
			for(j = 0; j < 20; j++){
				printf("%d\t", testState->deck[0][j + (20*i)]);
			}
			printf("\n");
		}
	}
	else
	{
		printf("Function shuffle failed to shuffle the deck\n");
		passFailFlags |= 1 << 1;
	}
	printf("\n");
	if(passFailFlags)
	{
		printf("Test Failed with Code 0x%08X\n\n", (int)passFailFlags);
	}
	else
	{
		printf("\nAll Tests Successful!\n\n");
	}
	
	return 0;
}
