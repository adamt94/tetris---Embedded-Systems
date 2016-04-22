#include "block.h"
#include "setup.h"
#include "stdlib.h"
#include "output.h"
void rotateBlock() {
    int i, j;
    Block *rotatedBlock = malloc(sizeof (Block));
    rotatedBlock->x = currentPiece->x;
    rotatedBlock->y = currentPiece->y;
    rotatedBlock->size = currentPiece->size;
    //Attempt to rotate block
    for (i = 0; i < currentPiece->size; i++) {
        for (j = 0; j < currentPiece->size; j++) {
            rotatedBlock->graphic[j][i] = currentPiece->graphic[currentPiece->size - 1 - i][j];
        }
    }

    //If acceptable rotation set currentPiece to rotatedBlock
    if (checkForCollision(rotatedBlock) == 0) {
        for (i = 0; i < currentPiece->size; i++) {
            for (j = 0; j < currentPiece->size; j++) {
                currentPiece->graphic[i][j] = rotatedBlock->graphic[i][j];
            }
        }
    }

}

void updateBlock() {
    int i, j;
    if (checkForCollision(currentPiece) == 1) {


        //        currentPiece->y = 1;
        //        currentPiece->x = 1;
    }
    //currentPiece->y = currentPiece->y  + 1;
}

int validMove(Block* attempt) {

}

int checkForCollision(Block *block) {
    int i, j;
    //For every cell in the current piece
    for (i = 0; i < block->size; i++) {
        for (j = 0; j < block->size; j++) {
            //If currently considered cell in graphic isn't blank
            if (block->graphic[i][j] != ' ') {
                //If cell within bucket boundaries
                if ((j) > 0 - 1 &&
                        (j) < (bucket.width) &&
                        (i) > 0 - 1 &&
                        (i) < (bucket.height)) {

                    //Check for collision with block in bucket
                    int test = block->y + i;
                    int test2 = block->x + j;
													
                    if (bucket.bucket[test][test2] != ' ') {
                        return 1;
                    }
                }
            }
        }
    }

    return 0;
}

int attemptMove(char move) {
	  int i, j;
    Block attempt = *currentPiece;
    switch (move) {
        case 'L':
            attempt.x = attempt.x - 1;
            break;
        case 'R':
            attempt.x = attempt.x + 1;
            break;
        case 'D':
            attempt.y = attempt.y + 1;
            break;
        default:
            break;
    }
    //If there isn't a collision make the move
    if (checkForCollision(&attempt) == 0) {
        currentPiece->x = attempt.x;
        currentPiece->y = attempt.y;
    } else if (move == 'D'){
        for (i = 0; i < currentPiece->size; i++) {
            for (j = 0; j < currentPiece->size; j++) {
                if (currentPiece->graphic[i][j] != ' ')
                    bucket.bucket[i + currentPiece->y][j + currentPiece->x] = currentPiece->blockID;
										//bucket.bucket[i + currentPiece->y][j + currentPiece->x].color = currentPiece->blockID;
            }
        }
				free(currentPiece);
				currentPiece = nextPiece;
				currentPiece->x = 3;
				currentPiece->y = 0;
				
				//Erase the next piece's position
				clearNextPieceArea();
				nextPiece = makeBlock();
    }
    return 1;
}