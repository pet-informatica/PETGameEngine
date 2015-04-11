#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include "Sprite.h"


class Personagem : public Sprite
{
    protected:
    private:

        string name;
        bool wasCaught;
        int points;

    public:
        Personagem(string name, Uint16 spriteWidth, Uint16 spriteHeight, string spriteSrc) throw(LoadImageException,NoVideoBufferException);
        virtual ~Personagem();


        virtual void handleEvent(SDL_Event &event) = 0;

        void setPoints(int points);
        int getPoints();

        void setWasCaught(bool wasCaught);
        bool getWasCaught();

        void setName(string name);
        string getName();

};

#endif // PERSONAGEM_H
