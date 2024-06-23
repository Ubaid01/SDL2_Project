#include "object.h"

Object::Object()
{
    solid = true;
    texture = nullptr;
}

void Object::setDest(int x, int y, int w, int h)
{
    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;
    // dest = { x , y , w , h } ; // This was causing error 
}

void Object::setDest(int x, int y) {
    dest.x = x ;
    dest.y = y ;
}

void Object::setSource(int x, int y, int w, int h) {
      src.x = x ;
      src.y = y ;
      src.w = w ;
      src.h = h ;
}

void Object::setTexture(std::string filename, SDL_Renderer* renderer)
{
    SDL_Surface* surf = IMG_Load(filename.c_str());
    if (surf == nullptr)
        std::cerr << "Texture Surface can not be initialized! " << SDL_GetError() << std::endl;

    //texture = SDL_CreateTextureFromSurface(renderer, surf);
    texture = IMG_LoadTexture(renderer, filename.c_str());

}
