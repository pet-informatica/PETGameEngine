#include "TiledMap.h"

//Incomplete

TiledMap::TiledMap(const string& tileSrcFile, Uint16 width, Uint16 height) throw(MapException) : VisualComponent()
{

}

TiledMap::TiledMap(const string& tileSrcFile) throw(MapException) : VisualComponent()
{

	tmx_img_load_func = (void* (*)(const char*))IMG_Load;
	tmx_img_free_func = (void  (*)(void*))SDL_FreeSurface;

    this->map = tmx_load(tileSrcFile.c_str());

    if( !this->map )
    	throw TiledMap::MapException();

    mapRect.w = map->width  * map->tile_width;
	mapRect.h = map->height * map->tile_height;
	mapRect.x = 0;  mapRect.y = 0;

    if (!(this->mapTexture = render_map(TiledMap::render, this->map)))
    	throw TiledMap::MapException("Unable to create map texture!");

    printf("Map texture ok!\n");

    this->xDelta = TiledMap::videoBuffer->w - mapRect.w;
    this->yDelta = TiledMap::videoBuffer->h - mapRect.h;


}

TiledMap::~TiledMap()
{
    SDL_DestroyTexture(mapTexture);
    tmx_map_free(map);
}

void TiledMap::draw()
{


	SDL_SetRenderTarget(TiledMap::render, TiledMap::sdlTexture2);
	SDL_RenderCopy(TiledMap::render, this->mapTexture, NULL, &this->mapRect);
	SDL_SetRenderTarget(TiledMap::render, NULL);

}

void TiledMap::update()
{


}

void TiledMap::update(SDL_Event &event)
{
	int vel = 15;
	if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
        case SDLK_RIGHT:

        	mapRect.x += -vel;
			
			if (xDelta > 0) {
				mapRect.x = xDelta/2;
			} else {
				if (mapRect.x < xDelta) mapRect.x = xDelta;
				if (mapRect.x > 0) mapRect.x = 0;
			}
			if (yDelta > 0) {
				mapRect.y = yDelta/2;
			} else {
				if (mapRect.y < yDelta) mapRect.y = yDelta;
				if (mapRect.y > 0) mapRect.y = 0;
			}

            break;
        case SDLK_LEFT:

        	mapRect.x += vel;
			
			if (xDelta > 0) {
				mapRect.x = xDelta/2;
			} else {
				if (mapRect.x < xDelta) mapRect.x = xDelta;
				if (mapRect.x > 0) mapRect.x = 0;
			}
			if (yDelta > 0) {
				mapRect.y = yDelta/2;
			} else {
				if (mapRect.y < yDelta) mapRect.y = yDelta;
				if (mapRect.y > 0) mapRect.y = 0;
			}

            break;
        case SDLK_UP:

        	mapRect.y += vel;
			
			if (xDelta > 0) {
				mapRect.x = xDelta/2;
			} else {
				if (mapRect.x < xDelta) mapRect.x = xDelta;
				if (mapRect.x > 0) mapRect.x = 0;
			}
			if (yDelta > 0) {
				mapRect.y = yDelta/2;
			} else {
				if (mapRect.y < yDelta) mapRect.y = yDelta;
				if (mapRect.y > 0) mapRect.y = 0;
			}


            break;
        case SDLK_DOWN:

        	mapRect.y += -vel;
			
			if (xDelta > 0) {
				mapRect.x = xDelta/2;
			} else {
				if (mapRect.x < xDelta) mapRect.x = xDelta;
				if (mapRect.x > 0) mapRect.x = 0;
			}
			if (yDelta > 0) {
				mapRect.y = yDelta/2;
			} else {
				if (mapRect.y < yDelta) mapRect.y = yDelta;
				if (mapRect.y > 0) mapRect.y = 0;
			}


            break;

            default:
            break;
        }
    }

}

bool TiledMap::isColliding(const SDL_Rect& collisionRect, const SDL_Rect& otherRect)
{

	float dcx = (collisionRect.x + collisionRect.w/2) - (otherRect.x + otherRect.w/2);
	float dcy = (collisionRect.y + collisionRect.h/2) - (otherRect.y + otherRect.h/2);
	float dst = sqrtf(dcx*dcx + dcy*dcy);

	
	float radius = fmin(collisionRect.w,collisionRect.h);


	printf("distance %f radius %f char_x %d char_y %d collision_x %d collision_y %d\n", dst, radius,otherRect.x, otherRect.y, collisionRect.x,collisionRect.y);
	if( dst < 50 )
		return true;
	else
		return false;

}

bool TiledMap::isColliding(const SDL_Rect& rect, const string& groupName)
{
	bool coliding = false;

	tmx_layer *layers = map->ly_head;


	
	
	while (layers) {
		if (layers->visible) {
			if (layers->type == L_OBJGR) {

				coliding = isCollidingObjects(rect, groupName, layers->content.head);
			}
		}
		layers = layers->next;
	}


	return coliding;

}

bool TiledMap::isCollidingObjects(const SDL_Rect& rect, const string& groupName, tmx_object *head)
{
	bool coliding = false;

	SDL_Rect objRect;


	while (head) {
		if (head->visible) {
			if (head->shape == S_SQUARE) {
				objRect.x =     head->x;  objRect.y =      head->y;
				objRect.w = head->width;  objRect.h = head->height;

		
				if( head->name != NULL && strcmp(groupName.c_str(), head->name) == 0 ){
					coliding = isColliding(objRect,rect);
				}
				

			} else if (head->shape  == S_POLYGON) {
				//TODO: Check collision with polygon
			} else if (head->shape == S_POLYLINE) {
				//TODO: Check collision with polyline
			} else if (head->shape == S_ELLIPSE) {
				/* FIXME: no function in SDL2 */
			}
		}
		head = head->next;
	}



	return coliding;

}

void TiledMap::set_color(SDL_Renderer *ren, int color) {
	unsigned char r, g, b;
	
	r = (color >> 16) & 0xFF;
	g = (color >>  8) & 0xFF;
	b = (color)       & 0xFF;
	
	SDL_SetRenderDrawColor(ren, r, g, b, SDL_ALPHA_OPAQUE);
}

void TiledMap::draw_polyline(SDL_Renderer *ren, int **points, int x, int y, int pointsc) {
	int i;
	for (i=1; i<pointsc; i++) {
		SDL_RenderDrawLine(ren, x+points[i-1][0], y+points[i-1][1], x+points[i][0], y+points[i][1]);
	}
}

void TiledMap::draw_polygon(SDL_Renderer *ren, int **points, int x, int y, int pointsc) {
	draw_polyline(ren, points, x, y, pointsc);
	if (pointsc > 2) {
		SDL_RenderDrawLine(ren, x+points[0][0], y+points[0][1], x+points[pointsc-1][0], y+points[pointsc-1][1]);
	}
}

void TiledMap::draw_objects(SDL_Renderer *ren, tmx_object *head, int color) {
	SDL_Rect rect;
	set_color(ren, color);
	/* FIXME line thickness */
	while (head) {
		if (head->visible) {
			if (head->shape == S_SQUARE) {
				rect.x =     head->x;  rect.y =      head->y;
				rect.w = head->width;  rect.h = head->height;
				SDL_RenderDrawRect(ren, &rect);
			} else if (head->shape  == S_POLYGON) {
				draw_polygon(ren, head->points, head->x, head->y, head->points_len);
			} else if (head->shape == S_POLYLINE) {
				draw_polyline(ren, head->points, head->x, head->y, head->points_len);
			} else if (head->shape == S_ELLIPSE) {
				/* FIXME: no function in SDL2 */
			}
		}
		head = head->next;
	}
}

int TiledMap::gid_clear_flags(unsigned int gid) {
	return gid & TMX_FLIP_BITS_REMOVAL;
}

void TiledMap::draw_layer(SDL_Renderer *ren, tmx_map *map, tmx_layer *layer) {
	unsigned long i, j;
	unsigned int x, y;
	float op;
	tmx_tileset *ts;
	SDL_Texture *tex_ts;
	SDL_Rect srcrect, dstrect;
	op = layer->opacity;
	for (i=0; i<map->height; i++) {
		for (j=0; j<map->width; j++) {
			ts = tmx_get_tile(map, layer->content.gids[(i*map->width)+j],(unsigned int*)&(srcrect.x), (unsigned int*)&(srcrect.y));
			if (ts) {
				/* TODO Opacity and Flips */
				srcrect.w = dstrect.w = ts->tile_width;
				srcrect.h = dstrect.h = ts->tile_height;
				dstrect.x = j*ts->tile_width;  dstrect.y = i*ts->tile_height;
				tex_ts = SDL_CreateTextureFromSurface(ren, (SDL_Surface*)ts->image->resource_image);
				SDL_RenderCopy(ren, tex_ts, &srcrect, &dstrect);
				SDL_DestroyTexture(tex_ts);
			}
		}
	}
}

void TiledMap::draw_image_layer(SDL_Renderer *ren, tmx_image *img) {
	SDL_Surface *bmp; 
	SDL_Texture *tex;
	SDL_Rect dim;
	
	bmp =  (SDL_Surface*)img->resource_image;
	
	dim.x = dim.y = 0;
	dim.w = bmp->w;
	dim.h = bmp->h;
	
	if ((tex = SDL_CreateTextureFromSurface(ren, bmp))) {
		SDL_RenderCopy(ren, tex, NULL, &dim);
		SDL_DestroyTexture(tex);
	}
	
}

SDL_Texture* TiledMap::render_map(SDL_Renderer *ren, tmx_map *map) {
	SDL_Texture *res;
	tmx_layer *layers = map->ly_head;
	int w, h;
	
	w = map->width  * map->tile_width;  /* Bitmap's width and height */
	h = map->height * map->tile_height;
	
	if (!(res = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h)))
		throw TiledMap::MapException("Could not create map texture!");
	SDL_SetRenderTarget(ren, res);
	
	set_color(ren, map->backgroundcolor);
	SDL_RenderClear(ren);
	
	while (layers) {
		if (layers->visible) {
			if (layers->type == L_OBJGR) {
				draw_objects(ren, layers->content.head, layers->color);
			} else if (layers->type == L_IMAGE) {
				draw_image_layer(ren, layers->content.image);
			} else if (layers->type == L_LAYER) {
				draw_layer(ren, map, layers);
			}
		}
		layers = layers->next;
	}
	
	SDL_SetRenderTarget(ren, NULL);
	return res;
}
