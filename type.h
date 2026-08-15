#ifndef TYPE_H
#define TYPE_H

#include <stdio.h>
#include <SDL3/SDL.h>


#define BOARD_SIZE 8
#define WHITE 1
#define BLACK 2

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
    int curentPlayer;
    int board[BOARD_SIZE][BOARD_SIZE];
} gameState;

gameState currentGame = {
    .curentPlayer = WHITE,

    .board = {
        {BLACK_R, BLACK_N, BLACK_B, BLACK_Q, BLACK_K, BLACK_B, BLACK_N, BLACK_R},
        {BLACK_P, BLACK_P, BLACK_P, BLACK_P, BLACK_P, BLACK_P, BLACK_P, BLACK_P},
        {0},
        {0},
        {0},
        {0},
        {WHITE_P, WHITE_P, WHITE_P, WHITE_P, WHITE_P, WHITE_P, WHITE_P, WHITE_P},
        {WHITE_R, WHITE_N, WHITE_B, WHITE_Q, WHITE_K, WHITE_B, WHITE_N, WHITE_R}
    }
};

typedef struct{
    SDL_Window *window;
    SDL_Renderer *renderer;
    gameState game;
} AppState;


#endif