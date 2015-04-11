#include "ResourceManager.h"

const SDL_Color ResourceManager::defaultColorKey = {0, 255, 0 };

ResourceManager::ResourceManager()
{
    //ctor
}

ResourceManager::~ResourceManager()
{
    //dtor
}

SDL_Surface* ResourceManager::loadImage(string filename, SDL_Surface* videoBuffer, SDL_Color colorKey)
{
    SDL_Surface* loadedImage = IMG_Load(filename.c_str());

    SDL_Surface* optimizedImage = NULL;

    if( loadedImage )
    {
        SDL_SetColorKey(loadedImage,SDL_TRUE,SDL_MapRGB(loadedImage->format,colorKey.r,colorKey.g,colorKey.b));

        optimizedImage = SDL_ConvertSurface(loadedImage, videoBuffer->format, NULL); //SDL_SetSurfaceAlphaMod(loadedImage);//SDL_DisplayFormatAlpha(loadedImage);

        SDL_FreeSurface(loadedImage);

        loadedImage = NULL;

    }




    return optimizedImage;

}

SDL_Surface* ResourceManager::createSDLSurface(Uint16 width, Uint16 height, SDL_Surface* videoBuffer)
{
    SDL_Surface* newSDLSurface = NULL;

    if(videoBuffer)
    {

        int depth = videoBuffer->format->BitsPerPixel;
        Uint32 flags = videoBuffer->flags;
        Uint32 Rmask = videoBuffer->format->Rmask;
        Uint32 Gmask = videoBuffer->format->Gmask;
        Uint32 Bmask = videoBuffer->format->Bmask;
        Uint32 Amask = videoBuffer->format->Amask;


        newSDLSurface = SDL_CreateRGBSurface(flags,width,height,depth,Rmask,Gmask,Bmask,Amask);
    }

    return newSDLSurface;
}
