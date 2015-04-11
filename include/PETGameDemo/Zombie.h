#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Monstro.h"

class Zombie : public Monstro
{
    public:
        Zombie(double visualField, Personagem* target, double vel,int thresholdVision) throw(LoadImageException,NoVideoBufferException,NoTargetException);
        virtual ~Zombie();


        void changeFrame();

    protected:
    private:
};

#endif // ZOMBIE_H
