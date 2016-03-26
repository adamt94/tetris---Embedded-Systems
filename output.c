/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *    Contains functions for outputting game to screen     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
#include "gfx.h"
#include "output.h"
//color for each Tetris shape
const color_t   tetrisShapeColors[7] = {Green, Yellow, Red, Blue, Magenta, SkyBlue, Orange}; 
// Prints the static blocks and moving block to screen

void printTetrisBucket() {
	  
	  int i, j;
    //Placement of bucket on screen
    bucket.x = 0;
    bucket.y = 0;
    
    //For every cell in the tetris bucket
    // gdispFillArea(100,100, 50, 50, Red);
    for (i = 0; i < bucket.height; i++) {
        for (j = 0; j < bucket.width; j++) {
          //  mvprintw(bucket.y + i, bucket.x + j, "%c", bucket.bucket[i][j].value);
						if((bucket.bucket[i][j].value != ' ')){
							gdispFillArea((bucket.x + (j*BLOCK_SIZE)), (bucket.y + (i*BLOCK_SIZE)), BLOCK_SIZE, BLOCK_SIZE, Black);
						}
					
        }
    }

    //For every piece in the currently moving block
    for (i = 0; i < currentPiece->size; i++) {
        for (j = 0; j < currentPiece->size; j++) {
            //If this isn't a blank char then print it
            if (currentPiece->graphic[i][j] != ' ') {
               // mvprintw(currentPiece->y + i, currentPiece->x + j, "%c", currentPiece->graphic[i][j]);
								
								gdispFillArea(((currentPiece->x * BLOCK_SIZE)+(j*BLOCK_SIZE)),((currentPiece->y* BLOCK_SIZE)+(i*BLOCK_SIZE)),BLOCK_SIZE, BLOCK_SIZE, tetrisShapeColors[currentPiece->blockID]);
							
            }

        }
    }


}

//Erase the block
void eraseBlock(){
	int i, j;
	//For every piece in the currently moving block
    for (i = 0; i < currentPiece->size; i++) {
        for (j = 0; j < currentPiece->size; j++) {
            //If this isn't a blank char then print it
								gdispFillArea(((currentPiece->x * BLOCK_SIZE)+(j*BLOCK_SIZE)),((currentPiece->y* BLOCK_SIZE)+(i*BLOCK_SIZE)),BLOCK_SIZE, BLOCK_SIZE,White);

        }
    }
}
// Displays the current score

void printScoreWindow() {
}
// Displays the next incoming block

void printNextBrickWindow() {
}
// Displays a game over screen

void printGameOver() {
}
// Displays a victory screen

void printVictory() {
}