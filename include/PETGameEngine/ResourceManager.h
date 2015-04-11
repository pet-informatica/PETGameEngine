#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H


#include <SDL2/SDL.h>
#include <SDL_image.h>
//#include <SDL2/SDL_events.h>
//#include <SDL2/SDL_keyboard.h>
//#include <SDL2/SDL_keycode.h>
#include "Component.h"


#include <string>

using std::string;

class ResourceManager
{
    public:

        static const SDL_Color defaultColorKey;

        ResourceManager();
        virtual ~ResourceManager();


        static SDL_Surface* loadImage(string filename,  SDL_Surface* videoBuffer, SDL_Color colorKey = ResourceManager::defaultColorKey);
        static SDL_Surface* createSDLSurface(Uint16 width, Uint16 height, SDL_Surface* videoBuffer);





    protected:
    private:
};

#endif // RESOURCEMANAGER_H
