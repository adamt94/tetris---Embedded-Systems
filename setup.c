#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> /* Contains the functions (ie. va_start) for variable arguments */
#include "setup.h"

void initialiseNewGame(int width, int height) {
    srand(25);
    bucket = makeBucket(width, height);
    currentPiece = makeBlock();
}

Bucket makeBucket(int width, int height) {
    int i, j;
    Bucket newBucket;

    newBucket.height = height;
    newBucket.width = width;

    //Attempt to allocate space for array of containers to bucket
    if ((newBucket.bucket = calloc(height, sizeof (char*))) ==
            NULL) {
      //  printf("\nFailed to allocate memory for bucket...\n");
        exit(1);
    }
    for (i = 0; i < height; i++) {
        if ((newBucket.bucket[i] = calloc(width, sizeof (char)))
                == NULL) {
         //  printf("\nFailed to allocate memory for bucket[]...\n");
            exit(1);
        }

        for (j = 0; j < width; j++) {
            if (i == height - 1 || j == 0 || j == width - 1) {
                newBucket.bucket[i][j] = '#';
            } else {
                newBucket.bucket[i][j] = ' ';
            }

        }

    }

    return newBucket;
}

Block* makeBlock() {
    Block* temp;
	  int choice;

    //Allocate memory for the Block
    if ((temp = malloc(sizeof (Block))) == NULL) {
      //  endwin(); //End ncurses
      //  printf("Unable to allocate memory for Block...");
        exit(1);
    }
        
    //Placement of block at spawn
    temp->x = 3;
    temp->y = 0;

    //Size of the block's visual representation
    temp->size = 3;
		
    //Set up the char array for the shape of the block
    setRandomBlockGraphic(temp);
    
    return temp;
}

void setRandomBlockGraphic(Block *temp){
	int choice;
		choice = rand() % 7;
		
		//Set blockID to the block type
    temp->blockID = choice;
		
    switch(choice){
        case 0:
            setBlockGraphic(temp, 9,
            ' ', 'X', ' ',
            'X', 'X', 'X',
            ' ', ' ', ' '
            );
            break;
        case 1:
            setBlockGraphic(temp, 9,
            'X', 'X', 'X',
            ' ', ' ', 'X',
            ' ', ' ', ' '
            );
            break;
        case 2:
            setBlockGraphic(temp, 9,
            'X', 'X', 'X',
            'X', ' ', ' ',
            ' ', ' ', ' '
            );
            break;
        case 3:
            setBlockGraphic(temp, 9,
            ' ', 'X', 'X',
            ' ', 'X', 'X',
            ' ', ' ', ' '
            );
            break;
        case 4:
            setBlockGraphic(temp, 9,
            ' ', 'X', 'X',
            'X', 'X', ' ',
            ' ', ' ', ' '
            );
            break;
        case 5:
            setBlockGraphic(temp, 9,
            'X', 'X', ' ',
            ' ', 'X', 'X',
            ' ', ' ', ' '
            );
            break;
        case 6:
            setBlockGraphic(temp, 9,
            'X', 'X', 'X',
            ' ', ' ', ' ',
            ' ', ' ', ' '
            );
            break;
    }
}

void setBlockGraphic(Block *temp, int argc, ...) {
    int i, j,size;
    
    //For accessing variable arguments given
    va_list lst;
    va_start(lst, argc);

    //Set the char array in the block to passed chars
    size = temp->size;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            //Set the char array to given variables
            temp->graphic[i][j] = va_arg(lst, int);

        }
    }

    //Stop checking for variable arguments
    va_end(lst);
}