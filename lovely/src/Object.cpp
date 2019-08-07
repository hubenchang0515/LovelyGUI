#include "Object.h"

namespace LovelyGUI
{

Object::Object(Object* parent)
{
    this->_parent = parent;
    if(parent != nullptr)
    {
        parent->add(this);
    }
}

Object::~Object()
{
    /* delete all son Object */
    for(Object* son : this->_sons)
    {
        delete son;
    }

    /* Remove self from parent's son Objects list */
    if(this->_parent != nullptr)
    {
        this->_parent->remove(this);
    }
}

void Object::add(Object* son)
{
    this->_sons.insert(son);
}

void Object::remove(Object* son)
{
    this->_sons.erase(son);
}

}; // namespace LovelyGUI