#ifndef OUTPUT_H
#define	OUTPUT_H 
#include "globals.h"
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *    Contains functions for outputting game to screen     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

// Prints the static blocks and moving block to screen
void printTetrisBucket(void);
//Erase the block from the screen
void eraseBlock(void);
//Clear the next piece block
void clearNextPieceArea(void);
// Displays the current score
void printScoreWindow(void);
// Displays the next incoming block
void printNextBrickWindow(void);
// Displays a game over screen
void printGameOver(void);
// Displays a victory screen
void printVictory(void);

void menuScreen(void);
#endif	/* OUTPUT_H */

