#include "VisualComponent.h"


VisualComponent::VisualComponent()
{
    this->surface = NULL;
    this->texture = NULL;
}

VisualComponent::VisualComponent(SDL_Surface* surface,Vetor2D offset)
{
    this->offset = offset;
    this->surface = surface;

    this->texture = SDL_CreateTextureFromSurface(VisualComponent::render, this->surface);

}
VisualComponent::~VisualComponent()
{
    this->clear();
}

void VisualComponent::clear()
{
    SDL_FreeSurface(this->surface);
    SDL_DestroyTexture(this->texture);
    this->texture = NULL;
    this->surface = NULL;



}

SDL_Surface* VisualComponent::getSurface()
{
    return this->surface;
}

void VisualComponent::setSurface(SDL_Surface* surface)
{
    if(this->surface)
    {
        this->clear();
    }

    this->surface = surface;

    this->texture = SDL_CreateTextureFromSurface(VisualComponent::render, this->surface);

}
Vetor2D& VisualComponent::getOffset()
{
    return this->offset;
}

SDL_Rect VisualComponent::getRect()
{
    SDL_Rect rect;

    rect.x = (int) this->offset.getX();
    rect.y = (int) this->offset.getY();

    rect.w = this->surface->w;
    rect.h = this->surface->h;


    return rect;
}

void VisualComponent::setOffset(Vetor2D offset)
{
    this->offset = offset;
}

Vetor2D VisualComponent::getDimension()
{
    return Vetor2D(this->surface->w, this->surface->h);
}
