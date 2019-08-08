#include "Application.h"
#include "LinearLayout.h"
#include "Spectrogram.h"
#include "Timer.h"
#include <stdexcept>
#include <vector>

using namespace LovelyGUI;

void pushRandomValue(void *param)
{
    std::vector<Spectrogram*> spectrogram = *static_cast<std::vector<Spectrogram*>*>(param);
    std::vector<SDL_Color> line;
    line.resize(spectrogram[0]->width());
    for(int i =0; i < spectrogram[0]->width(); i++)
    {
        line[i].r = rand() % 256;
        line[i].g = rand() % 256;
        line[i].b = rand() % 256;
        line[i].a = 255;
    }
    spectrogram[0]->pushLine(line);

    line.resize(spectrogram[1]->width());
    for(int i =0; i < spectrogram[1]->width(); i++)
    {
        line[i].r = rand() % 256;
        line[i].g = rand() % 256;
        line[i].b = rand() % 256;
        line[i].a = 255;
    }
    spectrogram[1]->pushLine(line);
}


int main(int argc, char* argv[])
{
    Application app;
    LinearLayout* root = new LinearLayout(&app);
    root->setDirection(LinearLayout::Direction::Vertical);
    app.setRootWidget(root);

    LinearLayout* line1 = new LinearLayout(root);
    LinearLayout* line2 = new LinearLayout(root);
    root->addWidget(line1);
    root->addWidget(line2);


    Spectrogram* spec1 =  new Spectrogram(line1);
    Widget* widget1 = new Widget(line1);
    line1->addWidget(spec1);
    line1->addWidget(widget1,2);

    Spectrogram* spec2 =  new Spectrogram(line2);
    Widget* widget2 = new Widget(line2);
    line2->addWidget(widget2,2);
    line2->addWidget(spec2);
    line2->setProportion(1, 2);
    

    std::vector<Spectrogram*> specs;
    specs.push_back(spec1);
    specs.push_back(spec2);

    Timer* timer = new Timer(&app);
    timer->setCallback(pushRandomValue, static_cast<void*>(&specs));
    timer->setInterval(20);
    app.addWorker(timer);
    app.exec();
    return 0;
}