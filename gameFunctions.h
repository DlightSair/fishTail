#ifndef GAME_FUCNTIONS_H
#define GAME_FUNCTIONS_H

void initializeGameState(gameState *game);
void movePiece(gameState *game);
collectionArray possibleMoves(gameState *game, int x, int y);

#endif