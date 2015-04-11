#ifndef MARIAMA_H
#define MARIAMA_H

#include "Personagem.h"
#include "TiledMap.h"

class Mariama : public Personagem
{
    protected:
    private:

        int vel;
        Vetor2D vdirector;

    public:
        //Default vdirectors
        static const Vetor2D VD_UP;
        static const Vetor2D VD_DOWN;
        static const Vetor2D VD_LEFT;
        static const Vetor2D VD_RIGHT;
        static const Vetor2D VD_STOP;


        TiledMap* map;

        Mariama(int vel) throw(LoadImageException,NoVideoBufferException);
        virtual ~Mariama();


        void setVel(int vel);
        int getVel();

        void handleEvent(SDL_Event &event);

        void setVDirector(Vetor2D vdirector);
        Vetor2D& getVDirector();

};

#endif // MARIAMA_H
