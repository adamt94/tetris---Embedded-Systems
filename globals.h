#include "gfx.h"
#ifndef GLOBALS_H
#define	GLOBALS_H

//The width and height of the game area
//const int width = 10;
//const int height = 20;

typedef enum GameState {
    GameInit,
    GameRunning,
    GameOver
} GameState;

typedef enum Move {
    LEFT,
    RIGHT,
    DOWN
} Move;

//The "Bucket" where pieces are placed
//  A bucket contains a bunch of containers, which hold information about piece locations

typedef struct Bucket {
    char **bucket;
    int height;
    int width;
    int x, y; //Position of bucket on screen
} Bucket;

typedef struct Block {
    int blockID;
    int x, y;
    int size;
    char graphic[3][3]; //Position of the lower left position of the block
} Block;

//The game area
extern Bucket bucket;

//Tetris pieces
extern Block *currentPiece;
extern Block *nextPiece;

extern const int BLOCK_SIZE;
//score
extern int Score;
//time for seed
extern int totaltime;

//color for each Tetris shape
extern  color_t   tetrisShapeColors[9]; 
#endif	/* GLOBALS_H */