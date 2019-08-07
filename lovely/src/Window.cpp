#include "Window.h"

namespace LovelyGUI
{

Window::Window(int width, int height, const std::string& title)
{
    this->_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    width, height, SDL_WINDOW_SHOWN);
    if(this->_window == nullptr)
    {
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_CreateWindow : %s", SDL_GetError());
        throw std::runtime_error("SDL_CreateWindow Error");
    }
}


Window::~Window()
{
    SDL_DestroyWindow(this->_window);
}


SDL_Window* Window::window()
{
    return this->_window;
}


int Window::width()
{
    int w,h;
    SDL_GetWindowSize(this->_window, &w, &h);
    return w;
}


int Window::height()
{
    int w,h;
    SDL_GetWindowSize(this->_window, &w, &h);
    return h;
}


std::string Window::title()
{
    return SDL_GetWindowTitle(this->_window);
}


void Window::setWidth(int width)
{
    int w,h;
    SDL_GetWindowSize(this->_window, &w, &h);
    SDL_SetWindowSize(this->_window, width, h);

}


void Window::setHeight(int height)
{
    int w,h;
    SDL_GetWindowSize(this->_window, &w, &h);
    SDL_SetWindowSize(this->_window, w, height);
}


void Window::setSize(int width, int height)
{
    SDL_SetWindowSize(this->_window, width, height);
}


void Window::setTitle(const std::string& title)
{
    SDL_SetWindowTitle(this->_window, title.c_str());
}


}; // namespace LovelyGUI