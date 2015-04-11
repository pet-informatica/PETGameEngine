#include "Component.h"
#include "messageSender.h"

Component::Component()
{


}

Component::~Component()
{
}

SDL_Surface* Component::videoBuffer = NULL;
SDL_Renderer* Component::render = NULL;
SDL_Window* Component::screen = NULL;
SDL_Texture* Component::sdlTexture = NULL;
SDL_Texture* Component::sdlTexture2 = NULL;
