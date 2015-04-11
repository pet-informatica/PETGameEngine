#include "screen.h"
#include "messageSender.h"
#include <sstream>




Screen::Screen(int width, int height, bool fullScreen,string windowTitle) throw(ScreenException,VideoBufferException,VideoInitErrorException)
{

    //Caso o subsistema de vídeo não tenha sido iniciado antes, tenta-se iniciá-lo
    if(!SDL_WasInit(SDL_INIT_VIDEO|SDL_INIT_EVENTS|SDL_INIT_TIMER))
    {

        if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS|SDL_INIT_TIMER) < 0 )
        {
            throw VideoInitErrorException();
        }
    }

    this->windowTitle = windowTitle;

/*
    const SDL_VideoInfo* vinfo = SDL_GetVideoInfo();

    int bpp = vinfo->vfmt->BitsPerPixel;

    bool hw_ok = vinfo->hw_available;

    Uint32 flags = 0;

    if(hw_ok)
    {
        flags = SDL_HWSURFACE;
    }
    else
    {
        flags = SDL_SWSURFACE;
    }

    if(fullScreen)
    {
        flags |= SDL_FULLSCREEN;
    }
*/
    if(Screen::videoBuffer != NULL)
    {
        throw ScreenException();
    }
    else
    {
        printf("Init Screen\n");

        if(windowTitle.size()!=0)
        {
            Screen::screen = SDL_CreateWindow(this->windowTitle.c_str(), 0, 0, width, height, SDL_WINDOW_SHOWN);
            if (!Screen::screen)
                throw VideoBufferException();


            printf("Screen ok\n");
        }

        
        printf("Init Render\n");
        Screen::render = SDL_CreateRenderer(Screen::screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if(!Screen::render)
        {

            throw VideoBufferException();

        }
        printf("Render ok\n");

        // if all this hex scares you, check out SDL_PixelFormatEnumToMasks()!
        Screen::videoBuffer = SDL_CreateRGBSurface(0, width, height, 32,
                                        0x00FF0000,
                                        0x0000FF00,
                                        0x000000FF,
                                        0xFF000000);
        Screen::sdlTexture = SDL_CreateTexture(Screen::render,
                                            SDL_PIXELFORMAT_ARGB8888,
                                            SDL_TEXTUREACCESS_STREAMING,
                                            width, height);
        Screen::sdlTexture2 = SDL_CreateTexture(Screen::render,
                                            SDL_PIXELFORMAT_ARGB8888,
                                            SDL_TEXTUREACCESS_TARGET,
                                            width, height);

        if(!Screen::videoBuffer || !Screen::sdlTexture)
        {

            throw VideoBufferException();
        }
        printf("videoBuffer and sdlTexture ok\n");

        

    }

    //this->timerFrameCount = Cronometro();
    //this->timerFrameControl = Cronometro();

    this->timerFrameCount.start();
    this->timerFrameControl.start();


    this->lockFrameRate = true;
    this->maxFps = 30;
    this->frameCount = 0;
    this->lastFrameCount = 0;


    //Seed to generate aleatory numbers, used for someone who needs it
    srand(time(NULL));

    //SDL_SetRelativeMouseMode(SDL_TRUE);
}

Screen::~Screen()
{
    this->components.clear();
    SDL_DestroyRenderer(this->render);
    SDL_Quit();
}

void Screen::draw()
{
    ComponentSet::draw();

    this->frameCount++;

    //Milisegundos por frame
    Uint32 mSecondsPerFrame = ONE_SECOND/this->maxFps;

    if(this->lockFrameRate)
    {
        if(this->timerFrameControl.getTicks() < mSecondsPerFrame)
        {
            SDL_Delay(mSecondsPerFrame - this->timerFrameControl.getTicks());
        }

        this->timerFrameControl.stop();
        this->timerFrameControl.start();

    }

    if(this->timerFrameCount.getTicks() >= 1000)
    {
        lastFrameCount = frameCount;
        frameCount = 0;

        timerFrameCount.stop();
        timerFrameCount.start();


    }






}

void Screen::update()
{
    ComponentSet::update();


}

Uint32 Screen::getMaxFps()
{
    return this->maxFps;
}

void Screen::setMaxFps(int maxFps)
{
    this->maxFps = maxFps;
}

Uint32 Screen::getLastFrameCount()
{
    return this->lastFrameCount;
}

void Screen::setlockFrameRate(bool lockFrameRate)
{
    this->lockFrameRate = lockFrameRate;
}

bool Screen::getlockFrameRate()
{
    return this->lockFrameRate;
}

Cronometro& Screen::getTimerFrameControl()
{
    return this->timerFrameControl;
}

string Screen::getWindowTitle()
{
    return this->windowTitle;
}

void Screen::setWindowTitle(string windowTitle)
{
    this->windowTitle = windowTitle;

    SDL_SetWindowTitle(Screen::screen, this->windowTitle.c_str());
    //SDL_WM_SetCaption(this->windowTitle.c_str(),NULL);
}

Vetor2D Screen::getDimension()
{
    return Vetor2D(Screen::videoBuffer->w, Screen::videoBuffer->h);
}
