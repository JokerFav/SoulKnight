#ifndef vector2f_HPP
#define vector2f_HPP

#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>

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
inline mt19937 random(chrono::steady_clock::now().time_since_epoch().count());

extern SDL_Rect camera;
extern vector<SDL_Rect> map_tiles;
const float sc45 = 0.7071f;

struct vector2f
{
	vector2f(float p_x = 0.0f, float p_y = 0.0f) : x(p_x), y(p_y) {}
	float x, y;
};



#endif