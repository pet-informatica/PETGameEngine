#ifndef SPRITE_H
#define SPRITE_H

#include "Surface.h"


class Sprite : public Surface
{
    private:

        SDL_Rect** frame;
        //Dimensions of the sprite sheet
        Uint16 maxFrameJ, maxFrameI;
        Uint16 currentJ, currentI;

        Uint16 spriteWidth, spriteHeight;

    public:

        Sprite(Uint16 spriteWidth, Uint16 spriteHeight, string spriteSrc) throw(LoadImageException,NoVideoBufferException);
        virtual ~Sprite();


        virtual void draw();
        virtual void update();

        void setCurrentI(Uint16 currentI);
        void setCurrentJ(Uint16 currentJ);

        Uint16 getCurrentI();
        Uint16 getCurrentJ();

        SDL_Rect getSpriteRect()
        {
           SDL_Rect rect;
           rect.x = this->offset.getX();
           rect.y = this->offset.getY();
           rect.w = spriteWidth;
           rect.h = spriteHeight;

           return rect;

        }

        virtual Vetor2D getDimension();
};

#endif // SPRITE_H
