#ifndef LOVELY_GUI_LINEARLAYOUT
#define LOVELY_GUI_LINEARLAYOUT

#include "Widget.h"
#include <vector>

namespace LovelyGUI
{

class LinearLayout : public Widget
{
public:
    enum class Direction
    {
        Horizontal = 0,
        Vertical,
    };

    LinearLayout(Object* parent=nullptr);
    virtual ~LinearLayout();

    virtual void setWidth(int width) override;
    virtual void setHeight(int height) override;

    void setDirection(Direction direction);

    void addWidget(Widget* widget, unsigned int proportion=1);
    void removeWidget(std::size_t index);
    void insertWidget(std::size_t index, Widget* widget, unsigned int proportion=1);
    void setProportion(std::size_t index, unsigned int proportion);

private:
    Direction _direction;
    std::vector<unsigned int> _proportion;
    std::vector<Widget*> _widgets;

    void adjustWidgets();

};

};

#endif