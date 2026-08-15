#include "type.h"
#include "displayFunctions.h"

void displayBoard(AppState *appState)
{
    int cellWidth = WIDTH/BOARD_SIZE;
    int cellHeight = HEIGHT/BOARD_SIZE;

    for(int i=0; i<BOARD_SIZE; i++)
    {
        for(int j=0; j<BOARD_SIZE; j++)
        {
            if((i+j) % 2 == WHITE){
                SDL_SetRenderDrawColor(appState->renderer, 238, 238, 210, 255);
            } else{
                SDL_SetRenderDrawColor(appState->renderer, 118, 150, 86, 255);
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

void displaySDL(AppState *appState)
{
    SDL_SetRenderDrawColor(appState->renderer, 0, 0, 0, 255);
    SDL_RenderClear(appState->renderer);

    displayBoard(appState);

    SDL_RenderPresent(appState->renderer);
}