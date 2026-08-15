#include <string.h>

#include "type.h"


void initializeGameState(AppState *appState)
{
    appState->game.curentPlayer = WHITE;

    int initialBoard[8][8] = {
        {BLACK_R, BLACK_N, BLACK_B, BLACK_Q, BLACK_K, BLACK_B, BLACK_N, BLACK_R},
        {BLACK_P, BLACK_P, BLACK_P, BLACK_P, BLACK_P, BLACK_P, BLACK_P, BLACK_P},
        {0},
        {0},
        {0},
        {0},
        {WHITE_P, WHITE_P, WHITE_P, WHITE_P, WHITE_P, WHITE_P, WHITE_P, WHITE_P},
        {WHITE_R, WHITE_N, WHITE_B, WHITE_Q, WHITE_K, WHITE_B, WHITE_N, WHITE_R}
    };

    memcpy(appState->game.board, initialBoard, sizeof(appState->game.board));

}