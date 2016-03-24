/* * * * * * * * * * * * * * * * * * * * * *
 *    Contains functions for game loop     *
 * * * * * * * * * * * * * * * * * * * * * *
 */

#include "gameLoop.h"

int checkUserInput(){
    //If key is left move block left
    //If key is right move block right
    //If key is down move block down
    //If key is rotate then rotate clockwise
    //Consider adding if key is PAUSE button then pause game
}

// Checks each row to see if any are full and need clearing, will add points and rebuild screen (move blocks down) if any are
int checkForFullRows(){
    int fullRow = 1;
    int i, j, a, b;
    //For bucket height
    for(i = 0; i < bucket.height - 1; i++){
        //For bucket width
        for(j = 0; j < bucket.width; j++){
            //If any character in this row is empty, the line can't be full
            if(bucket.bucket[i][j].value == ' '){
                fullRow = 0;
            }
        }
        //If all cells in line have been considered and line is full
        if(fullRow == 1){
            //Update score
            //For every line above this
            for(a = i; a > 0; a--){
                for(b = 0; b < bucket.width; b++){
                    //Move the blocks down by one
                    bucket.bucket[a][b].value = bucket.bucket[a - 1][b].value;
                }
            }
        }
        
        //Reset check to 1 in preparation for checking next line
        fullRow = 1;
    }
}