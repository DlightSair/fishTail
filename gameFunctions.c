#include <string.h>

#include "type.h"

int isBlack(int x){
    if(x<0){
        return 1;
    }else{
        return 0;
    }
}

int isWhite(int x){
    if(x>0){
        return 1;
    }else{
        return 0;
    }
}

int isBlank(int x){
    if(x==0){
        return 1;
    }else{
        return 0;
    }
}


void initializeGameState(AppState *appState)
{
    appState->game.currentPlayer = WHITE;

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

    appState->game.CC_x = -1;
    appState->game.CC_y = -1;

    appState->game.LC_x = -1;
    appState->game.LC_y = -1;
}

int checkBount(AppState *state){
    if(state->game.CC_x < 0 || state->game.CC_x > 7 || state->game.CC_y < 0 || state->game.CC_y > 7 ) return 0;
    if(state->game.LC_x < 0 || state->game.LC_x > 7 || state->game.LC_y < 0 || state->game.LC_y > 7 ) return 0;
    return 1;
}



int isMoveValid(AppState *state){

    if(!checkBount(state)) return 0; 

    int currentPlayer = state->game.currentPlayer;
    int movingPiece = state->game.board[state->game.LC_y][state->game.LC_x];
    int newCords_x = state->game.CC_x;
    int newCords_y = state->game.CC_y;

    if(isBlank(movingPiece)) return 0;
    if(currentPlayer == WHITE && isBlack(movingPiece)) return 0;
    if(currentPlayer == BLACK && isWhite(movingPiece)) return 0;
    

    return 1;
}

void movePiece(AppState *appState){

    int isValid = isMoveValid(appState);

    if(isValid){
        
        appState->game.board[appState->game.CC_y][appState->game.CC_x] = appState->game.board[appState->game.LC_y][appState->game.LC_x];
        appState->game.board[appState->game.LC_y][appState->game.LC_x] = 0;
        
        if(appState->game.currentPlayer == WHITE) {
            appState->game.currentPlayer = BLACK;
        } else if(appState->game.currentPlayer == BLACK){
            appState->game.currentPlayer = WHITE;
        }

    }
}