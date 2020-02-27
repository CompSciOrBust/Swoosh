#include <SDL2/SDL.h>
#include <GameObject.h>
#include <Utils.h>

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

Enemy::Enemy(SDL_Renderer *RendererRef, float *DeltaTimeUpdateRef, int Size, int X, int Y, int DeltaX, int DeltaY, float TimeToMoveRef)
{
    Renderer = RendererRef;
    DeltaTimeUpdate = DeltaTimeUpdateRef;
    Width = Size;
    Height = Size;
    PosX = X;
    PosY = Y;
    DeltaMovementX = DeltaX;
    DeltaMovementY = DeltaY;
    TimeToMove = TimeToMoveRef;
}

void Enemy::RenderObject()
{
    SDL_SetRenderDrawColor(Renderer, 255, 123, 0, 255);
    SDL_Rect CornerRect = {PosX,PosY,Width,Height};
    SDL_RenderFillRect(Renderer, &CornerRect);
}

void Enemy::UpdateObject()
{
    if(GetTime() > TimeToMove)
    {
        PosX += DeltaMovementX * *DeltaTimeUpdate * ((float)Width / 41);
        PosY += DeltaMovementY * *DeltaTimeUpdate * ((float)Height / 41);
    }
}