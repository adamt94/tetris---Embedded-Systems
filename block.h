/*
 *  All the methods related to manipulating the Tetris block 
 */

#ifndef BLOCK_H
#define	BLOCK_H
#include "globals.h"

int attemptMove(char move);
int checkForCollision(Block *block);
void updateBlock(void);
void rotateBlock();

#endif	/* BLOCK_H */

