#include "Personagem.h"

Personagem::Personagem(string name, Uint16 spriteWidth, Uint16 spriteHeight, string spriteSrc) throw(LoadImageException,NoVideoBufferException) : Sprite(spriteWidth, spriteHeight, spriteSrc)
{
    this->name = name;
    this->points = 0;
    this->wasCaught = false;
}

Personagem::~Personagem()
{
    //dtor
}



void Personagem::setPoints(int points)
{
    this->points = points;
}

int Personagem::getPoints()
{
    return this->points;
}

void Personagem::setWasCaught(bool wasCaught)
{
    this->wasCaught = wasCaught;
}

bool Personagem::getWasCaught()
{
    return this->wasCaught;
}

void Personagem::setName(string name)
{
    this->name = name;
}

string Personagem::getName()
{
    return this->name;
}
