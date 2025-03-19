#ifndef object_HPP
#define object_HPP
#include "vector2f.hpp"
using namespace std;


class Object
{
public:
	Object(SDL_Texture* new_tex);
	void render_behind(float y);
	void render_front(float y);
protected: 
	vector <vector2f> pos;
	vector <int> order;
	SDL_Texture* tex;
	vector <SDL_Rect> tiles;
};

class Wall : public Object
{
public:
	Wall();
};

class Decorations : public Object 
{
public:
	Decorations();
};












#endif