#ifndef LOVELY_GUI_RENDERER
#define LOVELY_GUI_RENDERER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <vector>

#include "Window.h"
#include "Object.h"
#include "Texture.h"

namespace LovelyGUI
{

enum class BlendMode
{
    None = SDL_BLENDMODE_NONE,
    Blend = SDL_BLENDMODE_BLEND,
    Add = SDL_BLENDMODE_ADD,
    Mod = SDL_BLENDMODE_MOD,
};

class Renderer : public Object
{
public:
    Renderer(Window* _window);
    ~Renderer();

    /* Thread Sync */
    int lock();
    int unlock();
    int tryLock();

    /* Texture */
    Texture createTexture(Uint32 width, Uint32 height);
    Texture createTextureFromSurface(Surface* surface);
    void destroyTexture(const Texture& texture);

    /* Setting */
    int setTarget(const Texture& texture=Texture::DefaultTarget);
    int setBlendMode(BlendMode mode=BlendMode::None);
    int setColor(Uint8 r, Uint8 g, Uint8 b);
    int setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    int setColor(const Color& color);

    /* Draw */
    int clear();
    void present();
    int drawPoint(int x, int y);
    int drawPoint(const Point& point);
    int drawPoints(const std::vector<Point>& points);
    int drawLine(int x1, int y1, int x2, int y2);
    int drawLine(const Point& point1, const Point& point2);
    int drawLines(const std::vector<Point>& points);
    int drawRect(const Rect& rect);
    int drawRects(const std::vector<Rect>& rects);
    int fillRect(const Rect& rect);
    int fillRects(const std::vector<Rect>& rects);
    int copy(const Texture& source, const Rect* srcRect, const Rect* dstRect);

private:
    SDL_Renderer* _renderer;
    SDL_mutex* _mutex;
};

}; // namespace LovelyGUI

#endif