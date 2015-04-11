#include "Sprite.h"

Sprite::Sprite(Uint16 spriteWidth, Uint16 spriteHeight, string spriteSrc) throw(LoadImageException,NoVideoBufferException)
{
    this->spriteWidth = spriteWidth;
    this->spriteHeight = spriteHeight;

    if(!Surface::videoBuffer)
    {
        throw NoVideoBufferException();
    }

    SDL_Surface* spriteSheet = ResourceManager::loadImage(spriteSrc, Sprite::videoBuffer, ResourceManager::defaultColorKey);

    if(!spriteSheet)
    {
        throw LoadImageException(spriteSrc.c_str());
    }

    this->setSurface(spriteSheet);

    this->maxFrameI = spriteSheet->h/spriteHeight;
    this->maxFrameJ = spriteSheet->w/spriteWidth;

    this->frame = new SDL_Rect*[this->maxFrameI];

    for(int i=0; i<this->maxFrameI; i++)
    {
        this->frame[i] = new SDL_Rect[this->maxFrameJ];
    }

    for(int i=0; i<this->maxFrameI; i++)
    {
        for(int j=0; j<this->maxFrameJ; j++)
        {
            this->frame[i][j].x = j*spriteWidth;
            this->frame[i][j].y = i*spriteHeight;

            this->frame[i][j].w = spriteWidth;
            this->frame[i][j].h = spriteHeight;
        }

    }

    this->currentI = 0;
    this->currentJ = 0;

}

Sprite::~Sprite()
{
    for(int i=0; i<this->maxFrameI; i++)
    {
        delete [] this->frame[i];
    }
    delete [] this->frame;

    

}

void Sprite::setCurrentI(Uint16 currentI)
{
    this->currentI = currentI%this->maxFrameI;

    if( currentI < 0 && this->currentI!=0 )
    {
        this->currentI += this->maxFrameI;
    }
}

void Sprite::setCurrentJ(Uint16 currentJ)
{
    this->currentJ = currentJ%this->maxFrameJ;

    if( currentJ < 0 && this->currentJ!=0 )
    {
        this->currentJ += this->maxFrameJ;
    }
}

Uint16 Sprite::getCurrentI()
{
    return this->currentI;
}

Uint16 Sprite::getCurrentJ()
{
    return this->currentJ;
}


void Sprite::draw()
{
    SDL_Rect offset = this->getRect();

    if(Surface::videoBuffer!= NULL && this->getSurface() != NULL)
    {
        SDL_BlitSurface(this->getSurface(),&this->frame[this->currentI][this->currentJ],Surface::videoBuffer,&offset);
    }

    SDL_SetRenderTarget(Sprite::render, Sprite::sdlTexture2);
    SDL_RenderCopy(Sprite::render, this->texture, &this->frame[this->currentI][this->currentJ], &offset);
    SDL_SetRenderTarget(Sprite::render, NULL);


}

void Sprite::update()
{

}

Vetor2D Sprite::getDimension()
{

    return Vetor2D(this->spriteWidth, this->spriteHeight );
}
