#ifndef enemy_HPP
#define enemy_HPP
#include "Window.hpp"
using namespace std;

class Enemy : public Entity
{
public:
	virtual ~Enemy() = default;
	bool is_death();
	bool is_attack();
	Enemy(vector2f spawn_point, SDL_Rect new_sprite);
protected:
	int wait;
	vector2f target;
	bool spawned, death, attack;
};

class Slime : public Enemy 
{
public:
	Slime(vector2f spawn_point);
	SDL_Rect get_attack_hitbox();
	void update(float current_time, float delta_time);
private:
	vector2f direction;
	vector2f max_move, current_move;
	SDL_Rect attack_hitbox[4];
};

extern vector <Enemy*> enemies;

void spawn_enemies();












#endif