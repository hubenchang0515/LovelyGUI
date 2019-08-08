#ifndef LOVELY_GUI_OBJECT
#define LOVELY_GUI_OBJECT

#include <set>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace LovelyGUI
{

using Point = SDL_Point;
using Rect = SDL_Rect;
using Color = SDL_Color;
using Texture = SDL_Texture;
using Event = SDL_Event;

class Object
{
public:
    Object(Object* parent=nullptr);
    virtual ~Object();

protected:
    void add(Object* son);
    void remove(Object* son);
    Object* _parent;
    std::set<Object*> _sons;
};

}; // namespace LovelyGUI

#endif