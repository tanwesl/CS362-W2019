#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "randTestUtils.h"

#define NOISY 0

int main(void)
{
	int passFailFlags = 0;
	struct gameState* testState = malloc(sizeof(struct gameState));
	struct gameState pretestState;
	time_t testTime = time(NULL);
	int result;

	while(difftime(time(NULL),testTime) < 30){
		initRandom(testState);
#if NOISY
		printState(testState, 0);
#endif
		pretestState = *testState;
		result = cardEffect(smithy, 0, 0, 0, testState, rand()%testState->handCount[testState->whoseTurn], 0);
		assert(!result);
#if NOISY
		printState(testState, 1);
#endif
		if(testState->handCount[pretestState.whoseTurn] != pretestState.handCount[pretestState.whoseTurn] + 2){
#if NOISY
			printf("Incorrect number of cards in player's hand.\n");
#endif
			passFailFlags |= 1 << 0;
		}
	}
	if(passFailFlags){
		printf("Test Failed with Error Code 0x%08X\n", passFailFlags);
	}
	else{
		printf("All tests successful.\n");
	}
	return 0;
}
