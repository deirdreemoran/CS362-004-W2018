//cardtest4.c
// Name: Deirdre Moran
// Function:  Tests the adventurer card


/*
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "myAssert.h"
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>


#define TESTCARD "adventurer"

int main() {
    int seed = 1000;
	int numPlayers = 2;
    int thisPlayer = 0;
    int i, j;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int v[3] = {estate, duchy, province};
	int t[3] = {copper, silver, gold};
	int cpr = 4;
	int slvr = 5;
	int gld = 6;
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// call adventurer cardEffect
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, 0);


	printf("----------------- Testing Card: %s ----------------\n\n", TESTCARD);
	// ----------- TEST 1: handCount of current player has increased by 2:  drawCard--------------
	printf("TEST 1: two treasures are removed from deck and placed in hand\n");
	printf("handCount is %d, expected %d\n\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 2);
	myAssert(G.handCount[thisPlayer] + 2 == testG.handCount[thisPlayer], __FILE__, __LINE__);


	// ----------- TEST 2: the 2 extra cards should come from discard or deck --------------
	printf("TEST 2: the 2 extra cards should come from discard or deck \n");

	// Check that the two cards came from discard or deck
	// the difference between G and testG should be 2
		printf("Difference is %d, expected %d\n\n",  G.discardCount[thisPlayer] + G.deckCount[thisPlayer] - testG.discardCount[thisPlayer] - testG.deckCount[thisPlayer], 2);
		myAssert(G.discardCount[thisPlayer] + G.deckCount[thisPlayer] == testG.discardCount[thisPlayer] + testG.deckCount[thisPlayer] + 2, __FILE__, __LINE__);

	// ----------- TEST 3: 2 drawn cards should be treasure cards --------------
	printf("TEST 3: 2 drawn cards should be treasure cards \n");

	// Check that treasure cards were drawn, they should be the top two cards of hand
	printf("treasure card is %d, expected %d or %d or %d\n", testG.hand[thisPlayer][testG.handCount[thisPlayer]-1], 4 , 5, 6);
	printf("treasure card is %d, expected %d or %d or %d\n\n", testG.hand[thisPlayer][testG.handCount[thisPlayer]-2], 4, 5, 6);

	myAssert((testG.hand[thisPlayer][testG.handCount[thisPlayer]-1] == cpr) || (testG.hand[thisPlayer][testG.handCount[thisPlayer]-1] == slvr) || (testG.hand[thisPlayer][testG.handCount[thisPlayer]-1] == gld), __FILE__, __LINE__);
	myAssert((testG.hand[thisPlayer][testG.handCount[thisPlayer]-2] == cpr) || (testG.hand[thisPlayer][testG.handCount[thisPlayer]-2] == slvr) || (testG.hand[thisPlayer][testG.handCount[thisPlayer]-2] == gld), __FILE__, __LINE__);

	// ----------- TEST 4: state of game should not change for other players --------------
	printf("TEST 4: state of game should not change for other players  \n");

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
	return 0;
}


