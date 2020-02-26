#include <SDL2/SDL.h>

class GameObject
{
    public:
    virtual void RenderObject();
    //virtual void CheckCollision();
    SDL_Renderer *Renderer;
    int PosX = 0;
    int PosY = 0;
    int Width = 0;
    int Height = 0;
};

void GameObject::RenderObject(){}