#include "VersatileSurface.h"

const Vetor2D VersatileSurface::defaultVDirector = Vetor2D(1,0);
const float VersatileSurface::defaultTaxaZoom = 1.0f;

VersatileSurface::VersatileSurface(string filename,Vetor2D offset,SDL_Color colorKey) throw(LoadImageException,NoVideoBufferException)
 : Surface(filename,offset,colorKey)
{

     this->fixedSurface.setOffset(offset);

     this->vdirector = VersatileSurface::defaultVDirector;

     this->taxaZoom = VersatileSurface::defaultTaxaZoom;

     this->fixedSurface.setSurface(SDL_DisplayFormatAlpha(this->getSurface()));
}

VersatileSurface::VersatileSurface() : Surface()
{

}

VersatileSurface::VersatileSurface(Uint16 width, Uint16 height)  throw(LoadImageException,NoVideoBufferException) : Surface(width,height)
{
     this->fixedSurface.setOffset(Vetor2D(0,0));

     this->vdirector = VersatileSurface::defaultVDirector;

     this->taxaZoom = VersatileSurface::defaultTaxaZoom;

     this->fixedSurface.setSurface(SDL_DisplayFormatAlpha(this->getSurface()));

}

Vetor2D VersatileSurface::getVCenter()
{
    Vetor2D vcenter = ( this->fixedSurface.getOffset() + Vetor2D(this->fixedSurface.getRect().w/2,this->fixedSurface.getRect().h/2) );

    return vcenter;
}

void VersatileSurface::setVCenter(Vetor2D vcenter)
{
    Vetor2D vDiff = vcenter - this->getVCenter();

    Surface::setOffset(this->getOffset() + vDiff);

    this->fixedSurface.setOffset(this->fixedSurface.getOffset() + vDiff);

}

Vetor2D VersatileSurface::getVDirector()
{
    return this->vdirector;
}

void VersatileSurface::setVDirector(Vetor2D vdirector)
{
    this->vdirector = vdirector;

    this->rotate(0);

    this->updateChanges();
}

void VersatileSurface::rotate(float degrees)
{
    this->vdirector = this->vdirector.rotate(degrees);

    this->setSurface(rotozoomSurface(this->fixedSurface.getSurface(),this->vdirector.getAngle(),this->taxaZoom,SMOOTHING_ON));

    this->updateChanges();

}

float VersatileSurface::getTaxaZoom()
{
    return this->taxaZoom;
}

void VersatileSurface::setTaxaZoom(float taxaZoom)
{
    if(taxaZoom >= ZOOM_VALUE_LIMIT) this->taxaZoom = taxaZoom;


    this->rotate(0);
}

void VersatileSurface::updateChanges()
{
    Vetor2D vcentroAntigo = Vetor2D(this->fixedSurface.getRect().w/2,this->fixedSurface.getRect().h/2);
    Vetor2D vcentroNovo = Vetor2D(this->getRect().w/2,this->getRect().h/2);

    Vetor2D vDiff = vcentroAntigo - vcentroNovo;

    Surface::setOffset(this->fixedSurface.getOffset() + vDiff);

}

void VersatileSurface::draw()
{
    SDL_Rect offset = this->getRect();

    if(Surface::videoBuffer!= NULL && this->getSurface() != NULL)
    {
        SDL_BlitSurface(this->getSurface(),NULL,Surface::videoBuffer,&offset);
    }

}

void VersatileSurface::update()
{

}

void VersatileSurface::setOffset(Vetor2D offset)
{
    Vetor2D vDiff = offset - this->getOffset();

    this->setVCenter(this->getVCenter() + vDiff);

}
