#define WinMain SDL_main
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <GameLogic.h>

int WinMain(int argc, char* args[])
{
    //vars
    int Height = 500;
    int Width = 700;
    bool IsRunning = true;
    SDL_Renderer *Renderer;
    SDL_Event Event;
    //init
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *GameWindow = SDL_CreateWindow("Swoosh", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_OPENGL);
    Renderer = SDL_CreateRenderer(GameWindow, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    GameManager Gmgr = GameManager(Renderer, &Event, Width, Height, &IsRunning);
    //main loop
    while (IsRunning)
    {
        SDL_RenderClear(Renderer);
        Gmgr.DrawFrame();
        Gmgr.DoLogic();
        SDL_RenderPresent(Renderer);
    }
    return 0;
}