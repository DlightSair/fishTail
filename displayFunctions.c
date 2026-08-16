#include "type.h"
#include "displayFunctions.h"
#include "gameFunctions.h"

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

void displayBoardandPieces(AppState *appState)
{
    int cellWidth = WIDTH/BOARD_SIZE;
    int cellHeight = HEIGHT/BOARD_SIZE;
    int delta=0;
    float ratio = 0.75;

    for(int i=0; i<BOARD_SIZE; i++)
    {
        for(int j=0; j<BOARD_SIZE; j++)
        {

            if(appState->game.hover_x == j && appState->game.hover_y == i){
                delta = -60;
                ratio = 0.95;
            } else {
                delta = 0;
                ratio = 0.8;
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


            int piece = appState->game.board[i][j];
            if(!piece)
                continue;

            SDL_Texture *texture = appState->pieceTextures[piece + 6];
            if(!texture)
                continue;

            SDL_FRect pieceRect = {
                .x = j*cellWidth + (1-ratio)*cellWidth*0.5,
                .y = i*cellHeight + (1-ratio)*cellHeight*0.5,
                .w = ratio*cellWidth,
                .h = ratio*cellHeight
            };

            SDL_RenderTexture(appState->renderer, texture, NULL, &pieceRect);
        }
    }
}


void displayPossibleMoves(AppState *AppState)
{
    int cellWidth = WIDTH/BOARD_SIZE;
    int cellHeight = HEIGHT/BOARD_SIZE;

    int x_pos = AppState->game.CC_x;
    int y_pos = AppState->game.CC_y;

    int piece = AppState->game.board[y_pos][x_pos];

    collectionArray moves = possibleMoves(&AppState->game, x_pos, y_pos);
    SDL_SetRenderDrawColor(AppState->renderer, 180, 180, 180, 80);

    for(int i=0; i<moves.size; i++){

        SDL_FRect rect = {
            .x = (moves.point[i].x + 0.25) * cellWidth,
            .y = (moves.point[i].y + 0.25) * cellHeight,
            .w = cellWidth * 0.5,
            .h = cellHeight * 0.5
        };

        SDL_RenderFillRect(AppState->renderer, &rect);
    }

    
}

void displaySDL(AppState *appState)
{
    SDL_SetRenderDrawColor(appState->renderer, 0, 0, 0, 255);
    SDL_RenderClear(appState->renderer);

    displayBoardandPieces(appState);
    displayPossibleMoves(appState);

    SDL_RenderPresent(appState->renderer);
}