/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *    Contains functions for outputting game to screen     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
#include "gfx.h"
#include "output.h"
//color for each Tetris shape
const color_t   tetrisShapeColors[8] = {Lime, Yellow, Red, Blue, Magenta, SkyBlue, Orange,Lime}; 
font_t          font16;
int lastDrawnX = 0;
int lastDrawnY = 0;
// Prints the static blocks and moving block to screen

void printTetrisBucket() {
	  
	  int i, j;
    //Placement of bucket on screen
    bucket.x = 120;
    bucket.y = 3;
    
    //For every cell in the tetris bucket
    // gdispFillArea(100,100, 50, 50, Red);
    for (i = 0; i < bucket.height; i++) {
        for (j = 0; j < bucket.width; j++) {
          //  mvprintw(bucket.y + i, bucket.x + j, "%c", bucket.bucket[i][j].value);
						if((bucket.bucket[i][j] != ' ')){
							if(bucket.bucket[i][j] == '#'){
								gdispFillArea((bucket.x + (j*BLOCK_SIZE)), (bucket.y + (i*BLOCK_SIZE)), BLOCK_SIZE, BLOCK_SIZE, Black);
							} else {
								//padding
								gdispFillArea((bucket.x + (j*BLOCK_SIZE)), (bucket.y + (i*BLOCK_SIZE)), BLOCK_SIZE, BLOCK_SIZE, White);
								//shape
								gdispFillArea((bucket.x + (j*BLOCK_SIZE)+1), (bucket.y + (i*BLOCK_SIZE)+1), BLOCK_SIZE-2, BLOCK_SIZE-2, tetrisShapeColors[bucket.bucket[i][j]]);
							}
							
						}
					
        }
    }


    //For every piece in the currently moving block
    for (i = 0; i < currentPiece->size; i++) {
        for (j = 0; j < currentPiece->size; j++) {
            //If this isn't a blank char then print it
            if (currentPiece->graphic[i][j] != ' ') {
               // mvprintw(currentPiece->y + i, currentPiece->x + j, "%c", currentPiece->graphic[i][j]);
							//padding
								gdispFillArea(((bucket.x + (currentPiece->x * BLOCK_SIZE))+(j*BLOCK_SIZE)),(((bucket.y) + (currentPiece->y* BLOCK_SIZE))+(i*BLOCK_SIZE)),BLOCK_SIZE, BLOCK_SIZE, White);
							//shape
								gdispFillArea(((bucket.x + (currentPiece->x * BLOCK_SIZE))+(j*BLOCK_SIZE)+1),(((bucket.y) + (currentPiece->y* BLOCK_SIZE))+(i*BLOCK_SIZE)+1),BLOCK_SIZE-2, BLOCK_SIZE-2, tetrisShapeColors[currentPiece->blockID]);
							
            }

        }
    }
		
		//Set last drawn block coordinates (for purposes of erasing display)
		lastDrawnX = currentPiece->x;
		lastDrawnY = currentPiece->y;

}

//Erase the block
void eraseBlock(){
	int i, j;
	//For every piece in the currently moving block
    for (i = 0; i < currentPiece->size; i++) {
        for (j = 0; j < currentPiece->size; j++) {
            //If this isn't a blank char then print it
								gdispFillArea(((bucket.x + (lastDrawnX * BLOCK_SIZE))+(j*BLOCK_SIZE)),(((bucket.y) + (lastDrawnY* BLOCK_SIZE))+(i*BLOCK_SIZE)),BLOCK_SIZE, BLOCK_SIZE, White);

        }
    }
}

//Clear the next piece area
void clearNextPieceArea(){
	int i, j;
    for (i = 0; i < nextPiece->size; i++) {
        for (j = 0; j < nextPiece->size; j++) {
								gdispFillArea(((360)+(j*BLOCK_SIZE)),(((130) )+(i*BLOCK_SIZE)),BLOCK_SIZE, BLOCK_SIZE, White);

        }
    }
}
// Displays the current score

void printScoreWindow() {
	char* str;
	font16 =  gdispOpenFont("DejaVuSans16");
	gdispDrawString(360, 20, "Score", font16, Black);
 // gdispDrawLine(365, 40, 380, 20, Purple);
	gdispFillArea(365, 35, 35, 1, Purple);
	
	//draw current score
  sprintf(str,"%d",Score);
	gdispDrawString(378, 42, str, font16, Purple);
	gdispCloseFont(font16);
}
// Displays the next incoming block

void printNextBrickWindow() {
	char* str;
	int i,j;
	font16 =  gdispOpenFont("DejaVuSans16");
	gdispDrawString(360, 100, "Next", font16, Black);
	gdispCloseFont(font16);
	
	//draw block

    //For every piece in the next block needs to be changed to nextPiece
    for (i = 0; i < nextPiece->size; i++) {
        for (j = 0; j < nextPiece->size; j++) {
            //If this isn't a blank char then print it
            if (nextPiece->graphic[i][j] != ' ') {
               // mvprintw(currentPiece->y + i, currentPiece->x + j, "%c", currentPiece->graphic[i][j]);
							//padding
								gdispFillArea(360+(j*BLOCK_SIZE),130+(i*(BLOCK_SIZE)),BLOCK_SIZE-2, BLOCK_SIZE-2, White);
							//shape
								gdispFillArea(361+(j*BLOCK_SIZE),131+(i*(BLOCK_SIZE)),BLOCK_SIZE-2, BLOCK_SIZE-2, tetrisShapeColors[nextPiece->blockID]);
							
            }

        }
    }
							
}
// Displays a game over screen

void printGameOver() {
}
// Displays a victory screen

void printVictory() {
}