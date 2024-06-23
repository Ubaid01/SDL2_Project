#ifndef GAME_H
#define GAME_H

#include <iostream>
using namespace std;
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <fstream>
#include <vector>

#include "audio.h"
#include "object.h"
#include "entity.h"

class Game {
public:
	  Game( const char* title );
	  ~Game();
	  void startGame();
	  void update();
	  void inputs();
	  void render();
	  void drawObject(Object o);
	  void drawFont(const char* msg, int x, int y, int r, int g, int b);
	  void loadMap(const char* filename);
	  void drawMap();
	  void scroll(int x, int y);
	  bool isRunning () const ;
	  bool collision(Object a, Object b);
private:
	  SDL_Window* window;
	  SDL_Renderer* renderer;
	  TTF_Font* font;
	  Entity player;
	  vector<Object> map;
	  bool gameRunning;
	  int windowWidth, windowHeight;
	  const int tileSize;
	  const int gravity;
	  int mouseX ;
	  int mouseY ;
	  int mapX ;
	  int mapY ;
	  int speed;
	  bool is_left, is_right, is_up, is_down, fall;
	  int idle_l, idle_r, run_l, run_r;
	  int count;
	  int frameCount, timerFPS, lastFrame;
};

#endif //GAME_H
