#include "Surface.h"
#include "messageSender.h"
#include <sstream>

const SDL_Color Surface::defaultColorKey = {0,255,0};


Surface::Surface(string filename,Vetor2D offset,SDL_Color colorKey) throw(LoadImageException,NoVideoBufferException) //: VisualComponent(Surface::loadImage(filename.c_str(),colorKey),offset)
{

    if(!Surface::videoBuffer)
    {
        throw NoVideoBufferException();
    }

    SDL_Surface* surface = ResourceManager::loadImage(filename, Surface::videoBuffer,colorKey);

    if(!surface)
    {
        throw LoadImageException(filename.c_str());
    }

    this->setOffset(offset);
    this->setSurface(surface);



}

Surface::Surface() : VisualComponent(NULL,Vetor2D::ZERO)
{

}

Surface::Surface(Uint16 width,Uint16 height) throw(LoadImageException,NoVideoBufferException) //: VisualComponent(Surface::createSDLSurface(width,height),Vetor2D::ZERO)
{
    if(!Surface::videoBuffer)
    {
        throw NoVideoBufferException();
    }

    SDL_Surface* surface = ResourceManager::createSDLSurface(width, height, Surface::videoBuffer);

    if(!surface)
    {
        throw LoadImageException("Couldn't create a surface");
    }

    this->setSurface(surface);

}

Surface::~Surface()
{

}

