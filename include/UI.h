#include <string>

class UIButton : public GameObject
{
    public:
    UIButton(SDL_Renderer *RendererRef, int PosXRef, int PosYRef, int WidthRef, int HeightRef, std::string Text);
    std::string ButtonText = "Button text";
    bool MouseOver(int MouseX, int MouseY);
};

void RenderText(std::string Text, int PosX, int PosY, int MaxWidth, SDL_Renderer *Renderer);