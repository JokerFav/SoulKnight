#ifndef object_HPP
#define object_HPP
#include "vector2f.hpp"
using namespace std;

// object is just pictures
// make the game more realistic
// can't move



class Object
{
public:
	Object(SDL_Texture* new_tex);
	void render_behind(Window &main_window, float y);
	void render_front(Window &main_window, float y);
protected: 
	vector <vector2f> pos;
	vector <int> order;
	SDL_Texture* tex;
	vector <SDL_Rect> tiles;
};

class Wall : public Object
{
public:
	Wall(Window &main_window);
};

class Decorations : public Object 
{
public:
	Decorations(Window &main_window);
};












#endif