#ifndef ALIEN_H
#define ALIEN_H

#include "Monstro.h"


class Alien : public Monstro
{
    public:
        Alien(double visualField, Personagem* target, double vel,int thresholdVision) throw(LoadImageException,NoVideoBufferException,NoTargetException);
        virtual ~Alien();


        void changeFrame();
    protected:
    private:
};

#endif // ALIEN_H
