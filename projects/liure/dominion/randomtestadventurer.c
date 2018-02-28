/**********************************************************************
*	CS362: Software Engineering II
*	Random Test: Adventurer
*	Author: Reed Liu
*	Date: 2/18/2018
***********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>

struct gameState* randomGameState(int seed, int card)
{
	struct gameState *g;

	g = newGame();
	int i, j = 0;
	int randomIntegers[11];
	int randInt;
	int *kCards;

	for (i = 0; i < 10; i++) {
		randomIntegers[i] = -1;
	}

	// Choose currentcard
	randomIntegers[0] = card;
	int isSame = 0;

	// Randomize the nine other kingdom cards.
	for (i = 1; i < 10; i++) {
		do {
			randInt = adventurer + rand() % (treasure_map + 1 - adventurer);
			if (randInt != randomIntegers[0] && randInt != randomIntegers[1] && randInt != randomIntegers[2] && randInt != randomIntegers[3]
				&& randInt != randomIntegers[4] && randInt != randomIntegers[5] && randInt != randomIntegers[6] && randInt != randomIntegers[7]
				&& randInt != randomIntegers[8] && randInt != randomIntegers[9]) {
				randomIntegers[i] = randInt;
				isSame = 0;
			}
			else {
				isSame = 1;
			}
		} while (isSame == 1);
	}

	kCards = kingdomCards(randomIntegers[0], randomIntegers[1], randomIntegers[2], randomIntegers[3], randomIntegers[4],
		randomIntegers[5], randomIntegers[6], randomIntegers[7], randomIntegers[8], randomIntegers[9]);

	// Randomize number of players between 2 and MAX.
	int randomNumberPlayers = rand() % (MAX_PLAYERS - 2) + 2;
	if (randomNumberPlayers == 1 || randomNumberPlayers > 4) {
		randomNumberPlayers = 2;
	}

	// Initialize and return newly generated game.
	int init = initializeGame(randomNumberPlayers, kCards, 4, g);
	free(kCards);
	return g;
}

int adventurerTest(struct gameState* testGame, int seed, int player)
{
	int i = 0;
	int temphand[100];// moved above the if statement
	int drawntreasure = 0;
	int cardDrawn = 10;
	// Choose a random hand position to add council room to.
	int randomHandPos = rand() % 6;

	cardEffect(adventurer, 0, 0, 0, testGame, randomHandPos, 0);
	return 0;
}

int main()
{
	srand(time(NULL));
	int sd;
	int testCheck;
	int playerHandBeforeDraw[4];
	int playerDeckBeforeDraw[4];
	int prevBuys;
	int i, j;
	int failCounter = 0;

	// Perform test 10000 times.
	printf("***********************ADVENTURER RANDOM TEST: BEGIN\n\n");
	for (j = 0; j < 10000; j++) {

		sd = j;
		// Set up the game state.
		struct gameState *testGame = randomGameState(sd, adventurer);

		// Discard a random number of cards.
		int getCard = rand() % testGame->deckCount[0] + 1;
		for (i = 0; i < getCard; i++) {
			drawCard(0, testGame);
		}

		// Copy state of player and opponent hand counts before playing card.
		for (i = 0; i < testGame->numPlayers; i++) {
			playerHandBeforeDraw[i] = testGame->handCount[i];
			playerDeckBeforeDraw[i] = testGame->deckCount[i];
		}

		// Set counter for number of coins in hand after draw.
		int testCoins = 0;

		// Run test and assert that the card ran correctly.
		testCheck = adventurerTest(testGame, sd, 0);
		if (testCheck != 0) {
			printf("ASSERT != 0!  CARD FAILED TO EXECUTE\n");
			failCounter++;
		}

		// Check if shuffle occurs on correct conditions (deckCount[currentPlayer] = 0) only.
		if (playerDeckBeforeDraw[0] == 0 && testGame->deckCount[0] < 1 && testGame->deckCount[0] != 0 && testGame->deckCount[0] != 1) {
			printf("RUN %d failed: DECK = 0 - current player deck should be > 1, currently %d\n", j + 1, testGame->deckCount[0]);
			failCounter++;
		}

		// Check that a shuffle does not occur on incorrect conditions.
		if (playerDeckBeforeDraw[0] >= 1 && testGame->deckCount[0] != playerDeckBeforeDraw[0] - 2 && testGame->deckCount[0] != 0) {
			printf("RUN %d failed: DECK > 0 - current player deck should be %d, currently %d\n", j + 1, playerDeckBeforeDraw[0] - 2, testGame->deckCount[0]);
			failCounter++;
		}

		// Check that player gets the correct number of cards into hand.
		if (testGame->handCount[0] != playerHandBeforeDraw[0] + 2) {
			printf("RUN %d failed: current player hand should be %d, currently %d\n", j + 1, playerHandBeforeDraw[0] + 2, testGame->handCount[0]);
			failCounter++;
		}

		free(testGame);
	}

	if (failCounter == 0) {
		printf("***********************ADVENTURER RANDOM TEST: All runs passed.\n");
	}
	else {
		printf("***********************ADVENTURER RANDOM TEST: %d failures logged.\n", failCounter);
	}
	printf("\n");
	getchar();
	return 0;
}