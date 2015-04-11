#include "ComponentSet.h"

using namespace std;

ComponentSet::ComponentSet()
{
    this->components = list<Component* > ();
}
ComponentSet::~ComponentSet()
{

    this->components.clear();
}

void ComponentSet::draw()
{
    SDL_RenderClear(ComponentSet::render);

    //Clear screen
    SDL_SetRenderTarget(ComponentSet::render, ComponentSet::sdlTexture2);
    SDL_SetRenderDrawColor(ComponentSet::render, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect( ComponentSet::render, NULL );
    
    SDL_SetRenderTarget(ComponentSet::render, NULL);


    SDL_FillRect(ComponentSet::videoBuffer,NULL,SDL_MapRGBA(ComponentSet::videoBuffer->format,255,0,0,255));

    list<Component*>::iterator it;

    for(it=this->components.begin();it!=this->components.end();it++)
    {

        (*it)->draw();
    }

    SDL_RenderCopy(ComponentSet::render, ComponentSet::sdlTexture2, NULL, NULL);
    SDL_RenderPresent(ComponentSet::render);

}
void ComponentSet::update()
{
    list<Component*>::iterator it;

    for(it=this->components.begin();it!=this->components.end();it++)
    {

        (*it)->update();
    }


}
void ComponentSet::update(SDL_Event &event)
{
    list<Component*>::iterator it;

    for(it=this->components.begin();it!=this->components.end();it++)
    {

        (*it)->update(event);
    }


}

void ComponentSet::add(Component* comp)
{
    this->components.push_back(comp);

}

void ComponentSet::remove(Component* comp)
{
    bool found = false;

    list<Component*>::iterator it;

    for(it = this->components.begin(); it!= this->components.end() && !found ; it++)
    {
        if((*it) == comp)
        {
            this->components.remove(comp);
            found = true;
        }

    }


}
