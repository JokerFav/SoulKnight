#ifndef Window_HPP
#define Window_HPP

#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 608;
const int MAP_WIDTH = 1200;
const int MAP_HEIGHT = 1200;
const int CAMERA_WIDTH = 200;
const int CAMERA_HEIGHT = 152;
const string WINDOW_NAME = "JokerFav's screen";
const int FPS = 100;
const float FRAME_DELAY = 1000.0f / FPS;

extern SDL_Rect camera;
extern vector<SDL_Rect> map_tiles;


class Window
{
	public:
			Window();
			void before_render();
			SDL_Texture* load_texture(string path);
			void QuitSDL();
			void render_map(SDL_Rect &tile, SDL_Texture* &MapTexture);
			void present();
		SDL_Window* window;
		SDL_Renderer* renderer;
	private:
};

extern Window main_window;


#endif