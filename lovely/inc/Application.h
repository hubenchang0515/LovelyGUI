#ifndef LOVELY_GUI_APPLICATION
#define LOVELY_GUI_APPLICATION

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>



namespace LovelyGUI
{

class Widget;

class Application
{
public:
    Application(int width=640, int height=400, const std::string& title="LovelyGUI Application");
    ~Application();

    int exec(int argc=0, char** argv=nullptr);

    /* Read-Only */
    static Application* app();
    static SDL_Window* window();
    static SDL_Renderer* renderer();

    /* Read */
    static int width();
    static int height();
    static std::string title();
    static Widget* rootWidget();

    /* Write */
    static void setWidth(int width);
    static void setHeight(int height);
    static void setTitle(const std::string& title);
    static Widget* setRootWidget(Widget* widget);

private:
    static Application* _app;
    static SDL_Window* _window;
    static SDL_Renderer* _renderer;
    static int _width;
    static int _height;
    static std::string _title;
    static Widget* _rootWidget;

    static bool _running;
    static bool update(const SDL_Event& event);
};

}; // namespace LovelyGUI


#endif