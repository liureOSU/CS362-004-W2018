#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/**********************************************************************
	CS362: Software Engineering II
	Unit Test 1: updateCoins
	Author: Reed Liu
	Date: 2/2/2018
***********************************************************************/

int main() {

	printf("\nBEGIN UNIT TEST 1: updateCoins\n\n");
	// Initialize gameState with relevant information.
	struct gameState *baseGame = newGame();
	struct gameState *testGame = newGame();
	baseGame->handCount[0] = 5;
	baseGame->handCount[1] = 3;
	
	// UNIT TEST 1: Test that GOLDS add the correct total to the game pool.  Use PLAYER 1.
	memcpy(&testGame, &baseGame, sizeof(struct gameState*));
	testGame->hand[0][0] = gold;
	testGame->hand[0][1] = village;
	testGame->hand[0][2] = village;
	testGame->hand[0][3] = smithy;
	testGame->hand[0][4] = adventurer;
	updateCoins(0, testGame, 0);
	
	printf("TEST 1: ADDING ONE GOLD FROM PLAYER 1 TO PILE\n");
	if (testGame->coins == 3) {
		printf("TEST 1 PASSED - CORRECT AMOUNT OF COINS (3) ADDED TO TOTAL\n");
	}
	else {
		printf("TEST 1 FAILED - NUMBER OF COINS INCORRECT\n");
	}
	printf("\n");

	// UNIT TEST 2: Test that 3 GOLDS (multiple) are correctly added to the game pool. Use PLAYER 2.
	testGame->hand[1][0] = gold;
	testGame->hand[1][1] = gold;
	testGame->hand[1][2] = gold;
	updateCoins(1, testGame, 0);

	printf("TEST 2: ADDING MULTIPLE (3) GOLDs FROM PLAYER 2 TO PILE\n");
	if (testGame->coins == 9) { 
		printf("TEST 2 PASSED - CORRECT AMOUNT OF COINS (9) ADDED TO TOTAL\n"); 
	}
	else { 
		printf("TEST 2 FAILED - NUMBER OF COINS INCORRECT\n"); 
	}
	printf("\n");

	// UNIT TEST 3: Test that 2 SILVERS are correctly added to the game pool. Use PLAYER 1.
	memcpy(&testGame, &baseGame, sizeof(struct gameState*));
	testGame->hand[0][0] = village;
	testGame->hand[0][1] = silver;
	testGame->hand[0][2] = great_hall;
	testGame->hand[0][3] = smithy;
	testGame->hand[0][4] = silver;
	updateCoins(0, testGame, 0);

	printf("TEST 3: ADDING TWO SILVER FROM PLAYER 1 TO PILE\n");
	if (testGame->coins == 4) {
		printf("TEST 3 PASSED - CORRECT AMOUNT OF COINS (4) ADDED TO TOTAL\n");
	}
	else {
		printf("TEST 3 FAILED - NUMBER OF COINS INCORRECT\n");
	}
	printf("\n");

	// UNIT TEST 4: Test that 2 COPPERS and 1 GOLD (multiple) are correctly added to the game pool. Use PLAYER 2.
	testGame->hand[1][0] = copper;
	testGame->hand[1][1] = gold;
	testGame->hand[1][2] = copper;
	updateCoins(1, testGame, 0);

	printf("TEST 4: ADDING 2 COPPERS and 1 GOLD FROM PLAYER 2 TO PILE\n");
	if (testGame->coins == 5) {
		printf("TEST 4 PASSED - CORRECT AMOUNT OF COINS (5) ADDED TO TOTAL\n");
	}
	else {
		printf("TEST 4 FAILED - NUMBER OF COINS INCORRECT\n");
	}
	printf("\n");

	// UNIT TEST 5: Check that BONUS subroutine works as intended by adding 6 BONUS coins.
	memcpy(&testGame, &baseGame, sizeof(struct gameState*));
	testGame->hand[0][0] = village;
	testGame->hand[0][1] = adventurer;
	testGame->hand[0][2] = great_hall;
	testGame->hand[0][3] = salvager;
	testGame->hand[0][4] = sea_hag;
	updateCoins(0, testGame, 6);

	printf("TEST 5: CHECK BONUS SUBROUTINE - ADDING 6 BONUS COINS\n");
	if (testGame->coins == 6) {
		printf("TEST 5 PASSED - CORRECT AMOUNT OF COINS (6) ADDED TO TOTAL\n");
	}
	else {
		printf("TEST 5 FAILED - NUMBER OF COINS INCORRECT\n");
	}
	printf("\n");

	return 0;
}