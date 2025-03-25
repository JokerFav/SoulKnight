#ifndef object_HPP
#define object_HPP
#include "Window.hpp"
using namespace std;

extern vector<Entity*> objects;

void spawn_objects();

class Wall : public Entity
{
public:
	Wall(vector2f spawn_point, SDL_Rect new_sprite);
};

class Decorations : public Entity 
{
public:
	Decorations(vector2f spawn_point, SDL_Rect new_sprite);
};











#endif