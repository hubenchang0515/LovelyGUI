#include "Application.h"
#include "Worker.h"
#include <SDL2/SDL.h>

namespace LovelyGUI
{

Worker::Worker(Object* parent) :
    Object(parent)
{

}

Worker::~Worker()
{
    SDL_Log("Worker::~Worker(%p)", this);

    Application::removeWorker(this);
}


}; // namespace LovelyGUI