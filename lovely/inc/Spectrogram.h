#ifndef LOVELY_GUI_SPECTROGRAM
#define LOVELY_GUI_SPECTROGRAM


#include "Application.h"
#include "Widget.h"

namespace LovelyGUI
{

/* Waterfall Image */
class Spectrogram : public Widget
{
public:
    Spectrogram(Object* parent=nullptr);
    virtual ~Spectrogram();

    virtual void setWidth(int width) override;
    virtual void setHeight(int height) override;

    virtual void pushLine(const std::vector<SDL_Color>& line);

protected:
    virtual void paintEvent(Renderer* renderer) override;

private:
    SDL_Texture* _texture;
    void adjustTexture();
};

}; // namespace LovelyGUI

#endif