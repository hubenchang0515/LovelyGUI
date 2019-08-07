#include "Application.h"
#include "Widget.h"

namespace LovelyGUI
{
    Widget::Widget(Widget* parent):
        Object(parent)
    {
        this->_x = 0;
        this->_y = 0;
        this->_width = 80;
        this->_height = 20;
    }

    Widget::~Widget()
    {

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

    bool Widget::update(const SDL_Event& event)
    {
        /* Update son widgets */
        for(Object* son : _sons)
        {
            Widget* widget = dynamic_cast<Widget*>(son);
            if(widget != nullptr)
            {
                if(widget->update(event) == false)
                {
                    return this->updateEvent(event);
                }
                else
                {
                    return true;
                }
            }
        }

        return false;
    }

    void Widget::paintEvent(Renderer* renderer)
    {
        static Rect rect;
        rect.x = this->_x;
        rect.y = this->_y;
        rect.w = this->_width;
        rect.h = this->_height;
        renderer->setColor(255, 105, 180);
        renderer->fillRect(rect);
        renderer->setColor(255, 255, 255);
        renderer->fillRect(rect);
    }

    bool Widget::updateEvent(const Event& event)
    {
        return false;
    }

}; // namespace LovelyGUI