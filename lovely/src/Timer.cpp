#include "Application.h"
#include "Timer.h"
#include <SDL2/SDL.h>

namespace LovelyGUI
{

Timer::Timer()
{

}


Timer::~Timer()
{
    Application::removeTimer(this);
}



void Timer::update()
{
    Uint32 now = SDL_GetTicks();
    if((now - this->_previous) > this->_interval)
    {
        this->_callback(this->_param);
        this->_previous = now;
    }
}

void Timer::setInterval(Uint32 ms)
{
    this->_interval = ms;
}



#if __cplusplus > 201703L
    void Timer::setCallback(std::function<void(std::any)> callback, std::any param)
    {
        this->_param = param;
        this->_callback = callback;
    }
#else
    void Timer::setCallback(std::function<void(void*)> callback, void* param)
    {
        this->_param = param;
        this->_callback = callback;
    }
#endif


}; // namespace LovelyGUI