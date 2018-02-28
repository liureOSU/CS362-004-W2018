#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/**********************************************************************
	CS362: Software Engineering II
	Unit Test 2: discardCard
	Author: Reed Liu
	Date: 2/2/2018
***********************************************************************/

int main() {
	
	printf("\nBEGIN UNIT TEST 2: discardCard\n\n");
	// Initialize gameState with relevant information.
	struct gameState *baseGame = newGame();
	struct gameState *testGame = newGame();
	baseGame->handCount[0] = 5;
	baseGame->handCount[1] = 3;
	baseGame->hand[0][0] = gold;
	baseGame->hand[0][1] = estate;
	baseGame->hand[0][2] = village;
	baseGame->hand[0][3] = smithy;
	baseGame->hand[0][4] = adventurer;
	baseGame->hand[1][0] = silver;
	baseGame->hand[1][1] = province;
	baseGame->hand[1][2] = copper;
	baseGame->playedCardCount = 0;

	memcpy(&testGame, &baseGame, sizeof(struct gameState*));
	discardCard(2, 0, testGame, 0);
	// TEST 1: Check that not removing the last card from a hand greater than one correctly decrements hand count.
	printf("TEST 1: Check that playing VILLAGE correctly decreases handCount by one from hand of 5.\n");
	if (testGame->handCount[0] == 4) {
		printf("TEST 1 PASSED - handCount correct value (4).\n");
	}
	else {
		printf("TEST 1 FAILED - handCount incorrect, shows %d\n", testGame->handCount[0]);
	}
	printf("\n");

	// TEST 2: Check that the last card in hand (adventurer) replaced previous village in handPos.
	printf("TEST 2: Check that last card in hand (ADVENTURER) replaced previous VILLAGE position (2).\n");
	if (testGame->hand[0][2] == adventurer) {
		printf("TEST 2 PASSED - Adventurer now in discarded Village's previous position.\n");
	}
	else {
		printf("TEST 2 FAILED - Adventurer did not go into Village's previous position.\n");
	}
	printf("\n");

	// TEST 3: Check that removing the last card in hand decrements handCount correctly.
	discardCard(3, 0, testGame, 0);
	printf("TEST 3: Check that removing the last card in hand (Smithy) decrements handCount correctly.\n");
	if (testGame->handCount[0] == 3) {
		printf("TEST 3 PASSED - handCount correct value (3).\n");
	}
	else {
		printf("TEST 3 FAILED - handCount incorrect, shows %d\n.", testGame->handCount[0]);
	}
	printf("\n");

	// TEST 4: Check that a card that is trashed does not add to the played pile.
	discardCard(0, 0, testGame, 1);
	printf("TEST 4: Check that a card that is trashed does not add to the played pile.\n");
	if (testGame->playedCardCount == 2) {
		printf("TEST 4 PASSED - playedCardCount shows correct value.\n");
	}
	else {
		printf("TEST 4 FAILED - playedCardCount incorrect, shows %d\n.", testGame->playedCardCount);
	}
	printf("\n");

	// TEST 5: Check that removing all cards from a player's hand results in handCount = 0.
	discardCard(0, 0, testGame, 0);
	discardCard(0, 0, testGame, 0);
	printf("TEST 5: Check that removing all cards from a player's hand results in handCount = 0.\n");
	if (testGame->handCount[0] == 0) {
		printf("TEST 5 PASSED - handCount = 0\n");
	}
	else {
		printf("TEST 5 FAILED - handCount shows %d.\n", testGame->handCount[0]);
	}
	printf("\n");
	getchar();
	return 0;
}