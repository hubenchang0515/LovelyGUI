#ifndef LOVELY_GUI_WIDGET
#define LOVELY_GUI_WIDGET

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <queue>

#include "Object.h"

namespace LovelyGUI
{

class Application;

class Widget : public Object
{
    friend class Application;
public:
    Widget(Widget* parent=nullptr);
    virtual ~Widget();

    int x();
    int y();
    void setX(int x);
    void setY(int y);

    int width();
    int height();
    void setWidth(int width);
    void setHeight(int height);

protected:
    void paintEvent(SDL_Renderer* renderer);
    bool updateEvent(const SDL_Event& event);

private:
    int _x;
    int _y;
    int _width;
    int _height;

    void paint(std::queue<Widget*>& paintQueue);
    bool update(const SDL_Event& event);
};

}; // namespace LovelyGUI

#endif