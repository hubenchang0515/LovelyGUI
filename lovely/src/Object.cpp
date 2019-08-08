#include "Object.h"
#include <SDL2/SDL.h>

namespace LovelyGUI
{

Object::Object(Object* parent)
{
    this->_parent = parent;
    if(parent != nullptr)
    {
        parent->add(this);
        SDL_Log("%p->add(%p)", parent, this);
    }
}

Object::~Object()
{
    SDL_Log("Object::~Object(%p)", this);

    /* delete all son Object */
    for(auto son = this->_sons.begin(); son != this->_sons.end();)
    {
        auto temp = son;
        ++son;
        delete (*temp);
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