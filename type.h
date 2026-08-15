#ifndef TYPE_H
#define TYPE_H

#include <stdio.h>
#include <SDL3/SDL.h>

#define BOARD_SIZE 8
#define WHITE 0
#define BLACK 1
#define PIECE_TEXTURE_COUNT 13


extern int WIDTH;
extern int HEIGHT;

enum {
    WHITE_P = 1,
    WHITE_N = 2,
    WHITE_B = 3,
    WHITE_R = 4,
    WHITE_K = 5,
    WHITE_Q = 6,

    BLACK_P = -1,
    BLACK_N = -2,
    BLACK_B = -3,
    BLACK_R = -4,
    BLACK_K = -5,
    BLACK_Q = -6
};

typedef struct{
    int currentPlayer;
    int board[BOARD_SIZE][BOARD_SIZE];
    int hover_x, hover_y;
    int CC_x, CC_y;
    int LC_x, LC_y;

} gameState;


typedef struct{
    SDL_Window *window;
    SDL_Renderer *renderer;
    gameState game;
    SDL_Texture *pieceTextures[PIECE_TEXTURE_COUNT];
} AppState;


#endif