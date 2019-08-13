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
    virtual int z();
    virtual void setX(int x);
    virtual void setY(int y);
    virtual void setZ(int z);

    virtual int width();
    virtual int height();
    virtual void setWidth(int width);
    virtual void setHeight(int height);

    virtual bool visiable();
    virtual void setVisiable(bool visiable=true);

    virtual Color frontColor();
    virtual void setFrontColor(Color color);
    virtual void setFrontColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    virtual void setFrontColor(Uint8 r, Uint8 g, Uint8 b);

    virtual Color backColor();
    virtual void setBackColor(Color color);
    virtual void setBackColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    virtual void setBackColor(Uint8 r, Uint8 g, Uint8 b);

protected:
    virtual void paintEvent(Renderer* renderer);
    virtual bool dealEvent(const Event& event);
    virtual void updateEvent();

private:
    int _x;
    int _y;
    int _z;
    int _width;
    int _height;

    bool _visiable;
    
    Color _frontColor;
    Color _backColor;

    virtual void paint(Renderer* renderer) final;
    virtual bool deal(const Event& event) final;
    virtual void update() final;
};

}; // namespace LovelyGUI

#endif