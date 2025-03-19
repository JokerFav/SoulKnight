#include "enemy.hpp"
using namespace std;

vector <Enemy*> enemies;

Enemy::Enemy(vector2f spawn_point, SDL_Rect new_sprite):
	Entity(spawn_point)
{
	pos = spawn_point;
	sprite = new_sprite;
	last_update = 0;
}

Slime::Slime(vector2f spawn_point):
	Enemy(spawn_point, {0, 0, 16, 32})
{
	health_point = 3;
	speed = 60;
	state = 0;
	wait = 2;
	texture = main_window.load_texture("res/slimeball.png");
	hitbox = SDL_Rect{(int)pos.x, (int)pos.y + 16, 16, 16};
}

void Slime::update(float current_time)
{
	if(current_time - last_update > 0.1f)
	{
		last_update = current_time;
		switch(state)
		{
			case 0: // idle
				if(order == 8)
				{
					if(wait > 0)
					{
						wait--;
						order = 4;
					}
					else
					{
						state = 1;
						order = 8;
					}
				}
				break;
			case 1: // jump 
				if(order == 16)
				{
					wait = 2;
					state = 0;
					order = 4;
				}
				break;
		}
		set_sprite(vector2f(0, order));
		order++;
		switch(state)
		{
			case 0:
				break;
			case 1:
				move_x(speed, hitbox);
				break;
		}
	}
}

void spawn_enemies()
{
	enemies.push_back(new Slime(vector2f(231, 63)));
}
