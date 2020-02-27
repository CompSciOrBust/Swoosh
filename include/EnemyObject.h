#include <SDL2/SDL.h>

class Enemy : public GameObject
{
    private:
    float DeltaMovementX;
    float DeltaMovementY;
    float TimeToMove;
    public:
    Enemy(SDL_Renderer *RendererRef, float *DeltaTimeUpdateRef, int Size, int X, int Y, int DeltaX, int DeltaY, float TimeToMoveRef);
    virtual void RenderObject();
    virtual void UpdateObject();
};