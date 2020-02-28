#include <SDL2/SDL.h>
#include <vector>
//#include <GameObject.h>
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