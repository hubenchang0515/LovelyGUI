#ifndef LOVELY_GUI_LABEL
#define LOVELY_GUI_LABEL

#include "Widget.h"
#include "Font.h"
#include "Texture.h"
#include <string>

namespace LovelyGUI
{

class Label : public Widget
{
public:
    Label(Object* parent=nullptr);
    ~Label();
    bool setText(const std::string& text);
    bool setFont(const std::string& file, int size=0);
    bool setFontSize(int size);

    virtual void paintEvent(Renderer* renderer) override;
    virtual bool dealEvent(const Event& event) override;

private:
    std::string _text;
    Font* _font;
    Texture _texture;

    bool render();
};

}; // namespace LovelyGUI

#endif