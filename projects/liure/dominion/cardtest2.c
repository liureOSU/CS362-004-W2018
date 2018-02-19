#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/**********************************************************************
	CS362: Software Engineering II
	Card Test 2: Adventurer
	Author: Reed Liu
	Date: 2/2/2018
***********************************************************************/

int main() {

	printf("\nBEGIN CARD TEST 2: Adventurer\n\n");
	// Initialize gameState with relevant information.
	struct gameState *baseGame = newGame();
	struct gameState *testGame = newGame();
	int cards[10] = { smithy, adventurer, salvager, sea_hag,
		council_room, feast, minion, great_hall, tribute, embargo };

	// Initialize new base game state and copy to test game state.
	initializeGame(2, cards, 1000, baseGame);
	memcpy(&testGame, &baseGame, sizeof(struct gameState*));
	testGame->hand[0][0] = adventurer;
	testGame->deckCount[0] = 1;

	// TEST 1: Check that a shuffle occurs correctly only if the deck is empty.
	printf("TEST 1: Check that a shuffle does not occur on boundary case 1 card remaining.\n");
	int playerBeforeDraw = testGame->handCount[0];
	int opponentBeforeDraw = testGame->handCount[1];
	int playerDeckBeforeDraw = testGame->deckCount[0];
	int opponentDeckBeforeDraw = testGame->deckCount[1];

	cardEffect(adventurer, 0, 0, 0, testGame, 0, 0);
	printf("Player deck count = %d, expected = > 1.\n", testGame->deckCount[0]);
	printf("Opponent deck count = %d, expected = %d.\n", testGame->deckCount[1], opponentDeckBeforeDraw);
	if (testGame->deckCount[0] > 1) {
		printf("TEST 1 PASSED: Player deck count is as expected.\n");
	}
	else {
		printf("TEST 1 FAILED: Player deck count not as expected.\n");
	}
	printf("\n");

	// TEST 2: Check that a player correctly draws only coins into hand.
	memcpy(&testGame, &baseGame, sizeof(struct gameState*));
	printf("TEST 2: Check that a player correctly draws only 2 treasures into hand.\n");
	playerBeforeDraw = testGame->handCount[0];
	opponentBeforeDraw = testGame->handCount[1];
	playerDeckBeforeDraw = testGame->deckCount[0];
	opponentDeckBeforeDraw = testGame->deckCount[1];
	
	// Set all cards in hand to estate initially.
	for (int i = 0; i < testGame->handCount[0]; i++) {
		testGame->hand[0][i] == estate;
	}

	// Set counter for number of coins in hand after draw.
	int testCoins = 0;

	cardEffect(adventurer, 0, 0, 0, testGame, 0, 0);
	for (int i = 0; i < testGame->handCount[0]; i++) {
		if (testGame->hand[0][i] == copper || testGame->hand[0][i] == silver || testGame->hand[0][i] == gold) {
			testCoins++;
		}
	}

	if (testCoins == 3) {
		printf("TEST 2 PASSED: Two drawn treasures from adventurer.\n");
	}
	else {
		printf("TEST 2 FAILED: Did not draw two treasures from adventurer.\n");
	}
	printf("\n");


	// TEST 3: Check that all discarded cards from adventurer are NOT treasures.
	memcpy(&testGame, &baseGame, sizeof(struct gameState*));
	printf(" TEST 3: Check that all discarded cards from adventurer are NOT treasures.\n");
	playerBeforeDraw = testGame->handCount[0];
	opponentBeforeDraw = testGame->handCount[1];
	playerDeckBeforeDraw = testGame->deckCount[0];
	opponentDeckBeforeDraw = testGame->deckCount[1];

	int badDiscard = 0;
	cardEffect(adventurer, 0, 0, 0, testGame, 0, 0);
	for (int i = 0; i < testGame->discardCount[0]; i++) {
		if (testGame->discard[0][i] == copper || testGame->discard[0][i] == silver || testGame->discard[0][i] == gold) {
			badDiscard++;
		}
	}

	if (badDiscard <= 0) {
		printf("TEST 3 PASSED: Only non treasure cards discarded.\n");
	}
	else {
		printf("TEST 3 FAILED: Treasure card discarded.\n");
	}
	printf("\n");



	return 0;
}