#include <SDL2/SDL.h>
#include <vector>
#include <GameObject.h>
#include <UI.h>

class GameOverScreen
{
    private:
    SDL_Renderer *Renderer;
    SDL_Event Event;
    int Width = 500;
    int Height = 500;
    int *WindowState;
    bool *IsRunning;
    std::vector<UIButton*> UIButtonsVector = std::vector<UIButton*>(0);
    public:
    GameOverScreen(SDL_Renderer *RendererRef, SDL_Event *EventRef, int WidthRef, int HeightRef, bool *IsRunningRef, int *WindowStateRef);
    void DrawFrame();
    void DoLogic();
};

GameOverScreen::GameOverScreen(SDL_Renderer *RendererRef, SDL_Event *EventRef, int WidthRef, int HeightRef, bool *IsRunningRef, int *WindowStateRef)
{
    //Set up vars
    Renderer = RendererRef;
    Event = *EventRef;
    Width = WidthRef;
    Height = HeightRef;
    WindowState = WindowStateRef;
    IsRunning = IsRunningRef;
    //Add buttons
    UIButton *RestartButton = new UIButton(Renderer, Width / 2, Height / 2 + 100, 200, 20, "Restart");
    UIButtonsVector.push_back(RestartButton);
}

void GameOverScreen::DrawFrame()
{
    //Draw the BG
    SDL_SetRenderDrawColor(Renderer, 94, 94, 94, 255);
    SDL_Rect BGRect = {0,0,Width,Height};
    SDL_RenderFillRect(Renderer, &BGRect);
    //Draw the game over text
    RenderText("GameOver!", Width / 2, Height / 2, Width, Renderer);
    for (int i = 0; i < UIButtonsVector.size(); i++)
    {
        UIButtonsVector.at(i)->RenderObject();
    }
}

void GameOverScreen::DoLogic()
{
    SDL_SetRelativeMouseMode(SDL_FALSE);
    while (SDL_PollEvent(&Event))
    {
        switch (Event.type)
        {
            //Exit button
            case SDL_QUIT:
            *IsRunning = false;
            break;
            //Mouse button
            case SDL_MOUSEBUTTONDOWN:
            for (int i = 0; i < UIButtonsVector.size(); i++)
            {
                switch (i)
                {
                    //Restart game button
                    case 0:
                    {
                        if (UIButtonsVector.at(i)->MouseOver(Event.motion.x, Event.motion.y))
                        {
                            *WindowState = 1;
                            printf("Test\n");
                        }
                        
                    }
                    break;
                }
            }
            break;
        }
    }
}