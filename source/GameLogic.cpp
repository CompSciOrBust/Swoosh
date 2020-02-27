#include <SDL2/SDL.h>
#include <GameObject.h>
#include <EnemyObject.h>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Utils.h>

class GameManager
{
    private:
    void SpawnEnemies();
    SDL_Renderer *Renderer;
    SDL_Event Event;
    int Width = 500;
    int Height = 500;
    int ArenaSize;
    int ArenaX;
    int ArenaY;
    bool *IsRunning;
    float TimeStarted;
    float LastUpdateTime = 0;
    float DeltaTimeUpdate;
    float LastRenderTime = 0;
    float DeltaTimeRender;
    float SpeedOfEnemies = 6;
    float NextEnemySpawnTime = 0;
    float EnemySpawnRate = 2;
    int WallSegments = 12;
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
    PlayerObject(SDL_Renderer *RendererRef, int Size, int X, int Y);
    virtual void RenderObject();
};

void GameManager::DrawFrame()
{
    DeltaTimeRender = LastRenderTime / GetTime();
    //Draw the background
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
    SDL_Rect BGRect = {0,0,Width,Height};
    SDL_RenderFillRect(Renderer, &BGRect);
    //DrawTheArena
    SDL_SetRenderDrawColor(Renderer, 54, 54, 54, 255);
    SDL_Rect ArenaRect = {ArenaX,ArenaY,ArenaSize,ArenaSize};
    SDL_RenderFillRect(Renderer, &ArenaRect);
    //Draw the game objects
    for (int i = 0; i < GameObjectsVector.size(); i++)
    {
        GameObjectsVector.at(i)->RenderObject();
    }
    LastRenderTime = GetTime();
}

void GameManager::DoLogic()
{
    DeltaTimeUpdate = LastUpdateTime / GetTime();
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
    //Update game objects
    for (int i = 4; i < GameObjectsVector.size(); i++)
    {
        GameObjectsVector.at(i)->UpdateObject();
    }
    //Spawn new enemies
    if(NextEnemySpawnTime < GetTime())
    {
        NextEnemySpawnTime = GetTime() + EnemySpawnRate;
        SpawnEnemies();
        if(EnemySpawnRate > 1) EnemySpawnRate -= 0.025;
        if(SpeedOfEnemies < 7) SpeedOfEnemies += 0.05;
    }
    LastUpdateTime = GetTime();
}

void GameManager::SpawnEnemies()
{
    //Choose a wall at random
    srand(time(0));
    int WallToUse = rand() % 4;
    int GapToUse = 2 + rand() % 8;
    int SizeOfEnemy = ArenaSize / WallSegments;
    float EnemyMoveTime = GetTime() + EnemySpawnRate;
    switch(WallToUse)
    {
        //Top wall
        case 0:
        {
            for(int Pos = WallSegments - 2; Pos > 0; Pos--)
            {
                if(Pos == GapToUse) continue;
                GameObject *EnemyObject = new Enemy(Renderer, &DeltaTimeUpdate, SizeOfEnemy, ArenaX + SizeOfEnemy * Pos, ArenaY, 0, SpeedOfEnemies, EnemyMoveTime);
                GameObjectsVector.push_back(EnemyObject);
            }
        }
        break;
        //Left wall
        case 1:
        {
            for(int Pos = WallSegments - 2; Pos > 0; Pos--)
            {
                if(Pos == GapToUse) continue;
                GameObject *EnemyObject = new Enemy(Renderer, &DeltaTimeUpdate, SizeOfEnemy, ArenaX + ArenaSize - SizeOfEnemy, ArenaY + SizeOfEnemy * Pos, -SpeedOfEnemies, 0, EnemyMoveTime);
                GameObjectsVector.push_back(EnemyObject);
            }
        }
        break;
        //Bottom wall
        case 2:
        {
            for(int Pos = WallSegments - 2; Pos > 0; Pos--)
            {
                if(Pos == GapToUse) continue;
                GameObject *EnemyObject = new Enemy(Renderer, &DeltaTimeUpdate, SizeOfEnemy, ArenaX + SizeOfEnemy * Pos, ArenaY + ArenaSize - SizeOfEnemy, 0, -SpeedOfEnemies, EnemyMoveTime);
                GameObjectsVector.push_back(EnemyObject);
            }
        }
        break;
        //Left wall
        case 3:
        {
            for(int Pos = WallSegments - 2; Pos > 0; Pos--)
            {
                if(Pos == GapToUse) continue;
                GameObject *EnemyObject = new Enemy(Renderer, &DeltaTimeUpdate, SizeOfEnemy, ArenaX, ArenaY + SizeOfEnemy * Pos, SpeedOfEnemies, 0, EnemyMoveTime);
                GameObjectsVector.push_back(EnemyObject);
            }
        }
        break;
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
    TimeStarted = GetTime();
    NextEnemySpawnTime = TimeStarted;
    //Set up Arena vars
    if (Width > Height) ArenaSize = Height;
    else ArenaSize = Width;
    ArenaSize = ArenaSize - ArenaSize % WallSegments;
    ArenaX = (Width - ArenaSize) / 2;
    ArenaY = (Height - ArenaSize) / 2;
    //Create player object
    PlayerObject *Player = new PlayerObject(RendererRef, ArenaSize / 50, ArenaX + ArenaSize / 2, ArenaY + ArenaSize / 2);
    GameObjectsVector.push_back(Player);
    //Create corners
    int CornerSize = ArenaSize / WallSegments;
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
    SDL_SetRenderDrawColor(Renderer, 255, 123, 0, 255);
    SDL_Rect CornerRect = {PosX,PosY,Width,Height};
    SDL_RenderFillRect(Renderer, &CornerRect);
}

PlayerObject::PlayerObject(SDL_Renderer *RendererRef, int Size, int X, int Y)
{
    Renderer = RendererRef;
    Width = Size;
    Height = Size;
    PosX = X;
    PosY = Y;
}

void PlayerObject::RenderObject()
{
    SDL_SetRenderDrawColor(Renderer, 0, 128, 253, 255);
    DrawCircle(Renderer, PosX, PosY, Width);
}