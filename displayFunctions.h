#ifndef DISPLAY_FUNCTIONS_H
#define DISPLAY_FUNCTIONS_H

#include "type.h"

void displayBoard(AppState *appState);
void displayPieces(AppState *appState);
void displaySDL(AppState *appState);

bool loadPieceTextures(AppState *appState);
void freePieceTextures(AppState *appState);

#endif
