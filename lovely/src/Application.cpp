#include <stdexcept>
#include <algorithm>

#include "Application.h"
#include "Widget.h"
#include "Timer.h"

namespace LovelyGUI
{

/* Singleton Pattern */
Application* Application::_app = nullptr;
Window* Application::_window = nullptr;
Renderer* Application::_renderer = nullptr;
Widget* Application::_rootWidget = nullptr;
Font* Application::_font = nullptr;
bool Application::_running = false;
std::set<Worker*> Application::_workers;
std::vector<Widget*> Application::_widgets;


/* Constructor */
Application::Application(int width, int height, const std::string& title) :
    Object(nullptr)
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
    try
    {
        Application::_window = new Window(width, height, title, this);
    }
    catch(const std::exception& e)
    {
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_CreateWindow : %s", e.what());
        throw std::runtime_error("SDL_CreateWindow Error");
    }

    /* Create Renderer */
    try
    {
        Application::_renderer = new Renderer(Application::_window);
    }
    catch(const std::exception& e)
    {
        delete Application::_window;
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_CreateRenderer : %s", e.what());
        throw std::runtime_error("SDL_CreateRenderer Error");
    }

    Application::_rootWidget = nullptr;
}


/* Distructor */
Application::~Application()
{
    SDL_Log("Application::~Application(%p)", this);
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
Window* Application::window()
{
    return Application::_window;
}

/* Get SDL_Renderer pointer */
Renderer* Application::renderer()
{
    return Application::_renderer;
}

/* Get font */
Font* Application::font()
{
    return Application::_font;
}

/* Get root widget */
Widget* Application::rootWidget()
{
    return Application::_rootWidget;
}

/* Set root widget */
void Application::setRootWidget(Widget* widget)
{
    Application::_rootWidget = widget;
    widget->setX(0);
    widget->setY(0);
    widget->setWidth(Application::_window->width());
    widget->setHeight(Application::_window->height());
}


/* Add timer */
void Application::addWorker(Worker* worker)
{
    Application::_workers.insert(worker);
}


/* Remove timer */
void Application::removeWorker(Worker* worker)
{
    Application::_workers.erase(worker);
}

/* Setting default font file */
bool Application::setDefaultFont(const std::string& file, int size)
{
    Application::_font = new Font(Application::app());
    return Application::_font->open(file, size);
}

/* Add widget to paint */
bool Application::addWidget(Widget* widget)
{
    /* Find the first element while element->z < widget->z or element == widget */
    std::vector<Widget*>::iterator index = std::find_if(Application::_widgets.begin(),
                                                        Application::_widgets.end(),
                                                        [&widget](Widget* element) -> bool
                                                        {
                                                            return widget->_z < element->_z || widget == element;
                                                        });

    /* Add widget into Application Widgets List */
    if(index == Application::_widgets.end() || *index != widget)
    {
        Application::_widgets.insert(index, widget);
    }
    else //  widget == *index
    {
        SDL_Log("Re-Add widget(%p) into Application Widgets List.", widget);
        return false;
    }

    return true;
}


/* Remove widget to not paint */
bool Application::removeWidget(Widget* widget)
{
    /* Find the first element while element == widget */
    std::vector<Widget*>::iterator index = std::find_if(Application::_widgets.begin(),
                                                        Application::_widgets.end(),
                                                        [&widget](Widget* element) -> bool
                                                        {
                                                            return widget == element;
                                                        });
    if(index != Application::_widgets.end())
    {
        Application::_widgets.erase(index);
    }
    else
    {
        SDL_Log("Remove invalid widget(%p) from Application Widgets List.", widget);
        return false;
    }

    return true;
}

/* Application main loop */
int Application::exec(int argc, char** argv)
{
    SDL_Event event;
    Application::_running = true;
    Uint32 ticks = SDL_GetTicks();
    const Uint32 deltaTicks = 1000/60;

    while(Application::_running)
    {
        /* Deal Events */
        while(SDL_PollEvent(&event) > 0)
        {
            this->deal(event);
        }

        /* Update */
        this->update();

        /* Paint the Widgets */
        this->paint();
        

        /* Release CPU */
        if(SDL_GetTicks() - ticks < deltaTicks)
        {
            SDL_Delay(deltaTicks - (SDL_GetTicks() - ticks));
        }
        ticks = SDL_GetTicks();
    }

    return 0;
}


/* Application deal Event */
bool Application::deal(const Event& event)
{
    /* Deal all SDL event */

    /* Pass Event to Workers */
    for(Worker* worker : Application::_workers)
    {
        if(worker->deal(event) == true)
        {
            return true;
        }
    }

    /* Pass Event to Widgets */
    for(Widget* widget : this->_widgets)
    {
        if(widget->deal(event) == true)
        {
            return true;
        }
    }


    /* Application mainloop exit */
    if(event.type == SDL_QUIT)
    {
        Application::_running = false;
    }

    return false;
}

/* Application paint */
void Application::paint()
{
    Renderer* renderer = Application::_renderer;
    if(renderer == nullptr)
    {
        SDL_Log("Renderer is nullptr");
        throw std::runtime_error("Renderer is nullptr");
    }

    /* Clear */
    renderer->setTarget(Texture::DefaultTarget);
    renderer->setColor(0xff, 0xff, 0xff);
    renderer->clear();

    /* Paint widgets */
    for(Widget* widget : this->_widgets)
    {
        if(widget->_visiable)
        {
            widget->paint(renderer);
        }
    }

    /* Present */
    renderer->setTarget(Texture::DefaultTarget);
    renderer->present();
}

/* Application update */
void Application::update()
{
    /* Update Workers */
    for(Worker* worker : Application::_workers)
    {
        worker->update();
    }

    /* Update Widgets */
    for(Widget* widget : this->_widgets)
    {
        widget->update();
    }
}



}; // namespace LovelyGUI