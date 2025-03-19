#ifndef enemy_HPP
#define enemy_HPP
#include "Window.hpp"
using namespace std;

class Enemy : public Entity
{
public:
	Enemy(vector2f spawn_point, SDL_Rect new_sprite);
protected:
	int health_point, state, order, wait, speed;
	SDL_Rect hitbox;
};

class Slime : public Enemy 
{
public:
	Slime(vector2f spawn_point);
	void update(float current_time);
};

extern vector <Enemy*> enemies;

void spawn_enemies();












#endif