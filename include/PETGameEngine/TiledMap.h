#ifndef TILEDMAP_H
#define TILEDMAP_H

#include "VisualComponent.h"
#include <tmx.h>
#include <exception>



//Incomplete
class TiledMap : public VisualComponent
{



    private:
        tmx_map* map;
        SDL_Texture *mapTexture;
		SDL_Rect mapRect;
		int xDelta, yDelta;


        void set_color(SDL_Renderer *ren, int color);
        void draw_polyline(SDL_Renderer *ren, int **points, int x, int y, int pointsc);
        void draw_polygon(SDL_Renderer *ren, int **points, int x, int y, int pointsc);
        void draw_objects(SDL_Renderer *ren, tmx_object *head, int color);
        int gid_clear_flags(unsigned int gid);
        void draw_layer(SDL_Renderer *ren, tmx_map *map, tmx_layer *layer);
        void draw_image_layer(SDL_Renderer *ren, tmx_image *img);
        SDL_Texture* render_map(SDL_Renderer *ren, tmx_map *map);

        bool isCollidingObjects(const SDL_Rect& rect, const string& groupName, tmx_object *head);

        bool isColliding(const SDL_Rect& collisionRect, const SDL_Rect& otherRect);

    public:

    	class MapException : public std::exception
		{
		    public:
		    	const char* msg;

		        MapException(const char* msg = "Unable to load map!") : msg(msg){
		        }

		        virtual const char* what() const throw() {
		        	return msg;
		        }



		};


        TiledMap(const string& tileSrcFile, Uint16 width, Uint16 height) throw(MapException);
        TiledMap(const string& tileSrcFile) throw(MapException);
        virtual ~TiledMap();

        virtual void draw();
        virtual void update();
        virtual void update(SDL_Event &event);

        bool isColliding(const SDL_Rect& rect, const string& groupName);

        SDL_Rect getRect(){
            return this->mapRect;
        }

        void setRect(SDL_Rect rect){
            this->mapRect = rect;
        }


        
};

#endif // TILEDMAP_H
