#include "Application.h"
#include "Widget.h"

namespace LovelyGUI
{
Widget::Widget(Object* parent):
    Object(parent)
{
    this->_x = 0;
    this->_y = 0;
    this->_width = 80;
    this->_height = 20;
    this->_backColor = {0xf0, 0xf0, 0xf0, 0xff};
    this->_frontColor = {0, 0, 0, 0};
}

Widget::~Widget()
{
    SDL_Log("Widget::~Widget(%p)", this);
}

int Widget::x()
{
    return this->_x;
}

int Widget::y()
{
    return this->_y;
}

void Widget::setX(int x)
{
    this->_x = x;
}

void Widget::setY(int y)
{
    this->_y = y;
}

int Widget::width()
{
    return this->_width;
}

int Widget::height()
{
    return this->_height;
}

void Widget::setWidth(int width)
{
    this->_width = width;
}

void Widget::setHeight(int height)
{
    this->_height = height;
}

void Widget::paint(std::queue<Widget*>& paintQueue)
{
    /* Push son widgets into queue back */
    for(Object* son : _sons)
    {
        Widget* widget = dynamic_cast<Widget*>(son);
        if(widget != nullptr)
        {
            paintQueue.push(widget);
        }
    }
}

Color Widget::frontColor()
{
    return this->_frontColor;
}

void Widget::setFrontColor(Color color)
{
    this->_frontColor = color;

    /* Push an Event */
    SDL_Event event;
    event.user.type = SDL_USEREVENT;
    event.user.code = 123;
    event.user.data1 = this;
    SDL_PushEvent(&event);
    SDL_Log("*****Push Event*****");
}


void Widget::setFrontColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    this->setFrontColor({r, g, b, a});
}

void Widget::setFrontColor(Uint8 r, Uint8 g, Uint8 b)
{
    this->setFrontColor({r, g, b, 0});
}


Color Widget::backColor()
{
    return this->_backColor;
}


void Widget::setBackColor(Color color)
{
    this->_backColor = color;

    /* Push an Event */
    SDL_Event event;
    event.user.type = SDL_USEREVENT;
    event.user.code = 123;
    event.user.data1 = this;
    SDL_PushEvent(&event);
    SDL_Log("*****Push Event*****");
}
void Widget::setBackColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    this->setBackColor({r, g, b, a});
}

void Widget::setBackColor(Uint8 r, Uint8 g, Uint8 b)
{
    this->setBackColor({r, g, b, 0});
}

bool Widget::deal(const SDL_Event& event)
{
    /* Pass event to son widgets */
    for(Object* son : _sons)
    {
        Widget* widget = dynamic_cast<Widget*>(son);
        if(widget != nullptr)
        {
            SDL_Log("Pass Event to %p", widget);
            if(widget->deal(event) == true)
            {
                return true;
            }
        }
    }

    this->dealEvent(event);
    return false;
}

void Widget::update()
{
    /* Update sons */
    for(Object* son : _sons)
    {
        Widget* widget = dynamic_cast<Widget*>(son);
        if(widget != nullptr)
        {
            widget->update();
        }
    }

    /* Update self */
    this->updateEvent();
}

void Widget::paintEvent(Renderer* renderer)
{
    static Rect rect;
    rect.x = this->x();
    rect.y = this->y();
    rect.w = this->width();
    rect.h = this->height();
    renderer->setTarget(Texture::DefaultTarget);
    renderer->setColor(0xf0, 0xf0, 0xf0);
    renderer->fillRect(rect);
}

bool Widget::dealEvent(const Event& event)
{
    return false;
}

void Widget::updateEvent()
{

}

}; // namespace LovelyGUI