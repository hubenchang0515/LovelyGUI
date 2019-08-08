#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Spectrogram.h"

namespace LovelyGUI
{

Spectrogram::Spectrogram(Object* parent) :
    Widget(parent)
{
    this->adjustTexture();
}

Spectrogram::~Spectrogram()
{
    SDL_Log("Spectrogram::~Spectrogram(%p)", this);

    SDL_DestroyTexture(this->_texture);
}

void Spectrogram::setWidth(int width)
{
    Widget::setWidth(width);
    this->adjustTexture();
}

void Spectrogram::setHeight(int height)
{
    Widget::setHeight(height);
    this->adjustTexture();
}

void Spectrogram::pushLine(const std::vector<Color>& line)
{
    Rect srcRect, dstRect;
    srcRect.x = 0;
    srcRect.y = 1;
    srcRect.w = this->width();
    srcRect.h = this->height() - 1;

    dstRect.x = 0;
    dstRect.y = 0;
    dstRect.w = this->width();
    dstRect.h = this->height() - 1;

    Application::renderer()->setTarget(this->_texture);
    Application::renderer()->copy(this->_texture, &srcRect, &dstRect);
    
    for(int i = 0; i < this->width() && ((std::size_t)i) < line.size(); i++)
    {
        Rect rect = {10,10,10,10};
        Application::renderer()->setColor(line[i]);
        Application::renderer()->drawPoint(i, this->height() - 1);
    }
    Application::renderer()->setTarget(nullptr);
}


void Spectrogram::paintEvent(Renderer* renderer)
{
    Application::renderer()->setTarget(nullptr);
    Rect screen = {this->x(), this->y(), this->width(), this->height()};
    Application::renderer()->copy(this->_texture, nullptr, &screen);
}

void Spectrogram::adjustTexture()
{
    if(this->_texture == nullptr)
    {
        Application::renderer()->destroyTexture(this->_texture);
    }

    if(this->width() == 0 || this->height() == 0)
    {
        return;
    }

    this->_texture = Application::renderer()->createTexture(this->width(), this->height());
    if(this->_texture == nullptr)
    {
        SDL_Log("%s", SDL_GetError());
        throw std::runtime_error("Spectrogram Error");
    }
}

}; // namespace LovelyGUI