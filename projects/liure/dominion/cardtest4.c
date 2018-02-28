#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/**********************************************************************
	CS362: Software Engineering II
	Card Test 4: Village
	Author: Reed Liu
	Date: 2/2/2018
***********************************************************************/

int main() {

	printf("\nBEGIN CARD TEST 4: village\n\n");
	// Initialize gameState with relevant information.
	struct gameState *baseGame = newGame();
	struct gameState *testGame = newGame();
	int cards[10] = { smithy, adventurer, salvager, sea_hag,
		council_room, feast, minion, great_hall, tribute, embargo };

	// Initialize new base game state and copy to test game state.
	initializeGame(2, cards, 1000, baseGame);
	memcpy(&testGame, &baseGame, sizeof(struct gameState*));
	testGame->hand[0][0] = village;

	// TEST 1: Check that a card was given successfully to the player.
	printf("TEST 1: Check that a card was given successfully to the player.\n");
	int playerBeforeDraw = testGame->handCount[0];
	int opponentBeforeDraw = testGame->handCount[1];
	int playerDeckBeforeDraw = testGame->deckCount[0];
	int opponentDeckBeforeDraw = testGame->deckCount[1];
	int playerActionsBeforeVillage = testGame->numActions;

	cardEffect(village, 0, 0, 0, testGame, 0, 0);
	printf("Player hand count = %d, expected = %d.\n", testGame->handCount[0], playerBeforeDraw);
	printf("Opponent hand count = %d, expected = %d.\n", testGame->handCount[1], opponentBeforeDraw);
	if (testGame->handCount[0] == playerBeforeDraw) {
		printf("TEST 1 PASSED: Player hand count is as expected.\n");
	}
	else {
		printf("TEST 1 FAILED: Player hand count is incorrect.\n");
	}
	printf("\n");

	// TEST 2: Check that two actions were successfully given to the player.
	printf("TEST 2: Check that two actions were successfully given to the player.\n");
	printf("Player number of actions = %d, expected = 3.\n", testGame->numActions);
	if (testGame->numActions == 3) {
		printf("TEST 2 PASSED: Player action count is correct.\n");
	}
	else {
		printf("TEST 2 FAILED: Action count incorrect.\n");
	}
	printf("\n");
	getchar();
	return 0;
}