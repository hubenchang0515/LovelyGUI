#include "Application.h"
#include "Widget.h"

using namespace LovelyGUI;

int main(int argc, char* argv[])
{
    Application app;
    Widget widget;
    app.setRootWidget(&widget);
    return app.exec();
}