#include "Application.h"
#include "LinearLayout.h"
#include "Spectrogram.h"
#include "Timer.h"
#include "Label.h"
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

    app.setDefaultFont("SourceHanSansCN-Normal.otf");
    LinearLayout* root = new LinearLayout(&app);
    root->setDirection(LinearLayout::Direction::Vertical);
    app.setRootWidget(root);

    LinearLayout* line1 = new LinearLayout(root);
    LinearLayout* line2 = new LinearLayout(root);
    root->addWidget(line1);
    root->addWidget(line2);


    Spectrogram* spec1 =  new Spectrogram(line1);
    Label* label1 = new Label(line1);
    label1->setText(u8"傻gay晨");
    label1->setFrontColor(Color({0, 0xff, 0, 0xff}));
    label1->setBackColor(0xff, 0, 0);
    line1->addWidget(spec1);
    line1->addWidget(label1,2);

    Spectrogram* spec2 =  new Spectrogram(line2);
    Label* label2 = new Label(line2);
    label2->setText(u8"薯条一点也不萌");
    line2->addWidget(label2,2);
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