#ifndef LIGHTSURFACE_H
#define LIGHTSURFACE_H

#include "Surface.h"

class LightSurface : public Surface
{
    protected:

        LightSurface();

    private:

        SDL_Rect clip;

    public:
        LightSurface(string filename,Vetor2D offset = Vetor2D::ZERO,SDL_Color colorKey = LightSurface::defaultColorKey) throw(LoadImageException,NoVideoBufferException);
        LightSurface(Uint16 width,Uint16 height) throw(LoadImageException,NoVideoBufferException);
        virtual ~LightSurface();

        virtual void draw();
        virtual void update();


        SDL_Rect getClip();
        void setClip(SDL_Rect clip);

        void setSurface(SDL_Surface* surface);
};

#endif // LIGHTSURFACE_H
