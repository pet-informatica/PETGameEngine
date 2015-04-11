#ifndef SCREEN_H
#define SCREEN_H

#include "ComponentSet.h"
#include "VideoBufferException.h"
#include "VideoInitErrorException.h"
#include "ScreenException.h"
#include "Cronometro.h"
#include <string>
#include <cstdlib>
#include <time.h>


using std::string;

class Screen : public ComponentSet
{
    private:

        Cronometro timerFrameControl;
        Cronometro timerFrameCount;
        Uint32 maxFps;
        Uint32 frameCount;
        Uint32 lastFrameCount;
        bool lockFrameRate; //Flag que indica se o frame rate está sendo controlado
        string windowTitle;

    public:
        Screen(int width,int height,bool fullScreen,string windowTitle = string()) throw(ScreenException,VideoBufferException,VideoInitErrorException);
        virtual ~Screen();

        virtual void draw();
        virtual void update();

        Uint32 getMaxFps();
        void setMaxFps(int maxFps);

        void setlockFrameRate(bool lockFrameRate);
        bool getlockFrameRate();

        string getWindowTitle();
        void setWindowTitle(string windowTitle);

        Uint32 getLastFrameCount();

        Cronometro& getTimerFrameControl();

        Vetor2D getDimension();
    protected:

};

#endif // SCREEN_H
