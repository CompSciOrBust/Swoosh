#include <SDL2/SDL.h>
#include <GameObject.h>
#include <vector>
#include <stdio.h>

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

class PlayerObject : public GameObject
{
    public:
    PlayerObject(SDL_Renderer *RendererRef, int Size);
    virtual void RenderObject();
};

void GameManager::DrawFrame()
{
    //Draw the background
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
    SDL_Rect BGRect = {0,0,Width,Height};
    SDL_RenderFillRect(Renderer, &BGRect);
    //DrawTheArena
    SDL_SetRenderDrawColor(Renderer, 94, 94, 94, 255);
    SDL_Rect ArenaRect = {ArenaX,ArenaY,ArenaSize,ArenaSize};
    SDL_RenderFillRect(Renderer, &ArenaRect);
    //Draw the game objects
    for (int i = 0; i < GameObjectsVector.size(); i++)
    {
        GameObjectsVector.at(i)->RenderObject();
    }
    
}

void GameManager::DoLogic()
{
    //Scan input
    while (SDL_PollEvent(&Event))
    {
        switch (Event.type)
        {
            case SDL_QUIT:
            *IsRunning = false;
            break;
            case SDL_MOUSEMOTION:
            {
                if(SDL_GetRelativeMouseMode() == SDL_TRUE)
                {
                    //Updater player x and y cords
                    GameObjectsVector.at(0)->PosX += Event.motion.xrel;
                    GameObjectsVector.at(0)->PosY += Event.motion.yrel;
                    //Check player is with in the bounds of the arena
                    if(GameObjectsVector.at(0)->PosX > ArenaX + ArenaSize)
                    {
                        GameObjectsVector.at(0)->PosX = ArenaX + ArenaSize;
                    }
                    else if(GameObjectsVector.at(0)->PosX < ArenaX)
                    {
                        GameObjectsVector.at(0)->PosX = ArenaX;
                    }
                    else if(GameObjectsVector.at(0)->PosY > ArenaY + ArenaSize)
                    {
                        GameObjectsVector.at(0)->PosY = ArenaY + ArenaSize;
                    }
                    else if(GameObjectsVector.at(0)->PosY < ArenaY)
                    {
                         GameObjectsVector.at(0)->PosY = ArenaY;
                    }
                }
            }
            break;
            case SDL_KEYDOWN:
            {
                if (Event.key.keysym.sym == SDLK_ESCAPE)
                {
                    if (SDL_GetRelativeMouseMode() == SDL_TRUE) SDL_SetRelativeMouseMode(SDL_FALSE);
                    else SDL_SetRelativeMouseMode(SDL_TRUE);
                }
                
            }
            break;
        }
    }
    
}

GameManager::GameManager(SDL_Renderer *RendererRef, SDL_Event *EventRef, int WidthRef, int HeightRef, bool *IsRunningRef)
{
    SDL_SetRelativeMouseMode(SDL_TRUE);
    Renderer = RendererRef;
    Event = *EventRef;
    Width = WidthRef;
    Height = HeightRef;
    IsRunning = IsRunning;
    //Set up Arena vars
    if (Width > Height) ArenaSize = Height;
    else ArenaSize = Width;
    ArenaX = (Width - ArenaSize) / 2;
    ArenaY = (Height - ArenaSize) / 2;
    //Create player object
    PlayerObject *Player = new PlayerObject(RendererRef, ArenaSize / 50);
    GameObjectsVector.push_back(Player);
    //Create corners
    int CornerSize = ArenaSize / 10;
    Corners *CornerTL = new Corners(RendererRef, CornerSize, ArenaX, ArenaY);
    Corners *CornerTR = new Corners(RendererRef, CornerSize, ArenaX + ArenaSize - CornerSize, ArenaY);
    Corners *CornerBL = new Corners(RendererRef, CornerSize, ArenaX, ArenaY + ArenaSize - CornerSize);
    Corners *CornerBR = new Corners(RendererRef, CornerSize, ArenaX + ArenaSize - CornerSize, ArenaY + ArenaSize - CornerSize);
    GameObjectsVector.push_back(CornerTL);
    GameObjectsVector.push_back(CornerTR);
    GameObjectsVector.push_back(CornerBL);
    GameObjectsVector.push_back(CornerBR);
}

GameManager::~GameManager()
{
}

Corners::Corners(SDL_Renderer *RendererRef, int Size, int x, int y)
{
    Renderer = RendererRef;
    Width = Size;
    Height = Size;
    PosX = x;
    PosY = y;
}

void Corners::RenderObject()
{
    SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
    SDL_Rect CornerRect = {PosX,PosY,Width,Height};
    SDL_RenderFillRect(Renderer, &CornerRect);
}

PlayerObject::PlayerObject(SDL_Renderer *RendererRef, int Size)
{
    Renderer = RendererRef;
    Width = Size;
    Height = Size;
}

void PlayerObject::RenderObject()
{
    SDL_SetRenderDrawColor(Renderer, 0, 0, 255, 255);
    SDL_Rect CornerRect = {PosX,PosY,Width,Height};
    SDL_RenderFillRect(Renderer, &CornerRect);
}