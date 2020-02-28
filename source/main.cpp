#define WinMain SDL_main
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <GameLogic.h>
#include <GameOverScreen.h>
int WinMain(int argc, char* args[])
{
    //vars
    int Height = 500;
    int Width = 700;
    int WindowState = 1;
    bool IsRunning = true;
    SDL_Renderer *Renderer;
    SDL_Event Event;
    //init
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Window *GameWindow = SDL_CreateWindow("Swoosh", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_OPENGL);
    Renderer = SDL_CreateRenderer(GameWindow, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    GameOverScreen Gos = GameOverScreen(Renderer, &Event, Width, Height, &IsRunning, &WindowState);
    GameManager Gmgr = GameManager(Renderer, &Event, Width, Height, &IsRunning, &WindowState);
    //main loop
    while (IsRunning)
    {
        switch (WindowState)
        {
            //Main menu
            case 0:
            {

            }
            break;
            //Gameplay
            case 1:
            {
                SDL_RenderClear(Renderer);
                Gmgr.DrawFrame();
                Gmgr.DoLogic();
                SDL_RenderPresent(Renderer);
                if(WindowState == 2) Gos = GameOverScreen(Renderer, &Event, Width, Height, &IsRunning, &WindowState);
            }
            break;
            //Game over
            case 2:
            {
                SDL_RenderClear(Renderer);
                Gos.DrawFrame();
                Gos.DoLogic();
                SDL_RenderPresent(Renderer);
                if(WindowState == 1) Gmgr = GameManager(Renderer, &Event, Width, Height, &IsRunning, &WindowState); //TODO: Don't crash. Fix in next commit.
            }
            break;
        }
    }
    return 0;
}