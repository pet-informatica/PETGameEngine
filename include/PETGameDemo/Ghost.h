#ifndef GHOST_H
#define GHOST_H

#include "Monstro.h"


class Ghost : public Monstro
{
    public:
        Ghost(double visualField, Personagem* target, double vel,int thresholdVision) throw(LoadImageException,NoVideoBufferException,NoTargetException);
        virtual ~Ghost();


        void changeFrame();
    protected:
    private:
};

#endif // GHOST_H
