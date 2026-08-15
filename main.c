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
    switch (event->type)
    {

    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
        break;
    
    case SDL_EVENT_WINDOW_RESIZED:
        WIDTH = event->window.data1;
        HEIGHT = event->window.data2;
        break;

    default:
        break;

    }

    return SDL_APP_CONTINUE;
}



void SDL_AppQuit(void *appstate, SDL_AppResult result)
{

}