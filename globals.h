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

//A container for a piece in the Tetris game space
//  ie. "X" = a Block, " " = an empty space in board
//  Using a struct in case there's the opportunity to add colour later

typedef struct Cell {
    char value;
} Cell;

//The "Bucket" where pieces are placed
//  A bucket contains a bunch of containers, which hold information about piece locations

typedef struct Bucket {
    Cell **bucket;
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


#endif	/* GLOBALS_H */