#ifndef map_HPP
#define map_HPP
#include "vector2f.hpp"
using namespace std;

class Map
{
public:
	Map();
	void map_init(Window &main_window);
	void map_render(Window &main_window);
private:
	SDL_Texture* MapTexture;
	vector2f pos;
};

#endif
