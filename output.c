/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *    Contains functions for outputting game to screen     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
#include "gfx.h"
#include "output.h"

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
							//draws the bucket
							if(bucket.bucket[i][j] == '#'){
								if( bucket.height-1 ==i){
									gdispFillArea((bucket.x + (j*BLOCK_SIZE)), (bucket.y + (i*BLOCK_SIZE)), 15, 5, tetrisShapeColors[8]);
								}
								else if(j ==0){
									gdispFillArea((bucket.x+10 + (j*BLOCK_SIZE)), (bucket.y + (i*BLOCK_SIZE)), 5, 15, tetrisShapeColors[8]);
								}
								else{
									gdispFillArea((bucket.x + (j*BLOCK_SIZE)), (bucket.y + (i*BLOCK_SIZE)), 5, 15, tetrisShapeColors[8]);
								}
								
							} 
							///draws shapes that collided with the bottom
							else {
								//padding
								gdispFillArea((bucket.x + (j*BLOCK_SIZE)), (bucket.y + (i*BLOCK_SIZE)), BLOCK_SIZE, BLOCK_SIZE, tetrisShapeColors[0]);
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
								gdispFillArea(((bucket.x + (currentPiece->x * BLOCK_SIZE))+(j*BLOCK_SIZE)),(((bucket.y) + (currentPiece->y* BLOCK_SIZE))+(i*BLOCK_SIZE)),BLOCK_SIZE, BLOCK_SIZE, tetrisShapeColors[0]);
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
								gdispFillArea(((bucket.x + (lastDrawnX * BLOCK_SIZE))+(j*BLOCK_SIZE)),(((bucket.y) + (lastDrawnY* BLOCK_SIZE))+(i*BLOCK_SIZE)),BLOCK_SIZE, BLOCK_SIZE, tetrisShapeColors[0]);

        }
    }
}

//Clear the next piece area
void clearNextPieceArea(){
	int i, j;
    for (i = 0; i < nextPiece->size; i++) {
        for (j = 0; j < nextPiece->size; j++) {
								gdispFillArea(((360)+(j*BLOCK_SIZE)),(((130) )+(i*BLOCK_SIZE)),BLOCK_SIZE, BLOCK_SIZE, tetrisShapeColors[0]);

        }
    }
}
// Displays the current score

void printScoreWindow() {
	char* str;
	font16 =  gdispOpenFont("DejaVuSans16");
	gdispDrawString(360, 20, "Score", font16, tetrisShapeColors[8]);
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
	gdispDrawString(360, 100, "Next", font16, tetrisShapeColors[8]);
	gdispCloseFont(font16);
	
	//draw block

    //For every piece in the next block needs to be changed to nextPiece
    for (i = 0; i < nextPiece->size; i++) {
        for (j = 0; j < nextPiece->size; j++) {
            //If this isn't a blank char then print it
            if (nextPiece->graphic[i][j] != ' ') {
               // mvprintw(currentPiece->y + i, currentPiece->x + j, "%c", currentPiece->graphic[i][j]);
							//padding
								gdispFillArea(360+(j*BLOCK_SIZE),130+(i*(BLOCK_SIZE)),BLOCK_SIZE-2, BLOCK_SIZE-2, tetrisShapeColors[0]);
							//shape
								gdispFillArea(361+(j*BLOCK_SIZE),131+(i*(BLOCK_SIZE)),BLOCK_SIZE-2, BLOCK_SIZE-2, tetrisShapeColors[nextPiece->blockID]);
							
            }

        }
    }
							
}
// Displays a game over screen

void printGameOver() {
	gdispClear(Red);
}
// Displays a victory screen

void printVictory() {
}

void menuScreen(){
	//color_t colorrange[9] = {White, Yellow, Red, Blue, Magenta, SkyBlue, Orange,Lime,Black}; 
													//			0			1			2			3			4					5				6				7			8
		// Main menu Background
	gdispFillArea(433, 247, 20, 20, tetrisShapeColors[2]);
	gdispFillArea(112, 247, 20, 20, tetrisShapeColors[7]);
	gdispFillArea(455, 247, 20, 20, tetrisShapeColors[2]);
	gdispFillArea(0, 204, 20, 20, tetrisShapeColors[3]);
	gdispFillArea(23, 225, 20, 20, tetrisShapeColors[1]);
	gdispFillArea(455, 224, 20, 20, tetrisShapeColors[2]);
	gdispFillArea(91, 247, 20, 20, tetrisShapeColors[7]);
	gdispFillArea(83, 80, 20, 20, tetrisShapeColors[4]);
	gdispFillArea(432, 203, 20, 20, tetrisShapeColors[6]);
	gdispFillArea(178, 247, 20, 20, tetrisShapeColors[5]);
	gdispFillArea(134, 247, 20, 20, tetrisShapeColors[7]);
	gdispFillArea(455, 201, 20, 20, tetrisShapeColors[2]);
	gdispFillArea(22, 247, 20, 20, tetrisShapeColors[3]);
	gdispFillArea(46, 248, 20, 20, tetrisShapeColors[1]);
	gdispFillArea(46, 225, 20, 20, tetrisShapeColors[1]);
	gdispFillArea(82, 102, 21, 20, tetrisShapeColors[4]);
	gdispFillArea(70, 247, 20, 20, tetrisShapeColors[7]);
	gdispFillArea(60, 102, 20, 20, tetrisShapeColors[4]);
	gdispFillArea(410, 225, 20, 20, tetrisShapeColors[6]);
	gdispFillArea(156, 247, 20, 20, tetrisShapeColors[5]);
	gdispFillArea(134, 225, 20, 20, tetrisShapeColors[5]);
	gdispFillArea(410, 247, 20, 20, tetrisShapeColors[6]);
	gdispFillArea(0, 226, 20, 20, tetrisShapeColors[3]);
	gdispFillArea(47, 227, 20, 20, tetrisShapeColors[1]);
	gdispFillArea(60, 80, 20, 20, tetrisShapeColors[4]);
	gdispFillArea(69, 225, 20, 20, tetrisShapeColors[1]);
	gdispFillArea(0, 247, 20, 20, tetrisShapeColors[3]);
	gdispFillArea(432, 225, 20, 20, tetrisShapeColors[6]);
	gdispFillArea(157, 225, 20, 20, tetrisShapeColors[5]);
	//Button
	gdispFillArea(200,60,80,30,Grey);
	gdispFillArea(200+3,60+3,80-6,30-6,Silver);
	//text
	font16 =  gdispOpenFont("DejaVuSans16");
	gdispDrawString(225, 66, "Play", font16, tetrisShapeColors[8]);
	gdispCloseFont(font16);
	
		//Button
	gdispFillArea(200,110,96,30,Grey);
	gdispFillArea(200+3,110+3,96-6,30-6,Silver);
	//text
	font16 =  gdispOpenFont("DejaVuSans16");
	gdispDrawString(205, 116, "Dark Mode", font16, tetrisShapeColors[8]);
	gdispCloseFont(font16);
	
	
		//Button
	gdispFillArea(200,160,126,30,Grey);
	gdispFillArea(200+3,160+3,126-6,30-6,Silver);
	//text
	font16 =  gdispOpenFont("DejaVuSans16");
	gdispDrawString(205, 166, "Random Mode", font16, tetrisShapeColors[8]);
	gdispCloseFont(font16);
}