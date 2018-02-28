//cardtest3.c
// Name: Deirdre Moran
// Function:  Tests the council_room card


/*
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "myAssert.h"
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>


#define TESTCARD "council_room"

int main() {
    int seed = 1000;
	int numPlayers = 2;
    int thisPlayer = 0;
    int i, j;
    char * file = __FILE__;
	int drawFour = 4;
	int discardOne = 1;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	struct gameState G, testG;
	int v[3] = {estate, duchy, province};
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, 0);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: Handcount increases by 3 (4 cards drawn, 1 discarded) --------------
	printf("TEST 1: Handcount is 3 (4 cards drawn, 1 discarded) \n");

	printf("handCount is %d, expected %d\n\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 3);
	// Assert that testG.handCount = G.handCount - # discarded + # added to hand
	myAssert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + drawFour - discardOne, file, __LINE__);
	// Assert that the four cards came from player's deck

	// ----------- TEST 2: Deckcount decreases by 4 --------------
	printf("TEST 2: Deckcount decreases by 4 \n");
	printf("deckCount is %d, expected %d\n\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 4);
	myAssert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - drawFour, file, __LINE__);

	// ----------- TEST 3: PlayedPile increases by 1 --------------
	printf("TEST 3: PlayedPile increases by 1 \n");

	// Assert that playedPile has increased by one
	printf("playedCards = %d, expected %d\n\n", testG.playedCardCount, G.playedCardCount + 1);
	myAssert(testG.playedCardCount - discardOne == G.playedCardCount, file, __LINE__);

	// ----------- TEST 4: Every player draws a card --------------
		printf("TEST 4: Every player draws a card\n");

	//Assert other player(s) draws a card
	for (i = 1; i < numPlayers; i++){
		myAssert(testG.handCount[thisPlayer + i] == G.handCount[thisPlayer + i] + 1, file, __LINE__);
		myAssert(testG.deckCount[thisPlayer + i] == G.deckCount[thisPlayer + i] - 1, file, __LINE__);
		printf("handCount for player %d is %d, expected %d\n", i, testG.handCount[i], G.handCount[i] + 1);
	}

			// ----------- TEST 5: state of game should not change for other players (minus card drawn) --------------
				printf("\nTEST 5: state of game should not change for other players (minus card drawn) \n");

				//Assert other players are unaffected
				for (j = 1; j < numPlayers; j++){
					myAssert(testG.discardCount[thisPlayer + j] == G.discardCount[thisPlayer + j], __FILE__, __LINE__);
					//Assert that other player's hand, deck, and discard have exactly the same cards

					for (i = 0; i < testG.discardCount[thisPlayer + j]; i++){
							myAssert(testG.discard[thisPlayer + j][i] == G.discard[thisPlayer + j][i], __FILE__, __LINE__);
					}
						    printf("discardCount player %d is %d, expected %d\n", j, testG.discardCount[j], G.discardCount[j]);
				}
				//Assert that the number of coins has not changed
				myAssert(G.coins == testG.coins, __FILE__, __LINE__);

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


