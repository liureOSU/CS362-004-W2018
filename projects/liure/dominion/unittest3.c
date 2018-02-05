#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/**********************************************************************
	CS362: Software Engineering II
	Unit Test 3: fullDeckCount
	Author: Reed Liu
	Date: 2/2/2018
***********************************************************************/

int main() {

	printf("\nBEGIN UNIT TEST 3: fullDeckCount\n\n");
	// Initialize gameState with relevant information.
	struct gameState *baseGame = newGame();
	struct gameState *testGame = newGame();
	baseGame->handCount[0] = 5;
	baseGame->deckCount[0] = 5;
	baseGame->discardCount[0] = 3;

	baseGame->hand[0][0] = copper;
	baseGame->hand[0][1] = copper;
	baseGame->hand[0][2] = copper;
	baseGame->hand[0][3] = estate;
	baseGame->hand[0][4] = copper;

	baseGame->deck[0][0] = silver;
	baseGame->deck[0][1] = estate;
	baseGame->deck[0][2] = silver;
	baseGame->deck[0][3] = silver;
	baseGame->deck[0][4] = estate;

	baseGame->discard[0][0] = gold;
	baseGame->discard[0][1] = estate;
	baseGame->discard[0][2] = estate;
	// Seed player 0 with hand, deck, and discard coppers and estates.

	// TEST 1: Check number of coppers in handCount is correct. Only hand has coppers.
	memcpy(&testGame, &baseGame, sizeof(struct gameState*));
	printf("TEST 1: Check number of coppers in handCount is correct. Only hand has coppers.\n");
	if (fullDeckCount(0,copper,testGame) == 4) {
		printf("TEST 1 PASSED - Counted (4) coppers.\n");
	}
	else {
		printf("TEST 1 FAILED - Copper count incorrect, shows %d\n", fullDeckCount(0, copper, testGame));
	}
	printf("\n");

	// TEST 2: Check number of silver in deckCount is correct. Only deck has silver.
	printf("TEST 2: Check number of silvers in deckCount is correct. Only deck has silver.\n");
	if (fullDeckCount(0, silver, testGame) == 3) {
		printf("TEST 2 PASSED - Counted (3) silvers..\n");
	}
	else {
		printf("TEST 2 FAILED - Silver count incorrect, shows %d\n", fullDeckCount(0, silver, testGame));
	}
	printf("\n");

	// TEST 3: Check number of gold in discardCount is correct. Only discard has gold.
	printf("TEST 3: Check number of gold in discardCount is correct. Only discard has gold.\n");
	if (fullDeckCount(0, gold, testGame) == 1) {
		printf("TEST 3 PASSED - Counted (1) gold..\n");
	}
	else {
		printf("TEST 3 FAILED - Gold count incorrect, shows %d\n", fullDeckCount(0, gold, testGame));
	}
	printf("\n");

	// TEST 4: Check that total number of estates across deck, hand, and discard is correct.
	printf("TEST 4: Check that total number of estates across deck, hand, and discard is correct.\n");
	if (fullDeckCount(0, estate, testGame) == 5) {
		printf("TEST 4 PASSED - Counted (5) estates..\n");
	}
	else {
		printf("TEST 4 FAILED - Estate count incorrect, shows %d\n", fullDeckCount(0, estate, testGame));
	}
	printf("\n");

	return 0;
}