#include <stdexcept>

#include "Application.h"
#include "Widget.h"

namespace LovelyGUI
{

/* Singleton Pattern */
Application* Application::_app = nullptr;
SDL_Window* Application::_window = nullptr;
SDL_Renderer* Application::_renderer = nullptr;
int Application::_width = 640;
int Application::_height = 400;
std::string Application::_title = "LovelyGUI Application";
Widget* Application::_rootWidget = nullptr;
bool Application::_running = false;


/* Constructor */
Application::Application(int width, int height, const std::string& title)
{
    /* Singleton Pattern Check */
    if(Application::_app != nullptr)
    {
        throw std::runtime_error("Application had been constructed more than once.");
    }

    /* Save pointer */
    Application::_app = this;

     /* Init SDL2 */
    if(0 != SDL_Init(SDL_INIT_EVERYTHING))
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_Init : %s", SDL_GetError());
        throw std::runtime_error("SDL_Init Error");
    }

    /* Init SDL2 TTF extension */
    if(0 != TTF_Init())
    {
        SDL_Quit();
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "TTF_Init : %s", TTF_GetError());
        throw std::runtime_error("TTF_Init Error");
    }

    /* Init SDL2 image extension */
    if(0 == IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF))
    {
        TTF_Quit();
        SDL_Quit();
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "IMG_Init : %s", IMG_GetError());
        throw std::runtime_error("IMG_Init Error");
    }

    /* Create Window */
    Application::_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    width, height, SDL_WINDOW_SHOWN);
    if(Application::_window == nullptr)
    {
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_CreateWindow : %s", SDL_GetError());
        throw std::runtime_error("SDL_CreateWindow Error");
    }
    Application::_width = width;
    Application::_height = height;
    Application::_title = title;

    /* Create Renderer */
    Application::_renderer = SDL_CreateRenderer(Application::_window, -1, SDL_RENDERER_ACCELERATED);
    if(Application::_renderer == nullptr)
    {
        Application::_renderer = SDL_CreateRenderer(Application::_window, -1, SDL_RENDERER_SOFTWARE);
        if(Application::_renderer == nullptr)
        {
            SDL_DestroyWindow(Application::_window);
            IMG_Quit();
            TTF_Quit();
            SDL_Quit();
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_CreateRenderer : %s", SDL_GetError());
            throw std::runtime_error("SDL_CreateRenderer Error");
        }
    }

    Application::_rootWidget = nullptr;
}


/* Distructor */
Application::~Application()
{
    SDL_DestroyRenderer(Application::_renderer);
    SDL_DestroyWindow(Application::_window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}


/* Get Application pointer */
Application* Application::app()
{
    return Application::_app;
}

/* Get SDL_Window pointer */
SDL_Window* Application::window()
{
    return Application::_window;
}

/* Get SDL_Renderer pointer */
SDL_Renderer* Application::renderer()
{
    return Application::_renderer;
}

/* Get window width */
int Application::width()
{
    return Application::_width;
}

/* Get window height */
int Application::height()
{
    return Application::_height;
}

/* Get window title */
std::string Application::title()
{
    return Application::_title;
}

/* Get root widget */
Widget* Application::rootWidget()
{
    return Application::_rootWidget;
}

/* Set window width */
void Application::setWidth(int width)
{
    SDL_SetWindowSize(Application::_window, width, Application::_height);
    if(Application::_rootWidget != nullptr)
    {
        Application::_rootWidget->setWidth(width);
    }
}

/* Set window height */
void Application::setHeight(int height)
{
    SDL_SetWindowSize(Application::_window, Application::_width, height);
    if(Application::_rootWidget != nullptr)
    {
        Application::_rootWidget->setHeight(height);
    }
}

/* Set window title */
void Application::setTitle(const std::string& title)
{
    SDL_SetWindowTitle(Application::_window, title.c_str());
}

/* Set root widget */
void Application::setRootWidget(Widget* widget)
{
    Application::_rootWidget = widget;
    widget->setX(0);
    widget->setY(0);
    widget->setWidth(Application::_width);
    widget->setHeight(Application::_height);
}


/* Application main loop */
int Application::exec(int argc, char** argv)
{
    SDL_Event event;
    Application::_running = true;

    while(Application::_running)
    {
        /* Clear */
        SDL_SetRenderTarget(Application::_renderer, nullptr);
        SDL_SetRenderDrawColor(Application::_renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(Application::_renderer);

        /* Has no root Widget */
        if(Application::_rootWidget == nullptr)
        {
            while(SDL_PollEvent(&event) > 0)
            {
                this->update(event);
            }
            continue;
        }

        /* Paint the root Widget */
        Application::_rootWidget->paint(Application::_renderer);

        /* Deal all SDL event */
        while(SDL_PollEvent(&event) > 0)
        {
            if(Application::_rootWidget->update(event) == false)
            {
                this->update(event);
            }
        }

        /* Present */
        SDL_RenderPresent(Application::_renderer);
    }

    return 0;
}


/* Application update */
bool Application::update(const SDL_Event& event)
{
    /* Application mainloop exit */
    if(event.type == SDL_QUIT)
    {
        Application::_running = false;
    }

    return false;
}



}; // namespace LovelyGUI