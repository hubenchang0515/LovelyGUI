#ifndef LOVELY_GUI_WIDGET
#define LOVELY_GUI_WIDGET

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <queue>

#include "Object.h"
#include "Renderer.h"

namespace LovelyGUI
{

class Application;

class Widget : public Object
{
    friend class Application;
public:
    Widget(Object* parent=nullptr);
    virtual ~Widget();

    virtual int x();
    virtual int y();
    virtual void setX(int x);
    virtual void setY(int y);

    virtual int width();
    virtual int height();
    virtual void setWidth(int width);
    virtual void setHeight(int height);

protected:
    virtual void paintEvent(Renderer* renderer);
    virtual bool dealEvent(const Event& event);
    virtual void updateEvent();

private:
    int _x;
    int _y;
    int _width;
    int _height;

    virtual void paint(std::queue<Widget*>& paintQueue) final;
    virtual bool deal(const Event& event) final;
    virtual void update() final;
};

}; // namespace LovelyGUI

#endif