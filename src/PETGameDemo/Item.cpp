#include "Item.h"

Item::Item(string filename, Personagem* owner) throw(NoTargetException) : LightSurface(filename)
{
    this->owner =  owner;
    this->nTimesPicked = 0;
    this->picked = false;

    if( !this->owner )
    {
        throw NoTargetException();
    }


}

Item::~Item()
{
    //dtor
}

void Item::setPicked(bool picked)
{
    this->picked = picked;

    if(this->picked) this->nTimesPicked++;
}

bool Item::getPicked()
{
    return this->picked;
}

void Item::setNTimesPicked(int nTimesPicked )
{
    this->nTimesPicked = nTimesPicked;
}

int Item::getNTimesPicked()
{
    return this->nTimesPicked;
}

void Item::update()
{
    Vetor2D centroItem = (this->getOffset() + this->getDimension()/2);
    Vetor2D centroPerso = (owner->getOffset() + owner->getDimension()/2);
    Vetor2D difCentro = centroItem - centroPerso;
    bool wasPicked = (difCentro.getNorma() <= this->getDimension().getNorma()/2);

    this->setPicked(wasPicked);
}
