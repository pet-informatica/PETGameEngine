#include "Zombie.h"

Zombie::Zombie(double visualField, Personagem* target, double vel,int thresholdVision) throw(LoadImageException,NoVideoBufferException,NoTargetException) : Monstro(64,64,"resources/ZombieJim.png",visualField,target,vel,thresholdVision)
{
    this->state == SEEK;
    this->setVel( this->getVel()/2);
}

Zombie::~Zombie()
{
    //dtor
}


void Zombie::changeFrame()
{

    if( this->getVDirector() == Monstro::VD_RIGHT && this->getCurrentI() != 3  )
    {
        this->setCurrentI(3);
        this->setCurrentJ(1);

    }
    else if( this->getVDirector() == Monstro::VD_LEFT && this->getCurrentI() != 2 )
    {

        this->setCurrentI(2);
        this->setCurrentJ(1);


    }
    else if( this->getVDirector() == Monstro::VD_UP && this->getCurrentI() != 0 )
    {
        this->setCurrentI(0);
        this->setCurrentJ(1);


    }
    else if( this->getVDirector() == Monstro::VD_DOWN && this->getCurrentI() != 1 )
    {
        this->setCurrentI(1);
        this->setCurrentJ(1);

    }
    else if( this->getVDirector() != Monstro::VD_STOP)
    {
        this->setCurrentJ(this->getCurrentJ() + 1);
    }
}
