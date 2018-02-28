//randomtestcard2.c
// Name: Deirdre Moran
// Function:  Tests the smithy card


/*
 * Include the following lines in your makefile:
 *
 * randomtestcard2: randomtestcard2.c dominion.o rngs.o
 *      gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "myAssert.h"
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define TESTCARD "smithy"
#define MAX_NUM_TESTS 1

int main() {
	srand(time(NULL));
    int seed;
    int index;
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;
	int treasure;
	int tempHand;
	int numPlayers = 2;
    int thisPlayer = 0;
    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	char * file = __FILE__;

	struct gameState G, testG;
	int v[3] = {estate, duchy, province};
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};


	// for all tests
	for(index = 0; index < MAX_NUM_TESTS; index++)
	{
		seed = rand();
		// initialize a game state and player cards
		initializeGame(MAX_PLAYERS, k, seed, &G);

		for(thisPlayer = 0; thisPlayer < MAX_PLAYERS; thisPlayer++)
		{
			// set random values for discard, hand, and deck counts
			G.discardCount[thisPlayer] = rand() % MAX_DECK;
			G.handCount[thisPlayer] = rand() % MAX_HAND;
			G.deckCount[thisPlayer] = rand() % MAX_DECK;
			// for each card in the three piles of each player, set random cards
			for (j = 0; j < G.discardCount[thisPlayer]; j++){
				G.discard[thisPlayer][j] = rand() % treasure_map + 1;
			}
			for (j = 0; j < G.handCount[thisPlayer]; j++){
				G.hand[thisPlayer][j] = rand() % treasure_map + 1;
			}
			for (j = 0; j < G.deckCount[thisPlayer]; j++){
				G.deck[thisPlayer][j] = rand() % treasure_map + 1;
			}
		}
		// set random handposition
		handpos = rand() % MAX_HAND;

		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);
		memcpy(&testG, &G, sizeof(struct gameState));
		cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, 0);

		printf("----------------- Testing Card: %s ----------------\n\n", TESTCARD);

		// ----------- TEST 1: handCount of current player has increased by 2 (3 drawn, 1 disgarded)--------------
		printf("TEST 1: handCount of current player increases by 2\n");
		printf("handCount is %d, expected %d\n\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 2);

		// Assert that testG.handCount = G.handCount - # discarded + # added to hand
		myAssert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 2, file, __LINE__);

		// ----------- TEST 2: the three drawn cards came from player's deck--------------
		printf("TEST 2: the three drawn cards came from player's deck\n");
		printf("deckCount is %d, expected %d\n\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 3);
		// Assert that the three cards came from player's deck
		myAssert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 3, file, __LINE__);


		// ----------- TEST 3: state of game should not change for other players --------------
		printf("TEST 3: state of game should not change for other players  \n");

		//Assert other players are unaffected
		for (j = 1; j < numPlayers; j++){
			myAssert(testG.handCount[thisPlayer + j] == G.handCount[thisPlayer + j], __FILE__, __LINE__);
			myAssert(testG.deckCount[thisPlayer + j] == G.deckCount[thisPlayer + j], __FILE__, __LINE__);
			myAssert(testG.discardCount[thisPlayer + j] == G.discardCount[thisPlayer + j], __FILE__, __LINE__);
			//Assert that other player's hand, deck, and discard have exactly the same cards
			for (i = 0; i < testG.handCount[thisPlayer + j]; i++){
				myAssert(testG.hand[thisPlayer + j][i] == G.hand[thisPlayer + j][i], __FILE__, __LINE__);
				}
			for (i = 0; i < testG.deckCount[thisPlayer + j]; i++){
					myAssert(testG.deck[thisPlayer + j][i] == G.deck[thisPlayer + j][i], __FILE__, __LINE__);
				}
			for (i = 0; i < testG.discardCount[thisPlayer + j]; i++){
					myAssert(testG.discard[thisPlayer + j][i] == G.discard[thisPlayer + j][i], __FILE__, __LINE__);
			}
					printf("handCount player %d is %d, expected %d\n", j, testG.handCount[j], G.handCount[j]);
					printf("discardCount player %d is %d, expected %d\n", j, testG.discardCount[j], G.discardCount[j]);
					printf("deckCount player %d is %d, expected %d\n", j, testG.deckCount[j], G.deckCount[j]);
		}
		//Assert that the number of coins has not changed
		myAssert(G.coins == testG.coins, __FILE__, __LINE__);

		//Assert that the number of numBuys has not changed
		myAssert(G.numBuys == testG.numBuys, __FILE__, __LINE__);

		//Assert Kingdom and Victory card piles do not change state
		for (i = 0; i < 3; i++) {
			printf("Card %d count = %d, expected = %d\n", v[i], testG.supplyCount[v[i]], G.supplyCount[v[i]]);
			myAssert(testG.supplyCount[v[i]] == G.supplyCount[v[i]], __FILE__, __LINE__);
		}
		for (i = 0; i < 10; i++) {
			printf("Card %d count = %d, expected = %d\n", k[i], testG.supplyCount[k[i]], G.supplyCount[k[i]]);
			myAssert(testG.supplyCount[k[i]] == G.supplyCount[k[i]], __FILE__, __LINE__);
		}
			printf("\n\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	}
	return 0;
}


