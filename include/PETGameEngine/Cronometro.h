#ifndef CRONOMETRO_H
#define CRONOMETRO_H

#include <SDL2/SDL.h>

const Uint32 ONE_SECOND = 1000; //One second is equals to 1000 milliseconds


class Cronometro
{
    private:

        bool paused;
        bool started;
        Uint32 pausedTicks;
        Uint32 startTicks;


    public:
        Cronometro();
        virtual ~Cronometro();

        void start();
        void stop();
        void pause();
        void unpause();

        bool isStarted();
        bool isPaused();

        Uint32 getTicks();
};

#endif // CRONOMETRO_H
