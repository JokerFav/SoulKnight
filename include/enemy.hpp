#ifndef enemy_HPP
#define enemy_HPP
#include "Window.hpp"
using namespace std;

class Enemy : public Entity
{
public:
	virtual ~Enemy() = default;
	Enemy(vector2f spawn_point, SDL_Rect new_sprite);
protected:
	int health_point, state, order, wait, speed;
	SDL_Rect hitbox;
	vector2f target;
};

class Slime : public Enemy 
{
public:
	Slime(vector2f spawn_point);
	void update(float current_time, vector2f new_target, float delta_time
		, SDL_Rect player_hitbox);
private:
	vector2f direction;
	vector2f max_move, current_move;
};

extern vector <Enemy*> enemies;

void spawn_enemies();












#endif