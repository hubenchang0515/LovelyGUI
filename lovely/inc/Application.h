#ifndef LOVELY_GUI_APPLICATION
#define LOVELY_GUI_APPLICATION

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <queue>
#include <set>

#include "Window.h"
#include "Renderer.h"

namespace LovelyGUI
{

class Widget;
class Timer;

class Application
{
public:
    Application(int width=640, int height=400, const std::string& title="LovelyGUI Application");
    ~Application();

    int exec(int argc=0, char** argv=nullptr);

    /* Read-Only */
    static Application* app();
    static Window* window();
    static Renderer* renderer();

    /* Read */
    static Widget* rootWidget();

    /* Write */
    static void setRootWidget(Widget* widget);
    static void addTimer(Timer* timer);
    static void removeTimer(Timer* timer);

private:
    static Application* _app;
    static Window* _window;
    static Renderer* _renderer;
    static Widget* _rootWidget;
    static std::queue<Widget*> _paintQueue;
    static std::set<Timer*> _timers;

    static bool _running;
    static bool update(const SDL_Event& event);
};

}; // namespace LovelyGUI


#endif