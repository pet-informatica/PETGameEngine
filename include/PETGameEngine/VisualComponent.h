#ifndef VISUAL_COMPONENT_H
#define VISUAL_COMPONENT_H

#include "Component.h"

class VisualComponent : public Component
{
    protected:

        SDL_Surface* surface;
        SDL_Texture* texture;
        Vetor2D offset;

    public:

        VisualComponent();
        VisualComponent(SDL_Surface* surface,Vetor2D offset = Vetor2D::ZERO);
        virtual ~VisualComponent();

        virtual void clear();

        virtual Vetor2D& getOffset();
        virtual void setOffset(Vetor2D offset);

        SDL_Rect getRect();



        virtual SDL_Surface* getSurface();
        virtual void setSurface(SDL_Surface* surface);

        virtual Vetor2D getDimension();

};

#endif
