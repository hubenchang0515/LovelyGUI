#include "Label.h"
#include "Application.h"
#include <string>

namespace LovelyGUI
{

Label::Label(Object* parent) :
    Widget(parent)
{
    this->_font = new Font(Application::font(), this);
    this->_text.clear();
    this->_texture = nullptr;
}


Label::~Label()
{
    SDL_Log("Label::~Label(%p)", this);
    if(this->_texture != nullptr)
    {
        SDL_DestroyTexture(this->_texture);
    }
}


bool Label::setText(const std::string& text)
{
    this->_text = text;
    return this->render();
}


bool Label::setFont(const std::string& file, int size)
{
    if(this->_font == nullptr)
    {
        SDL_Log("Label::setText : font is nullptr");
        return false;
    }

    this->_font->open(file, size);

    return this->render();
}


bool Label::setFontSize(int size)
{
    if(this->_font == nullptr)
    {
        SDL_Log("Label::setText : font is nullptr");
        return false;
    }

    this->_font->setSize(size);

    return this->render();
}


bool Label::dealEvent(const Event& event)
{
    if(event.type != SDL_USEREVENT)
        return false;

    SDL_Log("code %d data1 %p", event.user.code, event.user.data1);
    if(event.user.code == 123 && event.user.data1 == this)
    {
        SDL_Log("change color");
        return this->render();
    }

    return false;
}

void Label::paintEvent(Renderer* renderer)
{
    Rect screen = {this->x(), this->y(), this->width(), this->height()};
    
    renderer->setTarget(Texture::DefaultTarget);
    renderer->copy(this->_texture, nullptr, &screen);
}

bool Label::render()
{
    if(this->_text.empty() == false && this->_font != nullptr)
    {
        Surface* surface = this->_font->render(this->_text, this->frontColor(), this->backColor());
        if(surface == nullptr)
        {
            SDL_Log("Label::setText : render surface nullptr");
            return false;
        }

        if(this->_texture != nullptr)
        {
            Application::renderer()->destroyTexture(this->_texture);
        }
        this->_texture = Application::renderer()->createTextureFromSurface(surface);
        if(this->_texture == nullptr)
        {
            SDL_Log("Label::setText : render texture nullptr");
            return false;
        }
        SDL_FreeSurface(surface);

        return true;
    }
    else
    {   
        return true;
    }
}

}; // namespace LovelyGUI
