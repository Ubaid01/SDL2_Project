#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
using namespace std;
#include <SDL.h>
#include <SDL_image.h>

class Object {
public:
	Object() ;
	void setSource(int x, int y, int w, int h);
	SDL_Rect getSource() const { return src ; }
	void setDest(int x, int y);
	void setDest(int x, int y, int w, int h);
	SDL_Rect getDest() const { return dest ; }
	void setTexture(string filename, SDL_Renderer* ren);
	SDL_Texture* getTexture() const { return texture ; }
	void setSolid(bool s) { solid = s ; }
	bool getSolid() const { return solid ; }
	int getDX() const { return dest.x ; }
	int getDY() const { return dest.y ; }
	int getDW() const { return dest.w ; }
	int getDH() const { return dest.h ; }
	void setId(int i) { id = i ; }
	int getId() const { return id ; }
private:
	SDL_Rect src;
	SDL_Rect dest;
	SDL_Texture* texture;
	bool solid;
	int id;
};


#endif //OBJECT_H
