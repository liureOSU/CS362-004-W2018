/**********************************************************************
*	CS362: Software Engineering II
*	Random Test: Council Room
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
	int i, j;
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

int councilRoomTest(struct gameState* testGame, int seed, int player)
{
	int i = 0;
	// Choose a random hand position to add council room to.
	int randomHandPos = rand() & 6;
	testGame->hand[player][randomHandPos] = council_room;

	cardCouncilRoom(i, testGame, randomHandPos, player);

	return 0;
}

int main()
{
	int sd;
	int testCheck;
	int previousHandCount[4];
	int prevBuys;
	int i, j;
	int failCounter = 0;
	// Perform test 1000 times.
	printf("***********************COUNCIL ROOM RANDOM TEST: BEGIN\n\n");
	for (j = 0; j < 1000; j++) {

		sd = j;
		// Perform the test and assert that card finished execution.
		struct gameState *testGame = randomGameState(sd, council_room);
		for (i = 0; i < testGame->numPlayers; i++) {
			previousHandCount[i] = testGame->handCount[i];
		}
		prevBuys = testGame->numBuys;

		// Check that card did not fail to run.
		testCheck = councilRoomTest(testGame, sd, 0);
		if (testCheck != 0) {
			printf("ASSERT != 0!  CARD FAILED TO EXECUTE\n");
			failCounter++;
		}
		// Check that currentPlayer has the correct number of buys (+1 added due to card).
		if (testGame->numBuys != prevBuys + 1) {
			printf("RUN %d FAILED: ", j + 1);
			printf("Number of buys for currentPlayer should be %d, is currently %d\n",
				prevBuys + 1, testGame->numBuys);
			failCounter++;
		}
		// Check that currentPlayer has +4 cards.
		if (testGame->handCount[0] != previousHandCount[0] + 4) {
			printf("RUN %d FAILED: ", j + 1);
			printf("Number of card in player[0] hand should be %d, is currently %d\n",
				previousHandCount[0] + 1, testGame->handCount[0]);
			failCounter++;
		}
		// Check that all other players have +1 extra card.
		for (i = 1; i < testGame->numPlayers; i++) {
			if (testGame->handCount[i] != previousHandCount[i] + 1) {
				printf("RUN %d FAILED: ", j + 1);
				printf("Number of card in player[%d] hand should be %d, is currently %d\n",
					i + 1, previousHandCount[i] + 1, testGame->handCount[i]);
				failCounter++;
			}
		}
		free(testGame);
	}

	if (failCounter == 0) {
		printf("***********************COUNCIL ROOM RANDOM TEST: All runs passed.\n");
	}
	else {
		printf("***********************COUNCIL ROOM RANDOM TEST: %d failures logged.\n", failCounter);
	}
	printf("\n");
	return 0;
}