#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/**********************************************************************
	CS362: Software Engineering II
	Card Test 1: Smithy
	Author: Reed Liu
	Date: 2/2/2018
***********************************************************************/

int main() {

	printf("\nBEGIN CARD TEST 1: smithy\n\n");
	// Initialize gameState with relevant information.
	struct gameState *baseGame = newGame();
	struct gameState *testGame = newGame();
	int cards[10] = { smithy, adventurer, salvager, sea_hag,
		council_room, feast, minion, great_hall, tribute, embargo };

	// Initialize new base game state and copy to test game state.
	initializeGame(2, cards, 1000, baseGame);
	memcpy(&testGame, &baseGame, sizeof(struct gameState*));
	testGame->hand[0][0] = smithy;

	// TEST 1: Check that three cards are correctly added to player's hand.
	printf("TEST 1: Check that three cards are correctly added to player's hand.\n");
	int playerBeforeDraw = testGame->handCount[0];
	int opponentBeforeDraw = testGame->handCount[1];
	int playerDeckBeforeDraw = testGame->deckCount[0];
	int opponentDeckBeforeDraw = testGame->deckCount[1];
	cardEffect(smithy, 0, 0, 0, testGame, 0, 0);
	printf("Player hand count = %d, expected = %d.\n", testGame->handCount[0], playerBeforeDraw + 2);
	printf("Opponent hand count = %d, expected = %d.\n", testGame->handCount[1], opponentBeforeDraw);
	if (testGame->handCount[0] == playerBeforeDraw + 2) {
		printf("TEST 1 PASSED: Player hand count is as expected.\n");
	}
	else {
		printf("TEST 1 FAILED: Player hand count not as expected.\n");
	}
	printf("\n");

	// TEST 2: Check that the cards given to the player came from the player's deck.
	printf("TEST 2: Check that the cards given to the player came from the player's deck.\n");
	printf("Player deck count = %d, expected = %d.\n", testGame->deckCount[0], playerDeckBeforeDraw - 3);
	printf("Opponent deck count = %d, expected = %d.\n", testGame->deckCount[1], opponentDeckBeforeDraw);
	if (testGame->deckCount[0] == playerDeckBeforeDraw - 3) {
		printf("TEST 2 PASSED: Player deck count after smithy is as expected.\n");
	}
	else {
		printf("TEST 2 FAILED: Player deck count after smithy not as expected.\n");
	}
	printf("\n");

	return 0;
}