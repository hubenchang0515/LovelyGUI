#ifndef LOVELY_GUI_WORKER
#define LOVELY_GUI_WORKER

#include "Object.h"

#if __cplusplus > 201703L
    #include <any>
#endif

namespace LovelyGUI
{

class Worker : public Object
{
public:
    Worker(Object* parent=nullptr);
    virtual ~Worker();
    virtual void update() = 0;


};

}; // namespace LovelyGUI
#endif