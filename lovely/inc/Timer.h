#ifndef LOVELY_GUI_TIMER
#define LOVELY_GUI_TIMER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <vector>
#include <functional>

#if __cplusplus > 201703L
    #include <any>
#endif

namespace LovelyGUI
{

class Timer
{
public:
    Timer();
    ~Timer();
    void update();
    void setInterval(Uint32 ms);

    #if __cplusplus > 201703L
        void setCallback(std::function<void(std::any)> callback, std::any param);
    #else
        void setCallback(std::function<void(void*)> callback, void* param);
    #endif

private:
    Uint32 _interval;
    Uint32 _previous;

    #if __cplusplus > 201703L
        std::any _param;
        std::function<void(std::any)> _callback;
    #else
        void* _param;
        std::function<void(void*)> _callback;
    #endif
};

}; // namespace LovelyGUI
#endif