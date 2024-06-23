#pragma once

#ifndef __MAP_H__
#define __MAP_H__

#include "vector"
#include "SDL.h"
#include "object.h"

class Map 
{
public:
	Map();
	void fill( int x, int y, int w, int h ) ;
	void ground(int& x, int num, int frame) ;
	void groundWithSoil(int& x, int num, int frame, int soil_tiles);
	void renderMap( int start, SDL_Renderer* ren ) ;
	void loadMap( SDL_Renderer* ren ) ;
	SDL_Texture* getBackgroundTexture() const { return backgroundTexture.getTexture(); }
	void scroll(int x, int y);
	const std::vector<Object>& getTiles() const { return tiles; } // Method to get tiles
private:
	const int mapWidth;
	const int mapHeight;
	const int mapFrames;
	std::vector<std::vector<int>> map ; // Error problem with ground_soil
	std::vector<SDL_Rect> MapClips;
	Object mapTexture;
	Object backgroundTexture;
	//std::vector<Object> tiles; // To store all the tile objects
};

#endif // __MAP_H__