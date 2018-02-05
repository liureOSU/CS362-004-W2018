#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/**********************************************************************
	CS362: Software Engineering II
	Card Test 3: Council Room
	Author: Reed Liu
	Date: 2/2/2018
***********************************************************************/

int main() {

	printf("\nBEGIN CARD TEST 3: council room\n\n");
	// Initialize gameState with relevant information.
	struct gameState *baseGame = newGame();
	struct gameState *testGame = newGame();
	int cards[10] = { smithy, adventurer, salvager, sea_hag,
		council_room, feast, minion, great_hall, tribute, embargo };

	// Initialize new base game state and copy to test game state.
	initializeGame(2, cards, 1000, baseGame);
	memcpy(&testGame, &baseGame, sizeof(struct gameState*));
	testGame->hand[0][0] = council_room;

	// TEST 1: Check that three cards are correctly added to player's hand.
	printf("TEST 1: Check that four cards are correctly added to player's hand, and 1 to opponent\n");
	int playerBeforeDraw = testGame->handCount[0];
	int opponentBeforeDraw = testGame->handCount[1];
	int playerDeckBeforeDraw = testGame->deckCount[0];
	int opponentDeckBeforeDraw = testGame->deckCount[1];
	cardEffect(council_room, 0, 0, 0, testGame, 0, 0);
	printf("Player hand count = %d, expected = %d.\n", testGame->handCount[0], playerBeforeDraw + 4);
	printf("Opponent hand count = %d, expected = %d.\n", testGame->handCount[1], opponentBeforeDraw + 1);
	if (testGame->handCount[0] == playerBeforeDraw + 4) {
		printf("TEST 1 PASSED: Player hand count is as expected.\n");
	}
	else {
		printf("TEST 1 FAILED: Player hand count is incorrect.\n");
	}
	printf("\n");

	// TEST 2: Check that the cards given to the player came from the player's deck.
	printf("TEST 2: Check that the cards given to the player came from the player's deck.\n");
	printf("Player deck count = %d, expected = %d.\n", testGame->deckCount[0], playerDeckBeforeDraw - 4);
	printf("Opponent deck count = %d, expected = %d.\n", testGame->deckCount[1], opponentDeckBeforeDraw - 1);
	if (testGame->deckCount[0] == playerDeckBeforeDraw - 3) {
		printf("TEST 2 PASSED: Player deck count after council room is as expected.\n");
	}
	else { 
		printf("TEST 2 FAILED: Player deck count after council room not as expected.\n");
	}
	printf("\n");

	// TEST 3: Check that an extra buy was successfully given to the player.
	printf("TEST 3: Check that an extra buy was successfully given to the player.\n");
	printf("Player buy count = %d, expected = 2.\n", testGame->numBuys);
	if (testGame->numBuys == 2) {
		printf("TEST 3 PASSED: Player has successfully accrued an extra buy.\n");
	}
	else {
		printf("TEST 3 FAILED: Incorrect number of buys.\n");
	}
	printf("\n");

	return 0;
}