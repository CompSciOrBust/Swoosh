#include <SDL2/SDL.h>
#include <GameObject.h>
#include <vector>

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