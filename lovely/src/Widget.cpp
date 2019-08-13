#include "Application.h"
#include "Widget.h"

namespace LovelyGUI
{
Widget::Widget(Object* parent):
    Object(parent)
{
    this->_x = 0;
    this->_y = 0;
    this->_z = 0;
    this->_width = 80;
    this->_height = 20;
    this->_visiable = true;
    this->_backColor = {0xf0, 0xf0, 0xf0, 0xff};
    this->_frontColor = {0, 0, 0, 0};

    Widget* widget = dynamic_cast<Widget*>(parent);
    if(widget != nullptr)
    {
        this->_z = widget->_z + 1;
    }

    Application::addWidget(this);
}

Widget::~Widget()
{
    SDL_Log("Widget::~Widget(%p)", this);
    Application::removeWidget(this);
}

int Widget::x()
{
    return this->_x;
}

int Widget::y()
{
    return this->_y;
}

int Widget::z()
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

void Widget::setZ(int z)
{
    this->_z = z;
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

bool Widget::visiable()
{
    return this->_visiable;
}
void Widget::setVisiable(bool visiable)
{
    this->_visiable = visiable;
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

    //  TODO: code Event system 
    SDL_Event event;
    event.user.type = SDL_USEREVENT;
    event.user.code = 123;
    event.user.data1 = this;
    SDL_PushEvent(&event);
}
void Widget::setBackColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    this->setBackColor({r, g, b, a});
}

void Widget::setBackColor(Uint8 r, Uint8 g, Uint8 b)
{
    this->setBackColor({r, g, b, 0});
}

void Widget::paint(Renderer* renderer)
{
    this->paintEvent(renderer);
}

bool Widget::deal(const SDL_Event& event)
{
    return this->dealEvent(event);
}

void Widget::update()
{
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