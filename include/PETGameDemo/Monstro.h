#ifndef MONSTRO_H
#define MONSTRO_H

#include "Sprite.h"
#include "NoTargetException.h"
#include "Personagem.h"
#include "Cronometro.h"
#include <cstdlib>
#include <time.h>

class Monstro : public Sprite
{
    protected:

    Vetor2D vdirector;
    double visualField;
    double vel;
    Personagem* target;


    int state;

    //Limite de distância visual
    int thresholdVision;


    //Delay de resposta do monstro
    Cronometro delay_seek;
    Cronometro delay_universal;



    public:

        static const int RESPONSE_TIME_SEEK;
        static const int RESPONSE_TIME_UNIVERSAL;

        static const int SEEK;
        static const int PURSUIT;
        static const int CATCH;

        //Default vdirectors
        static const Vetor2D VD_UP;
        static const Vetor2D VD_DOWN;
        static const Vetor2D VD_LEFT;
        static const Vetor2D VD_RIGHT;
        static const Vetor2D VD_STOP;

        Monstro(Uint16 spriteWidth, Uint16 spriteHeight, string spriteSrc, double visualField, Personagem* target, double vel,int thresholdVision) throw(LoadImageException,NoVideoBufferException, NoTargetException);
        virtual ~Monstro();

        void setVDirector(Vetor2D vdirector);
        Vetor2D& getVDirector();

        void setVisualField(double visualField);
        double getVisualField();

        void setVel(double vel);
        double getVel();

        void setThresholdVision(int tresholdVision);
        int getThresholdVision();

        void move();

        virtual void changeFrame() = 0;

        virtual void actuate();
        virtual void seek();
        virtual void pursuit();

        bool targetIsVisible();

        int chooseDirection();


        virtual void update();

};

#endif // MONSTRO_H
