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
	bool is_spawn();
	SDL_Rect get_attack_hitbox();
	virtual SDL_Rect get_leg_rect() {return SDL_Rect{0, 0, 0, 0};}
	float get_y();
	Enemy(vector2f spawn_point, SDL_Rect new_sprite);
protected:
	int wait;
	vector2f target;
	bool spawned, death, attack;
	SDL_Rect real_attack_hitbox;
};

extern vector <Enemy*> enemies;
extern vector <Enemy*> rooms[3];

void spawn_enemies();

class Slime : public Enemy 
{
public:
	Slime(vector2f spawn_point);
	SDL_Rect set_attack_hitbox();
	SDL_Rect get_leg_rect();
	void update(float current_time, float delta_time);
private:
	vector2f direction;
	vector2f max_move, current_move;
	SDL_Rect attack_hitbox[4];
};

class Troll : public Enemy 
{
public:
	Troll(vector2f spawn_point);
	SDL_Rect set_attack_hitbox();
	SDL_Rect get_leg_rect();
	void update(float current_time, float delta_time);
private:
	vector2f direction;
	vector2f max_move, current_move;
};

class Orc : public Enemy 
{
public:
	Orc(vector2f spawn_point);
	SDL_Rect set_attack_hitbox();
	SDL_Rect get_leg_rect();
	void update(float current_time, float delta_time);
private:
	vector2f direction;
	vector2f max_move, current_move;
	SDL_Rect attack_hitbox[4];
};

class Skeleton : public Enemy 
{
public:
	Skeleton(vector2f spawn_point);
	SDL_Rect set_attack_hitbox();
	SDL_Rect get_leg_rect();
	void update(float current_time, float delta_time);
private:
	vector2f direction;
	vector2f max_move, current_move;
};

class Projectile : public Enemy 
{
public:
	Projectile(vector2f spawn_point, int type);
	void update(float current_time, float delta_time);
	float get_y();
private:
	vector2f direction;
	float speedx, speedy;
};












#endif