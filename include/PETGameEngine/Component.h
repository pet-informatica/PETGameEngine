#ifndef COMPONENT_H
#define COMPONENT_H

#include "Vetor2D.h"
#include <SDL2/SDL.h>
#include <SDL_image.h>


class Component
{
    protected:

     static SDL_Surface* videoBuffer;
     static SDL_Renderer *render;
     static SDL_Window *screen;
     static SDL_Texture *sdlTexture;
     static SDL_Texture *sdlTexture2;

    public:



        Component();
        virtual ~Component();

        virtual void draw() = 0;
        virtual void update() = 0;
        virtual void update(SDL_Event &event) {}

        SDL_Surface* getVideoBuffer(){
            return Component::videoBuffer;
        }


};

#endif
