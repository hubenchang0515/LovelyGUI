#ifndef LOVELY_GUI_WINDOW
#define LOVELY_GUI_WINDOW

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <stdexcept>

namespace LovelyGUI
{

class Window
{
public:
    Window(int width=640, int height=400, const std::string& title="LovelyGUI Application");
    ~Window();

    /* Read */
    SDL_Window* window();
    int width();
    int height();
    std::string title();

    /* Write */
    void setWidth(int width);
    void setHeight(int height);
    void setSize(int width, int height);
    void setTitle(const std::string& title);


private:
    SDL_Window* _window;
};

}; // namespace LovelyGUI

#endif