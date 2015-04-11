#ifndef SURFACE_H
#define SURFACE_H

#include "VisualComponent.h"
#include "LoadImageException.h"
#include "NoVideoBufferException.h"
#include "ResourceManager.h"
#include <string>

using std::string;


class Surface : public VisualComponent
{
    protected:

        Surface();

        public:

        static const SDL_Color defaultColorKey;

        Surface(string filename,Vetor2D offset,SDL_Color colorKey) throw(LoadImageException,NoVideoBufferException);
        Surface(Uint16 width,Uint16 height) throw(LoadImageException,NoVideoBufferException);

        ~Surface();

};

#endif // LIGHTSURFACE_H
