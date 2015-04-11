#ifndef ITEM_H
#define ITEM_H

#include "LightSurface.h"
#include "NoTargetException.h"

#include "Personagem.h"

class Item : public LightSurface
{
    protected:
    private:

        Personagem* owner;
        bool picked;
        int nTimesPicked;

    public:
        Item(string filename, Personagem* owner) throw(NoTargetException);
        virtual ~Item();


        void update();

        void setPicked(bool picked);
        bool getPicked();

        void setNTimesPicked( int nTimesPicked );
        int getNTimesPicked();

};

#endif // ITEM_H
