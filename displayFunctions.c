#include "type.h"
#include "displayFunctions.h"

#include <SDL3_image/SDL_image.h>

static const char *pieceFileNames[PIECE_TEXTURE_COUNT] = {
    "bQ", "bK", "bR", "bB", "bN", "bP",
    NULL,
    "wP", "wN", "wB", "wR", "wK", "wQ"
};

bool loadPieceTextures(AppState *appState)
{
    char *basePath = SDL_GetBasePath();

    for (int i = 0; i < PIECE_TEXTURE_COUNT; i++)
    {
        appState->pieceTextures[i] = NULL;

        if (pieceFileNames[i] == NULL)
            continue;

        char path[512];
        SDL_snprintf(path, sizeof(path), "%sassets/pieces/%s.png",
                     basePath ? basePath : "", pieceFileNames[i]);

        appState->pieceTextures[i] = IMG_LoadTexture(appState->renderer, path);
        if (!appState->pieceTextures[i])
        {
            SDL_Log("Couldn't load texture %s: %s", path, SDL_GetError());
            return false;
        }

        SDL_SetTextureScaleMode(appState->pieceTextures[i], SDL_SCALEMODE_LINEAR);
    }

    return true;
}

void freePieceTextures(AppState *appState)
{
    for (int i = 0; i < PIECE_TEXTURE_COUNT; i++)
    {
        if (appState->pieceTextures[i])
        {
            SDL_DestroyTexture(appState->pieceTextures[i]);
            appState->pieceTextures[i] = NULL;
        }
    }
}

void displayBoard(AppState *appState)
{
    int cellWidth = WIDTH/BOARD_SIZE;
    int cellHeight = HEIGHT/BOARD_SIZE;
    int delta=0;

    for(int i=0; i<BOARD_SIZE; i++)
    {
        for(int j=0; j<BOARD_SIZE; j++)
        {
            if(appState->game.hover_x == j && appState->game.hover_y == i){
                delta = -60;
            } else {
                delta = 0;
            }

            if((i+j) % 2 == WHITE){
                SDL_SetRenderDrawColor(appState->renderer, 238+delta, 238+delta, 210+delta, 255);
            } else{
                SDL_SetRenderDrawColor(appState->renderer, 118+delta, 150+delta, 86+delta, 255);
            }

            SDL_FRect rect = {
                .x = j*cellWidth,
                .y = i*cellHeight,
                .w = cellWidth,
                .h = cellHeight
            };

            SDL_RenderFillRect(appState->renderer, &rect);
        }
    }
}

void displayPieces(AppState *appState)
{
    int cellWidth = WIDTH/BOARD_SIZE;
    int cellHeight = HEIGHT/BOARD_SIZE;

    for(int i=0; i<BOARD_SIZE; i++)
    {
        for(int j=0; j<BOARD_SIZE; j++)
        {
            int piece = appState->game.board[i][j];
            if(piece == 0)
                continue;

            SDL_Texture *texture = appState->pieceTextures[piece + 6];
            if(!texture)
                continue;

            SDL_FRect rect = {
                .x = j*cellWidth + 0.1*cellWidth,
                .y = i*cellHeight + 0.1*cellHeight,
                .w = 0.8*cellWidth,
                .h = 0.8*cellHeight
            };

            SDL_RenderTexture(appState->renderer, texture, NULL, &rect);
        }
    }
}

void displaySDL(AppState *appState)
{
    SDL_SetRenderDrawColor(appState->renderer, 0, 0, 0, 255);
    SDL_RenderClear(appState->renderer);

    displayBoard(appState);
    displayPieces(appState);

    SDL_RenderPresent(appState->renderer);
}