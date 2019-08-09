#ifndef LOVELY_GUI_TEXTURE
#define LOVELY_GUI_TEXTURE

#include "Object.h"

namespace LovelyGUI
{

class Texture : public Object
{
public:
    static const Texture DefaultTarget;
    Texture();
    Texture(SDL_Texture* sdl_texture);
    ~Texture();

    operator SDL_Texture* ();
    operator SDL_Texture* () const;
    Texture& operator = (SDL_Texture* sdl_texture);
    bool operator == (const std::nullptr_t ptr);

    int width();
    int height();

private:
    SDL_Texture* _texture;
};

}; // namespace LovelyGUI

#endif