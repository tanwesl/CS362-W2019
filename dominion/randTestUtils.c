#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"

int activeCards[17] = {
	-1,
	-1,
	-1,
	-1,
	-1,
	-1,
	-1,
	-1,
	-1,
	-1,
	0,
	1,
	2,
	3,
	4,
	5,
	6
};

void initRandom(struct gameState* blankState){
	srand(time(NULL));
	int i, j;
	int totalCards;
	int zeroCount;
	char reloop;

	int maxVal;
	zeroCount = 0;

	//player info for game
	blankState->numPlayers = 2 + rand()%3;
	blankState->whoseTurn = rand()%blankState->numPlayers;
	//reset list of cards-in-use
	for(i = 0; i < 10; i++){
		activeCards[i] = -1;
	}
	//gen random list of non-repeating kingdom cards into cards-in-use list
	for(i = 0; i < 10; i++){
		activeCards[i] = 7 + rand()%20;
		for(j = 0; j < 10; j ++){
			if(j != i){
				if(activeCards[j] == activeCards[i]){
					i--;
				}
			}
		}
	}
	//gen random supply numbers for curse, victory, treasures
	//supply counts based on player count when needed
	//track number of empties to prevent end-game condition
	for(i = 0; i < 7; i++){
		switch(i){
			case(curse):
				maxVal = blankState->numPlayers*10 - 9;
				break;
			case(estate):
			case(duchy):
			case(province):
				if(blankState->numPlayers > 2){
					maxVal = 9;
				}
				else{
					maxVal = 13;
				}
				break;
			case(copper):
				maxVal = 61;
				break;
			case(silver):
				maxVal = 41;
				break;
			case(gold):
				maxVal = 31;
				break;
		}
		do{
			reloop = 0;
			blankState->supplyCount[i] = rand()%maxVal;
			if(blankState->supplyCount[i] == 0){
				if(i == province){
					reloop = 1;
				}
				else{
					zeroCount++;
				}
			}
			if(zeroCount == 3){
				zeroCount--;
				reloop = 1;
			}
		}while(reloop);		
	}
	//gen random supply numbers for kingdom cards
	//track empty piles to prevent end-game condition
	for(i = 0; i < 10; i++){
		blankState->supplyCount[activeCards[i]] = rand()%11;
		if(blankState->supplyCount[activeCards[i]] == 0){
			zeroCount++;
		}
		if(zeroCount == 3){
			i--;
			zeroCount--;
		}
	}
	for(i = 0; i < blankState->numPlayers; i++){
		//give a player a total of up to 150 across deck, hand, discard; more realistic than MAX_HAND=500;
		//still unrealistic as player would need to be monopolizing card gain in 3+ player game
		//gen random number 1-150 for handCount
		totalCards = 1 + rand()%150;
		//set hand size to random value from 1-150
		//hand must always be at least 1 as there is a card being played
		blankState->handCount[i] = 1 + rand()%(totalCards);
		//reduce card allowance for deck, discard, played card gen sizes based on hand size
		totalCards-=blankState->handCount[i];
		//gen random hand based on cards-in-use and hand size
		for(j = 0; j < blankState->handCount[i]; j++){
			blankState->hand[i][j] = activeCards[rand()%17];
		}
		//repeat for deck
		blankState->deckCount[i] = rand()%(totalCards+1);
		totalCards-=blankState->deckCount[i];
		for(j = 0; j < blankState->deckCount[i]; j++){
			blankState->deck[i][j] = activeCards[rand()%17];
		}
		//repeat for discard
		if(i == blankState->whoseTurn){
			blankState->discardCount[i] = rand()%(totalCards+1);
			totalCards-=blankState->discardCount[i];
			for(j = 0; j < blankState->discardCount[i]; j++){
				blankState->discard[i][j] = activeCards[rand()%17];
			}
			//also gen played cards for active player
			blankState->playedCardCount = totalCards;
			for(j = 0; j < blankState->discardCount[i]; j++){
				blankState->playedCards[j] = activeCards[rand()%17];
			}
		}
		else{
			blankState->discardCount[i] = totalCards;
			for(j = 0; j < blankState->discardCount[i]; j++){
				blankState->discard[i][j] = activeCards[rand()%17];
			}
		}
	}
	//Set game states:
	//phase is the action phase so it must be 1 by precondition
	blankState->phase = 1;
	//in action phase so coin count can only be treasure cards + bonus from actions
	updateCoins(blankState->whoseTurn, blankState, 0);
	//in action phase so must be at least one action and buy
	blankState->numActions = 1 + rand()%10;
	blankState->numBuys = 1 + rand()%10;
}

void printState(struct gameState* testState, int pre_post){
	int i;
	printf("/");
	for(i = 0; i < 35; i++){
		printf("*");
	}
	if(!pre_post){
		printf("\n *\n *\tPRETEST\n *\n");
	}
	else{
		printf("\n *\n *\tPOSTTEST\n *\n ");
	}
	for(i = 0; i < 35; i++){
		printf("*");
	}
	printf("/\n");
	printf("Player Count:\n\t%d\nCards Used:\n", testState->numPlayers);
	for(i = 0; i < 17; i++){
		printf("\t%d:\t%d\n", activeCards[i], testState->supplyCount[activeCards[i]]);
	}
	printf("Active Player:\n\t%d\nPhase:\n\t%d\nAction Count:\n\t%d\nCoin Count:\n\t%d\nBuy Count:\n\t%d\n", testState->whoseTurn, testState->phase,  testState->numActions, testState->coins, testState->numBuys);
	printf("Player Hand:\n\tSize:\t%d\n", testState->handCount[testState->whoseTurn]);
	printf("\tCards:\n");
	for(i = 0; i < testState->handCount[testState->whoseTurn]; i++){
		printf("\t\t%d\n", testState->hand[testState->whoseTurn][i]);
	}
	printf("Player Deck:\n\tSize:\t%d\n", testState->deckCount[testState->whoseTurn]);
	printf("\tCards:\n");
	for(i = 0; i < testState->deckCount[testState->whoseTurn]; i++){
		printf("\t\t%d\n", testState->deck[testState->whoseTurn][i]);
	}
	printf("Player Discard:\n\tSize:\t%d\n", testState->discardCount[testState->whoseTurn]);
	printf("\tCards:\n");
	for(i = 0; i < testState->discardCount[testState->whoseTurn]; i++){
		printf("\t\t%d\n", testState->discard[testState->whoseTurn][i]);
	}
	printf("Played:\n\tSize:\t%d\n", testState->playedCardCount);
	printf("\tCards:\n");
	for(i = 0; i < testState->playedCardCount; i++){
		printf("\t\t%d\n", testState->playedCards[i]);
	}
}
