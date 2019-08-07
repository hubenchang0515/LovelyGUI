#include "Application.h"
#include "Widget.h"
#include <stdexcept>

using namespace LovelyGUI;

/* 频谱瀑布图 */
class Spectrogram : public Widget
{
public:
    Spectrogram(Widget* parent=nullptr) :
        Widget(parent)
    {
        this->_texture = SDL_CreateTexture(Application::renderer(), SDL_PIXELFORMAT_RGBA8888, 
                                            SDL_TEXTUREACCESS_TARGET, 640, 400);
        if(this->_texture == nullptr)
        {
            SDL_Log("%s", SDL_GetError());
            throw std::runtime_error("Spectrogram Error");
        }

        for(int i = 0; i < 640; i++)
        {
            lastData[i] = rand()%256;
        }
    }

    void push(int data[640])
    {
        SDL_Rect srcRect, dstRect;
        srcRect.x = 0;
        srcRect.y = 1;
        srcRect.w = 640;
        srcRect.h = 399;

        dstRect.x = 0;
        dstRect.y = 0;
        dstRect.w = 640;
        dstRect.h = 399;
        SDL_SetRenderTarget(Application::renderer(), this->_texture);
        SDL_RenderCopy(Application::renderer(), this->_texture, &srcRect, &dstRect);
        
        for(int i = 0; i < 640; i++)
        {
            SDL_SetRenderDrawColor(Application::renderer(), 0, 0, lastData[i], 0xff);
            SDL_RenderDrawPoint(Application::renderer(), i, 399);
        }
    }

protected:
    void paintEvent(SDL_Renderer* renderer) override
    {
        int symbol = 1;
        for(int i = 0; i < 640; i++)
        {
            if(lastData[i] > 200)
            {
                symbol = -1;
            }
            else if(lastData[i] < 100)
            {
                symbol = 1;
            }
            else if(rand() % 100 > 80)
            {
                symbol = symbol;
            }
            else
            {
                symbol = -symbol;
            }
            

            lastData[i] = lastData[i] + symbol * (rand() % 10);
            if(rand() % 100 > 90)
            {
                lastData[i] = (lastData[i] + symbol * 100 ) % 256;
            }
        }

        push(lastData);

        SDL_SetRenderTarget(renderer, nullptr);
        SDL_RenderCopy(renderer, this->_texture, nullptr, nullptr);
    }


private:
    SDL_Texture* _texture;
    int lastData[640];
};

int main(int argc, char* argv[])
{
    Application app;
    Spectrogram rootWidget;
    app.setRootWidget(&rootWidget);
    return app.exec();
}