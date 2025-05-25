#include "input.h"

#include <SDL3/SDL.h>

static SDL_Event frame_event = {0};
static bool move_up = false;
static bool move_down = false;
static bool quit_called = false;

bool I_Init()
{
    if(!SDL_InitSubSystem(SDL_INIT_EVENTS)) return false;
    return true;
}

void I_Stop()
{
    SDL_QuitSubSystem(SDL_INIT_EVENTS);
}

void I_Update()
{
    while(SDL_PollEvent(&frame_event))
    {
        switch(frame_event.type)
        {
            case SDL_EVENT_QUIT:
                quit_called = true;
                break;
            case SDL_EVENT_KEY_DOWN:
                if(frame_event.key.key == SDLK_UP)
                    move_up = true;
                if(frame_event.key.key == SDLK_DOWN)
                    move_down = true;
                if(frame_event.key.key == SDLK_ESCAPE)
                    quit_called = true;
                break;
            case SDL_EVENT_KEY_UP:
                if(frame_event.key.key == SDLK_UP)
                    move_up = false;
                if(frame_event.key.key == SDLK_DOWN)
                    move_down = false;
                break;
            default:
                break;
        }
    }
}

bool I_MoveUp()     { return move_up; }
bool I_MoveDown()   { return move_down; }
bool I_QuitCalled() { return quit_called; }