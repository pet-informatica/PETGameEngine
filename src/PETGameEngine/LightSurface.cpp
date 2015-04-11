#include "LightSurface.h"

LightSurface::LightSurface(string filename,Vetor2D offset,SDL_Color colorKey) throw(LoadImageException,NoVideoBufferException) : Surface(filename,offset,colorKey)
{
    this->clip.x = 0;
    this->clip.y = 0;
    this->clip.w = this->getSurface()->w;
    this->clip.h = this->getSurface()->h;
}

LightSurface::LightSurface() : Surface()
{
    this->clip.x = 0;
    this->clip.y = 0;
    this->clip.w = 0;//this->getSurface()->w;
    this->clip.h = 0;//this->getSurface()->h;

}

LightSurface::LightSurface(Uint16 width,Uint16 height) throw(LoadImageException,NoVideoBufferException) : Surface(width,height)
{
    this->clip.x = 0;
    this->clip.y = 0;
    this->clip.w = this->getSurface()->w;
    this->clip.h = this->getSurface()->h;

}

LightSurface::~LightSurface()
{
    //dtor
}

void LightSurface::draw()
{
    SDL_Rect offset = this->getRect();

    if(Surface::videoBuffer!= NULL && this->getSurface() != NULL)
    {
        SDL_BlitSurface(this->getSurface(),&this->clip,Surface::videoBuffer,&offset);
    }

    SDL_SetRenderTarget(LightSurface::render, LightSurface::sdlTexture2);
    SDL_RenderCopy(LightSurface::render, this->texture, &this->clip, &offset);
    SDL_SetRenderTarget(LightSurface::render, NULL);


}

void LightSurface::update()
{

}

SDL_Rect LightSurface::getClip()
{
    return this->clip;
}

void LightSurface::setClip(SDL_Rect clip)
{
    this->clip = clip;
}

void LightSurface::setSurface(SDL_Surface* surface)
{
    VisualComponent::setSurface(surface);

    this->clip.x = 0;
    this->clip.y = 0;
    this->clip.w = this->getSurface()->w;
    this->clip.h = this->getSurface()->h;
}
