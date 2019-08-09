#include "Texture.h"

namespace LovelyGUI
{

const Texture Texture::DefaultTarget;

Texture::Texture()
{
    this->_texture = nullptr;
}

Texture::Texture(SDL_Texture* sdl_texture) :
    Object(nullptr)
{
    this->_texture = sdl_texture;
}

Texture::~Texture() 
{
    SDL_Log("Texture::~Texture(%p)", this);
}

Texture::operator SDL_Texture* ()
{
    return this->_texture;
}

Texture::operator SDL_Texture* () const
{
    return this->_texture;
}

bool Texture::operator == (const std::nullptr_t ptr)
{
    return this->_texture == ptr;
}

Texture& Texture::operator = (SDL_Texture* sdl_texture)
{
    if(this->_texture != nullptr)
    {
        SDL_DestroyTexture(this->_texture);
    }

    this->_texture = sdl_texture;

    return *this;
}


int Texture::width()
{
    Uint32 format;
    int access;
    int w;
    int h;

    SDL_QueryTexture(this->_texture, &format, &access, &w, &h);

    return w;
}


int Texture::height()
{
    Uint32 format;
    int access;
    int w;
    int h;

    SDL_QueryTexture(this->_texture, &format, &access, &w, &h);

    return w;
}

}; // namespace LovelyGUI