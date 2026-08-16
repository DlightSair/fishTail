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

void initializeGameState(gameState *game)
{
    game->currentPlayer = WHITE;

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

    memcpy(game->board, initialBoard, sizeof(game->board));

    game->CC_x = -1;
    game->CC_y = -1;

    game->LC_x = -1;
    game->LC_y = -1;
}



static const pointCords ROOK_DIRS[4]   = {{1,0},{-1,0},{0,1},{0,-1}};
static const pointCords BISHOP_DIRS[4] = {{1,1},{1,-1},{-1,1},{-1,-1}};
static const pointCords KNIGHT_OFFSETS[8] = {
    {1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1},{-2,1},{-1,2}
};

static const pointCords KING_OFFSETS[8] = {
    {1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}
};

static int inBounds(int x, int y){
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}




static void addMove(collectionArray *moves, int x, int y){
    moves->point[moves->size].x = x;
    moves->point[moves->size].y = y;
    moves->size++;
}


static int tryAddSquare(collectionArray *moves, gameState *game, int piece, int x, int y){
    if(!inBounds(x, y)) return 0;

    int target = game->board[y][x];

    if(isBlank(target)){
        addMove(moves, x, y);
        return 1;
    }

    if( (isWhite(piece) && isBlack(target)) || (isBlack(piece) && isWhite(target)) ){
        addMove(moves, x, y);
    }
    return 0;
}



static void slideMoves(collectionArray *moves, gameState *game, int piece, int x, int y, const pointCords *dirs, int dirCount){
    for(int d=0; d<dirCount; d++){
        int nx = x, ny = y;
        do {
            nx += dirs[d].x;
            ny += dirs[d].y;
        } while(tryAddSquare(moves, game, piece, nx, ny));
    }
}



static void stepMoves(collectionArray *moves, gameState *game, int piece, int x, int y, const pointCords *offsets, int count){
    for(int i=0; i<count; i++){
        tryAddSquare(moves, game, piece, x+offsets[i].x, y+offsets[i].y);
    }
}


static void pawnMoves(collectionArray *moves, gameState *game, int piece, int x, int y){
    int dir = isWhite(piece) ? -1 : 1;
    int startRow = isWhite(piece) ? 6 : 1;

    if(inBounds(x, y+dir) && isBlank(game->board[y+dir][x])){
        addMove(moves, x, y+dir);

        if(y == startRow && isBlank(game->board[y+2*dir][x])){
            addMove(moves, x, y+2*dir);
        }
    }

    int dxs[2] = {-1, 1};
    for(int i=0; i<2; i++){
        int nx = x+dxs[i], ny = y+dir;
        if(!inBounds(nx, ny)) continue;

        int target = game->board[ny][nx];
        if( (isWhite(piece) && isBlack(target)) || (isBlack(piece) && isWhite(target)) ){
            addMove(moves, nx, ny);
        }
    }
}



collectionArray possibleMoves(gameState *game, int x, int y){
    collectionArray moves = { .size = 0 };

    int piece = game->board[y][x];
    if(isBlank(piece)) return moves;
    if(game->currentPlayer == WHITE && isBlack(piece)) return moves;
    if(game->currentPlayer == BLACK && isWhite(piece)) return moves;

    switch(piece){
        case WHITE_R: case BLACK_R:
            slideMoves(&moves, game, piece, x, y, ROOK_DIRS, 4);
            break;

        case WHITE_B: case BLACK_B:
            slideMoves(&moves, game, piece, x, y, BISHOP_DIRS, 4);
            break;

        case WHITE_Q: case BLACK_Q:
            slideMoves(&moves, game, piece, x, y, ROOK_DIRS, 4);
            slideMoves(&moves, game, piece, x, y, BISHOP_DIRS, 4);
            break;

        case WHITE_N: case BLACK_N:
            stepMoves(&moves, game, piece, x, y, KNIGHT_OFFSETS, 8);
            break;

        case WHITE_K: case BLACK_K:
            stepMoves(&moves, game, piece, x, y, KING_OFFSETS, 8);
            break;

        case WHITE_P: case BLACK_P:
            pawnMoves(&moves, game, piece, x, y);
            break;
    }

    return moves;
}






int checkBound(gameState *game){
    if(game->CC_x < 0 || game->CC_x > 7 || game->CC_y < 0 || game->CC_y > 7 ) return 0;
    if(game->LC_x < 0 || game->LC_x > 7 || game->LC_y < 0 || game->LC_y > 7 ) return 0;
    return 1;
}



int isMoveValid(gameState *game){

    if(!checkBound(game)) return 0; 

    int currentPlayer = game->currentPlayer;
    int movingPiece = game->board[game->LC_y][game->LC_x];
    int newCords_x = game->CC_x;
    int newCords_y = game->CC_y;

    if(isBlank(movingPiece)) return 0;
    if(currentPlayer == WHITE && isBlack(movingPiece)) return 0;
    if(currentPlayer == BLACK && isWhite(movingPiece)) return 0;
    

    return 1;
}



void movePiece(gameState *game){

    int isValid = 0;
    collectionArray moves = possibleMoves(game, game->LC_x, game->LC_y);
    for(int i=0; i<moves.size; i++){
        if(game->CC_x == moves.point[i].x && game->CC_y == moves.point[i].y){
            isValid = 1;
        }
    }

    if(isValid){
        
        game->board[game->CC_y][game->CC_x] = game->board[game->LC_y][game->LC_x];
        game->board[game->LC_y][game->LC_x] = 0;
        
        if(game->currentPlayer == WHITE) {
            game->currentPlayer = BLACK;
        } else if(game->currentPlayer == BLACK){
            game->currentPlayer = WHITE;
        }

    }
}