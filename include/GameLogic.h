#include <SDL2/SDL.h>
#include <GameObject.h>
#include <vector>

class GameManager
{
    private:
    SDL_Renderer *Renderer;
    SDL_Event Event;
    int Width = 500;
    int Height = 500;
    int ArenaSize;
    int ArenaX;
    int ArenaY;
    bool *IsRunning;
    std::vector<GameObject*> GameObjectsVector = std::vector<GameObject*>(0);
    public:
    void DrawFrame();
    void DoLogic();
    GameManager(SDL_Renderer *RendererRef, SDL_Event *EventRef, int WidthRef, int HeightRef, bool *IsRunningRef);
    ~GameManager();
};

class Corners : public GameObject
{
    public:
    Corners(SDL_Renderer *RendererRef, int Size, int X, int Y);
    virtual void RenderObject();
};