#include "Alien.h"

Alien::Alien(double visualField, Personagem* target, double vel,int thresholdVision) throw(LoadImageException,NoVideoBufferException,NoTargetException) : Monstro(40,51,"resources/etSprites.png",visualField,target,vel,thresholdVision)
{

}

Alien::~Alien()
{
    //dtor
}


void Alien::changeFrame()
{

    if( this->getVDirector() == Monstro::VD_RIGHT && this->getCurrentI() != 3  )
    {
        this->setCurrentI(3);
        this->setCurrentJ(0);

    }
    else if( this->getVDirector() == Monstro::VD_LEFT && this->getCurrentI() != 2 )
    {

        this->setCurrentI(2);
        this->setCurrentJ(3);


    }
    else if( this->getVDirector() == Monstro::VD_UP && this->getCurrentI() != 1 )
    {
        this->setCurrentI(1);
        this->setCurrentJ(0);


    }
    else if( this->getVDirector() == Monstro::VD_DOWN && this->getCurrentI() != 0 )
    {
        this->setCurrentI(0);
        this->setCurrentJ(3);

    }
    else if( this->getVDirector() != Monstro::VD_STOP)
    {
        this->setCurrentJ(this->getCurrentJ() + 1);
    }
}
