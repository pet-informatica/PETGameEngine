#include "Ghost.h"

Ghost::Ghost(double visualField, Personagem* target, double vel,int thresholdVision) throw(LoadImageException,NoVideoBufferException,NoTargetException) : Monstro(52,54,"resources/ghostgreen.png",visualField,target,vel,thresholdVision)
{
    //ctor
}

Ghost::~Ghost()
{
    //dtor
}

void Ghost::changeFrame()
{

    if( this->getVDirector() == Monstro::VD_RIGHT && this->getCurrentI() != 0  )
    {
        this->setCurrentI(1);
        this->setCurrentJ(0);

    }
    else if( this->getVDirector() == Monstro::VD_LEFT && this->getCurrentI() != 1 )
    {

        this->setCurrentI(1);
        this->setCurrentJ(0);


    }
    else if( this->getVDirector() != Monstro::VD_STOP)
    {
        this->setCurrentJ(this->getCurrentJ() + 1);
    }

}
