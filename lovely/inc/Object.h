#ifndef LOVELY_GUI_OBJECT
#define LOVELY_GUI_OBJECT

#include <set>

namespace LovelyGUI
{

class Object
{
public:
    Object(Object* parent=nullptr);
    virtual ~Object();

protected:
    void remove(Object* son);
    Object* _parent;
    std::set<Object*> _sons;
};

}; // namespace LovelyGUI

#endif