#ifndef COMPONENT_SET_H
#define COMPONENT_SET_H

#include <list>
#include "Component.h"

using std::list;

class ComponentSet : public Component
{
    protected:

        list<Component*> components;

    public:

        ComponentSet();
        virtual ~ComponentSet();

        virtual void draw();
        virtual void update();
        virtual void update(SDL_Event &event);

        //Adiciona um componente no final da lista
        void add(Component* comp);
        //Remove um component
        void remove(Component *comp);



};











#endif
