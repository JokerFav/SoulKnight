#ifndef map_HPP
#define map_HPP
#include "window.hpp"
using namespace std;

class Map
{
public:
	Map();
	void map_init();
	void map_render();
private:
	SDL_Texture* MapTexture;
	vector2f pos;
};

#endif
