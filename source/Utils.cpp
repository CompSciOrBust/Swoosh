#include <time.h>
#include <cmath>
#include <SDL2/SDL.h>

float GetTime()
{
    return (float)clock()/CLOCKS_PER_SEC;
}

void DrawCircle(SDL_Renderer *Renderer, int CentreX, int CentreY, int Radius)
{
    //I couldn't find a nice algorithm for drawing circles so I wrote my own
    for(int i = Radius * Radius; i > 0; i--)
    {
        int x = i % Radius;
        int y = (i - x) / Radius;
        if(sqrt(x*x+y*y) < Radius)
        {
            SDL_RenderDrawPoint(Renderer, CentreX + x, CentreY + y);
            SDL_RenderDrawPoint(Renderer, CentreX + -x, CentreY + y);
            SDL_RenderDrawPoint(Renderer, CentreX + x, CentreY + -y);
            SDL_RenderDrawPoint(Renderer, CentreX + -x, CentreY + -y);
        }
    }
    SDL_RenderDrawPoint(Renderer, CentreX, CentreY);
}