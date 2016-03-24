/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *    Contains functions for outputting game to screen     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
#include "gfx.h"
#include "output.h"

// Prints the static blocks and moving block to screen

void printTetrisBucket() {
	   color_t   tetrisShapeColors = Red;
	   int i, j;
    //Placement of bucket on screen
    bucket.x = 0;
    bucket.y = 0;
		currentPiece->x = 0;
		currentPiece->y = 0;
    
    //For every cell in the tetris bucket
 //    gdispFillArea(100,100, 50, 50, Red);
    for (i = 0; i < bucket.height; i++) {
        for (j = 0; j < bucket.width; j++) {
          //  mvprintw(bucket.y + i, bucket.x + j, "%c", bucket.bucket[i][j].value);
						if((bucket.bucket[i][j].value != ' ')){
						    GLCD_DrawRectangle ((bucket.x + (j*BLOCK_SIZE)), (bucket.y + (i*BLOCK_SIZE)), BLOCK_SIZE, BLOCK_SIZE);
						}
					
        }
    }

    //For every piece in the currently moving block
    for (i = 0; i < currentPiece->size; i++) {
        for (j = 0; j < currentPiece->size; j++) {
            //If this isn't a blank char then print it
            if (currentPiece->graphic[i][j] != ' ') {
               // mvprintw(currentPiece->y + i, currentPiece->x + j, "%c", currentPiece->graphic[i][j]);
								GLCD_DrawRectangle (((currentPiece->x)+(j*BLOCK_SIZE)),((currentPiece->y)+(i*BLOCK_SIZE)),BLOCK_SIZE, BLOCK_SIZE);
            }

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