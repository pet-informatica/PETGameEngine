#include "Monstro.h"

const int Monstro::SEEK = 0;
const int Monstro::PURSUIT = 1;
const int Monstro::CATCH = 2;

const Vetor2D Monstro::VD_UP = Vetor2D(0, -1);
const Vetor2D Monstro::VD_DOWN = Vetor2D(0, 1);
const Vetor2D Monstro::VD_RIGHT = Vetor2D(1, 0);
const Vetor2D Monstro::VD_LEFT = Vetor2D(-1, 0);
const Vetor2D Monstro::VD_STOP = Vetor2D::ZERO;

// 200 ms
const int Monstro::RESPONSE_TIME_SEEK = 1000;
const int Monstro::RESPONSE_TIME_UNIVERSAL = 200;


Monstro::Monstro(Uint16 spriteWidth, Uint16 spriteHeight, string spriteSrc, double visualField, Personagem* target, double vel,int thresholdVision) throw(LoadImageException,NoVideoBufferException,NoTargetException) : Sprite(spriteWidth, spriteHeight, spriteSrc)
{
    this->vdirector = Monstro::VD_RIGHT;
    //this->foundTarget = false;


    this->target = target;
    this->vel = vel;
    this->thresholdVision = thresholdVision;
    this->visualField = visualField;

    if(!this->target) throw NoTargetException();


    this->delay_seek.start();
    this->delay_universal.start();

    this->state = Monstro::SEEK;

    this->vdirector = Monstro::VD_RIGHT;

    srand(time(NULL));
}

Monstro::~Monstro()
{

}

void Monstro::setVDirector(Vetor2D vdirector)
{
    this->vdirector = vdirector;
}

Vetor2D& Monstro::getVDirector()
{
    return this->vdirector;
}

void Monstro::setVisualField(double visualField)
{
    this->visualField = visualField;
}
double Monstro::getVisualField()
{
    return this->visualField;
}
void Monstro::setVel(double vel)
{
    this->vel = vel;
}
double Monstro::getVel()
{
    return this->vel;
}

void Monstro::move()
{
    this->setOffset(this->getOffset() + this->vdirector*vel);
}

void Monstro::setThresholdVision(int thresholdVision)
{
    this->thresholdVision = thresholdVision;
}

int Monstro::getThresholdVision()
{
    return this->thresholdVision;
}

bool Monstro::targetIsVisible()
{
    Vetor2D v = this->getOffset() - target->getOffset();

    bool visible = (abs(v.angleBetween(this->vdirector)) <= visualField && v.getNorma() <= this->thresholdVision);

    return visible;
}

int Monstro::chooseDirection()
{
    return rand()%4;
}

void Monstro::update()
{
    this->actuate();
}

void Monstro::seek()
{
    if( this->targetIsVisible() )
    {
        this->state = Monstro::PURSUIT;
        this->setVel(this->getVel()*2);
    }

    int directionChoosen = this->chooseDirection();

    if( directionChoosen == 0 )
    {
        this->vdirector = Monstro::VD_RIGHT;
    }
    else if( directionChoosen == 1 )
    {
        this->vdirector = Monstro::VD_LEFT;
    }
    else if( directionChoosen == 2)
    {
        this->vdirector = Monstro::VD_DOWN;
    }
    else if( directionChoosen == 3 )
    {
        this->vdirector = Monstro::VD_UP;
    }

}

void Monstro::pursuit()
{
    if( !this->targetIsVisible() )
    {
        this->state = Monstro::SEEK;
        this->delay_seek.stop();
        this->delay_seek.start();

        this->setVel(this->getVel()/2);

    }
    else
    {
        double dx = ( target->getOffset().getX() - this->getOffset().getX() );
        double dy = ( target->getOffset().getY() - this->getOffset().getY() );

        if( abs(dx) > abs(dy) )
        {
            if( dx > 0 ) this->vdirector = Monstro::VD_RIGHT;
            else if( dx < 0 ) this->vdirector = Monstro::VD_LEFT;
        }
        else if( abs(dy) > abs(dx) )
        {
            if( dy > 0 ) this->vdirector = Monstro::VD_DOWN;
            else if( dy < 0 ) this->vdirector = Monstro::VD_UP;
        }

        if( Vetor2D(dx,dy).getNorma() <= this->getDimension().getNorma()/2)
        {
            this->vdirector = Monstro::VD_STOP;
            this->target->setWasCaught(true);
        }
    }


}

void Monstro::actuate()
{
    if( this->delay_universal.getTicks() >= Monstro::RESPONSE_TIME_UNIVERSAL)
    {
        if( this->state == Monstro::SEEK )
        {
            if( this->delay_seek.getTicks() >= Monstro::RESPONSE_TIME_SEEK )
            {
                this->seek();

                delay_seek.stop();
                delay_seek.start();
            }

            this->changeFrame();
            this->move();

        }
        else if( this->state == Monstro::PURSUIT )
        {
            this->pursuit();

            this->changeFrame();
            this->move();
        }

        delay_universal.stop();
        delay_universal.start();

    }

}





