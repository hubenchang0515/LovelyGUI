#ifndef LOVELY_GUI_FONT
#define LOVELY_GUI_FONT

#include "Object.h"
#include <string>

namespace LovelyGUI
{

class Font : public Object
{
public:
    Font(Object* parent=nullptr);
    Font(const Font* font, Object* parent=nullptr);
    Font(const Font&) = delete;
    Font(const Font&&) = delete;
    ~Font();
    bool open(const std::string& file, int size=0);
    void close();
    Surface* render(const std::string& text, Color fg, Color bg);
    bool setFile(const std::string& file);
    bool setSize(int size);

private:
    std::string _file;
    int _size;
    TTF_Font* _font;

};

}; // namespace LovelyGUI

#endif