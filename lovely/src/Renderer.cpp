#include "Renderer.h"
#include <stdexcept>

namespace LovelyGUI
{

Renderer::Renderer(Window* window) :
    Object(window)
{
    SDL_Window* sdlWindow = window->window();

    /* Create Renderer */
    this->_renderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
    if(this->_renderer == nullptr)
    {
        this->_renderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_SOFTWARE);
        if(this->_renderer == nullptr)
        {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_CreateRenderer : %s", SDL_GetError());
            throw std::runtime_error("SDL_CreateRenderer Error");
        }
    }

    /* Create mutex */
    this->_mutex = SDL_CreateMutex();
    if(this->_mutex == nullptr)
    {
        SDL_DestroyRenderer(this->_renderer);
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_CreateMutex : %s", SDL_GetError());
        throw std::runtime_error("SDL_CreateMutex Error");
    }
}

Renderer::~Renderer()
{
    SDL_Log("Renderer::~Renderer(%p)", this);

    if(this->_mutex != nullptr)
    {
        SDL_UnlockMutex(this->_mutex);
    }
    SDL_DestroyMutex(this->_mutex);
    SDL_DestroyRenderer(this->_renderer);
}


int Renderer::lock()
{
    return SDL_LockMutex(this->_mutex);
}


int Renderer::unlock()
{
    return SDL_UnlockMutex(this->_mutex);
}


int Renderer::tryLock()
{
    return SDL_TryLockMutex(this->_mutex);
}


Texture Renderer::createTexture(Uint32 width, Uint32 height)
{
    return SDL_CreateTexture(this->_renderer, SDL_PIXELFORMAT_RGBA8888, 
                                SDL_TEXTUREACCESS_TARGET, width, height);
}


Texture Renderer::createTextureFromSurface(Surface* surface)
{
    return SDL_CreateTextureFromSurface(this->_renderer, surface);
}


void Renderer::destroyTexture(const Texture& texture)
{
    SDL_DestroyTexture(texture);
}


int Renderer::setTarget(const Texture& texture)
{
    return SDL_SetRenderTarget(this->_renderer, texture);
}


int Renderer::setBlendMode(BlendMode mode)
{
    return SDL_SetRenderDrawBlendMode(this->_renderer, static_cast<SDL_BlendMode>(mode));
}


int Renderer::setColor(Uint8 r, Uint8 g, Uint8 b)
{
    return SDL_SetRenderDrawColor(this->_renderer, r, g, b, 0);
}


int Renderer::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    return SDL_SetRenderDrawColor(this->_renderer, r, g, b, a);
}


int Renderer::setColor(const Color& color)
{
    return SDL_SetRenderDrawColor(this->_renderer, color.r, color.g, color.b, color.a);
}


int Renderer::clear()
{
    return SDL_RenderClear(this->_renderer);
}


void Renderer::present()
{
    SDL_RenderPresent(this->_renderer);
}


int Renderer::drawPoint(int x, int y)
{
    return SDL_RenderDrawPoint(this->_renderer, x, y);
}


int Renderer::drawPoint(const Point& point)
{
    return SDL_RenderDrawPoint(this->_renderer, point.x, point.y);
}


int Renderer::drawPoints(const std::vector<Point>& points)
{
    return SDL_RenderDrawPoints(this->_renderer, points.data(), points.size());
}


int Renderer::drawLine(int x1, int y1, int x2, int y2)
{
    return SDL_RenderDrawLine(this->_renderer, x1, y1, x2, y2);
}


int Renderer::drawLine(const Point& point1, const Point& point2)
{
    return SDL_RenderDrawLine(this->_renderer, point1.x, point1.y, point2.x, point2.y);
}


int Renderer::drawLines(const std::vector<Point>& points)
{
    return SDL_RenderDrawLines(this->_renderer, points.data(), points.size());
}


int Renderer::drawRect(const Rect& rect)
{
    return SDL_RenderDrawRect(this->_renderer, &rect);
}

int Renderer::drawRects(const std::vector<Rect>& rects)
{
    return SDL_RenderDrawRects(this->_renderer, rects.data(), rects.size());
}

int Renderer::fillRect(const Rect& rect)
{
    return SDL_RenderFillRect(this->_renderer, &rect);
}

int Renderer::fillRects(const std::vector<Rect>& rects)
{
    return SDL_RenderFillRects(this->_renderer, rects.data(), rects.size());
}

int Renderer::copy(const Texture& source, const Rect* srcRect, const Rect* dstRect)
{
    return SDL_RenderCopy(this->_renderer, source, srcRect, dstRect);
}

}; // namespace LovelyGUI