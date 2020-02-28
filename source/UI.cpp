#include <GameObject.h>
#include <string>
#include <SDL2/SDL_ttf.h>

class UIButton : public GameObject
{
    public:
    UIButton(SDL_Renderer *RendererRef, int PosXRef, int PosYRef, int WidthRef, int HeightRef, std::string Text);
    std::string ButtonText = "Button text";
    bool MouseOver(int MouseX, int MouseY);
    virtual void RenderObject();
};

UIButton::UIButton(SDL_Renderer *RendererRef, int PosXRef, int PosYRef, int WidthRef, int HeightRef, std::string Text)
{
    Renderer = RendererRef;
    PosX = PosXRef;
    PosY = PosYRef;
    Width = WidthRef;
    Height = HeightRef;
    ButtonText = Text;
}

bool UIButton::MouseOver(int MouseX, int MouseY)
{
    if (MouseX > PosX && MouseX < PosX + Width && MouseY > PosY && MouseY < PosY + Height) return true;
    else return false;
}

void UIButton::RenderObject()
{
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
    SDL_Rect ButtonRect = {PosX - Width / 2, PosY - Height / 2, Width, Height};
    SDL_RenderFillRect(Renderer, &ButtonRect);
}

void RenderText(std::string Text, int PosX, int PosY, int MaxWidth, SDL_Renderer *Renderer)
{
    SDL_Color TextColour = {255, 255, 255};
    TTF_Font *TextFont = TTF_OpenFont("C:\\Windows\\Fonts\\Arial.ttf", 28 );
    SDL_Surface* GameOverTextSurface = TTF_RenderText_Blended_Wrapped(TextFont, Text.c_str(), TextColour, MaxWidth);
    SDL_Texture* GameOverTextTexture = SDL_CreateTextureFromSurface(Renderer, GameOverTextSurface);
    SDL_Rect TextRect = {PosX - GameOverTextSurface->w / 2, PosY - GameOverTextSurface->h / 2, GameOverTextSurface->w, GameOverTextSurface->h};
    SDL_RenderCopy(Renderer, GameOverTextTexture, NULL, &TextRect);
    SDL_DestroyTexture(GameOverTextTexture);
    SDL_FreeSurface(GameOverTextSurface);
}