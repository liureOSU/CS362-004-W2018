#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/**********************************************************************
	CS362: Software Engineering II
	Unit Test 4: fullDeckCount
	Author: Reed Liu
	Date: 2/2/2018
***********************************************************************/

int main() {

	printf("\nBEGIN UNIT TEST 3: handCard\n\n");
	// Initialize gameState with relevant information.
	struct gameState *baseGame = newGame();
	struct gameState *testGame = newGame();
	baseGame->numPlayers = 2;
	baseGame->whoseTurn = 0;
	baseGame->handCount[0] = 5;

	baseGame->hand[0][0] = copper;
	baseGame->hand[0][1] = silver;
	baseGame->hand[0][2] = gold;
	baseGame->hand[0][3] = duchy;
	baseGame->hand[0][4] = province;

	// TEST 1: Check number of coppers in handCount is correct. Only hand has coppers.
	memcpy(&testGame, &baseGame, sizeof(struct gameState*));
	printf("TEST 1: Check that each card in hand of 5 is correctly returned by handCard.\n");
	if (handCard(0,testGame) == copper && handCard(1,testGame) == silver &&
		handCard(2,testGame) == gold && handCard(3, testGame) == duchy &&
		handCard(4, testGame) == province) {
		printf("TEST 1 PASSED - Each card correctly returned by handCard.\n");
	}
	else {
		printf("TEST 1 FAILED - Cards were not correctly returned by handCard.\n");
	}
	printf("\n");

	return 0;
}