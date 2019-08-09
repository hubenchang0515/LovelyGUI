#include "LinearLayout.h"
#include "Widget.h"
#include <vector>

namespace LovelyGUI
{


    LinearLayout::LinearLayout(Object* parent) :
        Widget(parent)
    {
        this->_direction = Direction::Horizontal;
    }

    LinearLayout::~LinearLayout()
    {
        SDL_Log("LinearLayout::~LinearLayout(%p)", this);
    }

    void LinearLayout::setWidth(int width)
    {
        Widget::setWidth(width);
        this->adjustWidgets();
    }

    void LinearLayout::setHeight(int height)
    {
        Widget::setHeight(height);
        this->adjustWidgets();
    }

    void LinearLayout::setDirection(Direction direction)
    {
        this->_direction = direction;
        this->adjustWidgets();
    }

    void LinearLayout::addWidget(Widget* widget, unsigned int proportion)
    {
        this->_widgets.push_back(widget);
        this->_proportion.push_back(proportion);
        this->adjustWidgets();
    }

    void LinearLayout::removeWidget(std::size_t index)
    {
        this->_proportion.erase(this->_proportion.begin() + index);
        this->_widgets.erase(this->_widgets.begin()+ index);
        this->adjustWidgets();
    }

    void LinearLayout::insertWidget(std::size_t index, Widget* widget, unsigned int proportion)
    {
        this->_widgets.insert(this->_widgets.begin()+ index, widget);
        this->_proportion.insert(this->_proportion.begin() + index, proportion);
        this->adjustWidgets();
    }

    void LinearLayout::setProportion(std::size_t index, unsigned int proportion)
    {
        this->_proportion[index] = proportion;
        this->adjustWidgets();
    }

    void LinearLayout::adjustWidgets()
    {
        double totalProportion = 0;
        for(auto& i : this->_proportion)
        {
            totalProportion += i;
        }

        std::size_t index = 0;
        int space = 0;
        for(Widget* widget : this->_widgets)
        {
            if(this->_direction == Direction::Horizontal)
            {
                widget->setY(this->y());
                widget->setHeight(this->height());

                widget->setX(this->x() + space);
                int width = this->_proportion[index] / totalProportion * this->width();
                widget->setWidth(width);
                space += width;
            }
            else
            {
                widget->setX(this->x());
                widget->setWidth(this->width());

                widget->setY(this->y() + space);
                int height = this->_proportion[index] / totalProportion * this->height();
                widget->setHeight(height);
                space += height;
            }

            index += 1;
        }
    }

};