#include "Font.h"

namespace LovelyGUI
{

Font::Font(Object* parent) :
    Object(parent)
{
    this->_file.clear();
    this->_size = 16;
    this->_font = nullptr;
}

Font::Font(const Font* font, Object* parent) :
    Object(parent)
{
    this->_file = font->_file;
    this->_size = font->_size;
    this->_font = nullptr;
    this->open(this->_file, this->_size);
}

Font::~Font()
{
    SDL_Log("Font::~Font(%p)", this);
}


bool Font::open(const std::string& file, int size)
{
    if(this->_font != nullptr)
    {
        SDL_Log("TTF_CloseFont(%p)", this->_font);
        TTF_CloseFont(this->_font);
        this->_font = nullptr;
    }

    if(size <= 0)
    {
        size = this->_size;
    }

    this->_font = TTF_OpenFont(file.c_str(), size);
    if(this->_font == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "TTF_OpenFont : %s", TTF_GetError());
        return false;
    }

    this->_file = file;
    this->_size = size;
    return true;
}

void Font::close()
{
    if(this->_font != nullptr)
    {
        TTF_CloseFont(this->_font);
        this->_font = nullptr;
    }
}


bool Font::setFile(const std::string& file)
{
    return this->open(file);
}


bool Font::setSize(int size)
{
    if(this->_file.empty() == false)
    {
        return this->open(this->_file, size);
    }
    else
    {
        return false;
    }
}

Surface* Font::render(const std::string& text, Color fg, Color bg)
{
    return TTF_RenderUTF8(this->_font, text.c_str(), fg, bg);
}

}; // namespace LovelyGUI