#include "Application.h"
#include "Widget.h"

using namespace LovelyGUI;

int main(int argc, char* argv[])
{
    Application app;
    Widget rootWidget;
    app.setRootWidget(&rootWidget);
    Widget* wid1 = new Widget(&rootWidget);
    Widget* wid2 = new Widget(&rootWidget);
    wid2->setX(200);
    return app.exec();
}