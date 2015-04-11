#include "VisualComponent.h"
#include "screen.h"
#include "LightSurface.h"
#include <exception>
#include <list>
#include "messageSender.h"
#include <sstream>
#include "VersatileSurface.h"
#include "Sprite.h"
#include "Zombie.h"
#include "Mariama.h"
#include "Alien.h"
#include "Ghost.h"
#include "Item.h"
#include "TiledMap.h"



using namespace std;

const Vetor2D X_AXIS = Vetor2D(1,0);
const int TIMEOUT_PICKITEM = 5000;
const int TIMEOUT_INTRO = 6000;

bool isInsideTheScreen(VisualComponent* vcomp, Screen* tela);
bool checkOutScreen(VisualComponent* comp, Screen* tela);
Item* chooseItem(Screen* tela);
Vetor2D randomOffset(Item* item, Screen* tela);
void checkItems(Screen* tela, Personagem* perso);

stringstream ss;

LightSurface *backGround = NULL;
LightSurface *intro = NULL;
Zombie* zombie = NULL;
Alien* alien = NULL;
Ghost* ghost = NULL;
Mariama* mari = NULL;
TiledMap* map = NULL;

Item *item[3];
Cronometro itemChronos;
Cronometro introChronos;
Item* lastItemPut = NULL;


int main(int argc,char *args[])
{
    Screen tela(800,600,false,"defaultTitle");
    printf("Surface ok\n");

    try
    {

        map = new TiledMap("resources/Tilesets/cin.tmx");

        backGround = new LightSurface("resources/background.jpg");
        printf("Background ok\n");
        intro = new LightSurface("resources/intro.png");
        printf("Intro ok\n");
        mari = new Mariama(15);
        printf("Mariama ok\n");
        zombie = new Zombie(180, mari, 20, 300);
        printf("Zombie ok\n");
        alien = new Alien(180, mari, 14, 300);
        printf("Alien ok\n");
        ghost = new Ghost(360, mari, 7, 500);
        printf("Ghost ok\n");

        item[0] = new Item("resources/pinkoleh.png", mari);
        item[1] = new Item("resources/orangeJuice.png", mari);
        item[2] = new Item("resources/birthdaycake.png", mari);

        printf("Items ok\n");

    }
    catch(exception &e)
    {

        sendMessage(e.what());
        exit(1);

    }
    printf("Surfaces and Characters ok\n");

    tela.setWindowTitle("Mariama monstros e doces");
    introChronos.start();

    //intro->setOffset(tela.getDimension()/2 - intro->getDimension()/2);

    //tela.add(intro);
    //tela.draw();
    //while( introChronos.getTicks() <= TIMEOUT_INTRO );



    //tela.remove(intro);

    //delete intro;

    introChronos.stop();

    tela.add(map);
    tela.add(mari);
    //tela.add(zombie);
    //tela.add(alien);
    //tela.add(ghost);

    lastItemPut = chooseItem(&tela) ;
    tela.add( lastItemPut );


    zombie->setOffset(Vetor2D::ZERO);
    alien->setOffset( tela.getDimension() - alien->getDimension()*1.2 );
    ghost->getOffset().setX( tela.getDimension().getX() );

    Vetor2D center = tela.getDimension()/2 - mari->getDimension()/2;

    
    mari->setOffset(center);
    mari->map = map;

    stringstream message;

    tela.setMaxFps(60);



    Cronometro timer;

    bool quit = false;

    SDL_Event event;

    //SDL_EnableKeyRepeat(100,50);

    itemChronos.start();

    while(!quit)
    {
        while(SDL_PollEvent(&event))
        {

            mari->handleEvent(event);
            

           

            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
            if(event.type == SDL_KEYDOWN)
            {

                switch(event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                default:
                    break;
                }



            }



        }

        checkOutScreen(zombie, &tela);
        checkOutScreen(alien, &tela);
        checkOutScreen(ghost, &tela);

        if( mari->getWasCaught() )
        {
            mari->setWasCaught(false);
            // sendMessage("Mari was caught!");
            mari->setOffset( zombie->getOffset()/3 + alien->getOffset()/3 + ghost->getOffset()/3 );

            mari->setPoints( mari->getPoints() - 3);

            if( zombie->getVDirector() == Monstro::VD_STOP && alien->getVDirector() == Monstro::VD_STOP && ghost->getVDirector() == Monstro::VD_STOP )
            {
                sendMessage("Mari was caught! Game Over! Try to save Mariama's birthday again!");
                mari->setPoints(0);
                zombie->setOffset(Vetor2D::ZERO);
                alien->setOffset( tela.getDimension() - alien->getDimension()*1.2 );
                ghost->getOffset().setX( tela.getDimension().getX() );
                backGround->setSurface(ResourceManager::loadImage("resources/background.jpg", ghost->getVideoBuffer(), ResourceManager::defaultColorKey));
                for(int i=0;i<3;i++){
                    item[i]->setNTimesPicked(0);
                }

            }
        }

        ss.str("");

        ss << "Score[ " << mari->getPoints() << " ] Cakes[ " << item[2]->getNTimesPicked() << " ] Orange Juice[ " << item[1]->getNTimesPicked() << " ] Pinkoleh[ " << item[0]->getNTimesPicked() << " ] Time to pick item: " << (TIMEOUT_PICKITEM - itemChronos.getTicks()) << " ms ... 26/10/2011 Happy Birthday Mari ^^! - E.A.A." << endl;

        tela.setWindowTitle(ss.str());
        tela.draw();
        tela.update();
        checkItems(&tela, mari);

    }


    delete backGround;
    delete zombie;
    delete alien;
    delete ghost;
    delete mari;
    delete map;

    for(int i=0; i<3; i++) delete item[i];

    return 0;

}

bool isInsideTheScreen(VisualComponent* visualComp, Screen* tela)
{
    Vetor2D v_tela = tela->getDimension();
    Vetor2D v_comp = visualComp->getOffset();

    return  (v_comp.getX() >= 0 && v_comp.getY() >= 0 && v_comp.angleBetween(X_AXIS) >= 0 && v_comp.angleBetween(X_AXIS) <= 90  && v_comp.getNorma() <= v_tela.getNorma());

}

bool checkOutScreen(VisualComponent* comp, Screen* tela)
{
    if( comp->getOffset().getX() < 0 ) {
        comp->getOffset().setX(0);
        return true;
    }
    if( comp->getOffset().getY() < 0 ) {
        comp->getOffset().setY(0);
        return true;
    } 
    if( comp->getOffset().getX() > (tela->getDimension().getX() - comp->getDimension().getX()) ){
        comp->getOffset().setX(tela->getDimension().getX() - comp->getDimension().getX());
        return true;
    } 
    if( comp->getOffset().getY() > (tela->getDimension().getY() - comp->getDimension().getY()) ) {
        comp->getOffset().setY(tela->getDimension().getY() - comp->getDimension().getY());
        return true;
    }

    return false;


}

Item* chooseItem(Screen* tela)
{
    int i = rand()%3;
    item[i]->setOffset( randomOffset(item[i], tela) );

    return item[i];
}

Vetor2D randomOffset(Item* item, Screen* tela)
{
    int maxX = int(tela->getDimension().getX() - item->getDimension().getX());
    int maxY = int(tela->getDimension().getY() - item->getDimension().getY());

    return Vetor2D(rand()%maxX, rand()%maxY);
}

void checkItems(Screen* tela, Personagem* perso)
{
    bool found = false;
    bool timeout = false;
    int i = 0;
    while( i<3 && !found)
    {
        found = item[i]->getPicked();

        if( !found ) i++;
    }

    timeout = (itemChronos.getTicks() >= TIMEOUT_PICKITEM);

    if(found || timeout )
    {
        if(timeout)
        {
            tela->remove(lastItemPut);
        }
        else if(found)
        {
            tela->remove(item[i]);
            item[i]->setPicked(false);
        }


        lastItemPut = chooseItem(tela);
        tela->add( lastItemPut );

        if(found) perso->setPoints(perso->getPoints() + item[i]->getNTimesPicked());

        if( i == 2 && item[i]->getNTimesPicked() >= 3)
        {
            backGround->setSurface(ResourceManager::loadImage("resources/birthdaybg.jpg", perso->getVideoBuffer(), ResourceManager::defaultColorKey));
        }

        itemChronos.stop();
        itemChronos.start();

    }




}

