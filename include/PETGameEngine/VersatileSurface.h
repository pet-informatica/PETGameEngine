#ifdef _D_VSURFACE_H_

#ifndef _VSURFACE_H_
#define _VSURFACE_H_



#include "LightSurface.h"
#include "SDL/SDL_rotozoom.h"
#include "messageSender.h"
#include <sstream>

//Vetores da base canônica do R2,vetores diretores dos eixos cartesianos
const Vetor2D VEIXO_X = Vetor2D(1,0);
const Vetor2D VEIXO_Y = Vetor2D(0,1);
const float ZOOM_VALUE_LIMIT = 0.001f;

class VersatileSurface : public Surface
{
    private:

    LightSurface fixedSurface;

    Vetor2D vdirector;

    float taxaZoom;

    protected:

    static const Vetor2D defaultVDirector;
    static const float defaultTaxaZoom;

    void updateChanges();

    VersatileSurface();

    public:


        VersatileSurface(string filename,Vetor2D offset = Vetor2D::ZERO,SDL_Color colorKey = VersatileSurface::defaultColorKey) throw(LoadImageException,NoVideoBufferException);

        VersatileSurface(Uint16 width,Uint16 height) throw(LoadImageException,NoVideoBufferException);

        Vetor2D getVCenter();
        void setVCenter(Vetor2D vcenter);

        Vetor2D getVDirector();
        void setVDirector(Vetor2D vdirector);


        void rotate(float degrees);

        float getTaxaZoom();
        void setTaxaZoom(float taxaZoom);

        virtual void draw();
        virtual void update();

        virtual void setOffset(Vetor2D offset);





};
#endif // _VSURFACE_H_

#endif 

