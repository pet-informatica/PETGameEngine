#include "Mariama.h"

const Vetor2D Mariama::VD_UP = Vetor2D(0, -1);
const Vetor2D Mariama::VD_DOWN = Vetor2D(0, 1);
const Vetor2D Mariama::VD_RIGHT = Vetor2D(1, 0);
const Vetor2D Mariama::VD_LEFT = Vetor2D(-1, 0);
const Vetor2D Mariama::VD_STOP = Vetor2D::ZERO;

Mariama::Mariama(int vel) throw(LoadImageException,NoVideoBufferException) : Personagem("Mariama", 60, 52, "resources/mari_redim.png")
{
    this->vel = vel;

    this->setCurrentI(0);
    this->setCurrentJ(0);
}

Mariama::~Mariama()
{
    //dtor
}


void Mariama::setVel(int vel)
{
    this->vel = vel;
}

int Mariama::getVel()
{
    return this->vel;
}

void Mariama::setVDirector(Vetor2D vdirector)
{
    this->vdirector = vdirector;
}

Vetor2D& Mariama::getVDirector()
{
    return this->vdirector;
}

void Mariama::handleEvent(SDL_Event &event)
{
    this->vdirector = Mariama::VD_RIGHT;

    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
        case SDLK_RIGHT:

            this->vdirector = Mariama::VD_RIGHT;

            //this->setOffset(this->getOffset() + this->vdirector*this->vel);

            if( this->getCurrentJ() != 3 )
            {
                this->setCurrentJ(3);
                this->setCurrentI(0);
            }
            break;
        case SDLK_LEFT:

            this->vdirector = Mariama::VD_LEFT;

            //this->setOffset(this->getOffset() + this->vdirector*this->vel);

            if( this->getCurrentJ() != 1 )
            {
                this->setCurrentJ(1);
                this->setCurrentI(0);
            }
            break;
        case SDLK_UP:

            this->vdirector = Mariama::VD_UP;

            //this->setOffset(this->getOffset() + this->vdirector*this->vel);

            if( this->getCurrentJ() != 2 )
            {
                this->setCurrentJ(2);
                this->setCurrentI(0);
            }

            break;
        case SDLK_DOWN:

            this->vdirector = Mariama::VD_DOWN;

            //this->setOffset(this->getOffset() + this->vdirector*this->vel );

            if( this->getCurrentJ() != 0 )
            {
                this->setCurrentJ(0);
                this->setCurrentI(0);
            }

            break;

            default:
            break;
        }
        SDL_Rect mapTmp = map->getRect();
        map->update(event);
        SDL_Rect mapRect = map->getRect();

        Vetor2D pos(this->getSpriteRect().x - mapRect.x,this->getSpriteRect().y - mapRect.y);
        SDL_Rect mariRect;
        mariRect.x = pos.getX();
        mariRect.y = pos.getY();
        mariRect.w = this->getSpriteRect().w;
        mariRect.h = this->getSpriteRect().h;

        if( map->isColliding(mariRect,"Collision"))
        {
            map->setRect(mapTmp);
        }


        
        
  

        this->setCurrentI(this->getCurrentI() + 1);
    }
    else
    {
        this->setCurrentI(0);
    }
}
