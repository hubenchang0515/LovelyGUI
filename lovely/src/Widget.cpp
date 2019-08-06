#include "Application.h"
#include "Widget.h"

namespace LovelyGUI
{
    Widget::Widget(Widget* parent):
        Object(parent)
    {

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

    void Widget::paint(SDL_Renderer* renderer)
    {
        /* Paint self */
        this->paintEvent(renderer);

        /* Paint son widgets */
        for(Object* son : _sons)
        {
            Widget* widget = dynamic_cast<Widget*>(son);
            if(widget != nullptr)
            {
                widget->paint(renderer);
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

    void Widget::paintEvent(SDL_Renderer* renderer)
    {
        static SDL_Rect rect;
        SDL_SetRenderDrawColor(renderer, 255, 105, 180, 255);
        rect.x = this->_x;
        rect.y = this->_y;
        rect.w = this->_width;
        rect.h = this->_height;
        SDL_RenderFillRect(renderer, &rect);
    }

    bool Widget::updateEvent(const SDL_Event& event)
    {
        return false;
    }

}; // namespace LovelyGUI