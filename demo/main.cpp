#include "Application.h"
#include "Spectrogram.h"
#include "Timer.h"
#include <stdexcept>
#include <vector>

using namespace LovelyGUI;

void pushRandomValue(void *param)
{
    Spectrogram* spectrogram = static_cast<Spectrogram*>(param);
    std::vector<SDL_Color> line;
    line.resize(spectrogram->width());
    for(int i =0; i < spectrogram->width(); i++)
    {
        line[i].r = rand() % 256;
        line[i].g = rand() % 256;
        line[i].b = rand() % 256;
    }
    spectrogram->pushLine(line);
}

int main(int argc, char* argv[])
{
    Application app;
    Spectrogram* rootWidget = new Spectrogram(&app);
    app.setRootWidget(rootWidget);
    Timer* timer = new Timer(&app);
    timer->setCallback(pushRandomValue, static_cast<void*>(rootWidget));
    timer->setInterval(20);
    app.addWorker(timer);
    app.exec();
    return 0;
}