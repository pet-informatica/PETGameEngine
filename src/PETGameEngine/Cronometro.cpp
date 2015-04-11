#include "cronometro.h"

Cronometro::Cronometro()
{
    this->stop();
}

Cronometro::~Cronometro()
{
    //dtor
}

void Cronometro::start()
{
    if(!this->started)
    {
        this->paused = false;
        this->started = true;

        this->startTicks = SDL_GetTicks();
    }
}

void Cronometro::stop()
{
    this->paused = false;
    this->started = false;
    this->pausedTicks = 0;
    this->startTicks = 0;
}

void Cronometro::pause()
{
    if(!this->paused)
    {
        this->pausedTicks = SDL_GetTicks() - this->startTicks;

        this->paused = true;
    }
}

void Cronometro::unpause()
{
    if(this->paused)
    {
        this->startTicks = SDL_GetTicks() - this->pausedTicks;

        this->paused = false;
    }
}

bool Cronometro::isStarted()
{
    return this->started;
}

bool Cronometro::isPaused()
{
    return this->paused;
}

Uint32 Cronometro::getTicks()
{
    if(this->started)
    {
        if(!this->paused)
        {
            return SDL_GetTicks() - this->startTicks;
        }
        else if(this->paused)
        {
            return this->pausedTicks;
        }

    }
    else
    {
        return 0;
    }
}
