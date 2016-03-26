#ifndef SETUP_H
#define	SETUP_H
#include "globals.h"

void initialiseNewGame(int width, int height);
Bucket makeBucket(int width, int height);
Block* randomBlock();
Block* makeBlock();
void setBlockGraphic(Block *block, int argc, ...);
void setRandomBlockGraphic(Block *block);

#endif	/* SETUP_H */

