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
class Worker;

class Application : public Object
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
    static void addWorker(Worker* worker);
    static void removeWorker(Worker* worker);

private:
    static Application* _app;
    static Window* _window;
    static Renderer* _renderer;
    static Widget* _rootWidget;
    static std::queue<Widget*> _paintQueue;
    static std::set<Worker*> _workers;

    static bool _running;
    static bool update(const SDL_Event& event);
};

}; // namespace LovelyGUI


#endif