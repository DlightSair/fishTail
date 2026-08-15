#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>

#include "type.h"
#include "gameFunctions.h"
#include "displayFunctions.h"

int WIDTH = 800;
int HEIGHT = 800;


SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    AppState *state = malloc( sizeof(AppState) );
    initializeGameState(state);
    
    *appstate = state;
    
    if(!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't Initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if(!SDL_CreateWindowAndRenderer("Chess", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE, &state->window, &state->renderer)){
        SDL_Log("Couldn't Initilize Windor/Renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if(!loadPieceTextures(state)) {
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}



SDL_AppResult SDL_AppIterate(void *appstate)
{
    AppState *state = (AppState *)appstate;

    displaySDL(state);

    return SDL_APP_CONTINUE;
}



SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{

    AppState *state = (AppState *)appstate;

    switch (event->type)
    {

    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
        break;
    
    case SDL_EVENT_WINDOW_RESIZED:
        WIDTH = event->window.data1;
        HEIGHT = event->window.data2;
        break;

    case SDL_EVENT_MOUSE_MOTION:
        state->game.hover_x = event->motion.x/(WIDTH/BOARD_SIZE);
        state->game.hover_y = event->motion.y/(HEIGHT/BOARD_SIZE);
        break;

    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        int click_x = event->button.x/(WIDTH/BOARD_SIZE);
        int click_y = event->button.y/(HEIGHT/BOARD_SIZE);

        int isClickSame = (state->game.CC_x == click_x && state->game.CC_y == click_y);
        if( !isClickSame ){
            state->game.LC_x = state->game.CC_x;
            state->game.LC_y = state->game.CC_y;

            state->game.CC_x = click_x;
            state->game.CC_y = click_y;
        } 
        
        movePiece(state);

        break;

    default:
        state->game.hover_x = -1;
        state->game.hover_y = -1;
        break;

    }

    return SDL_APP_CONTINUE;
}



void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    AppState *state = (AppState *)appstate;

    if(state) {
        freePieceTextures(state);
        free(state);
    }
}