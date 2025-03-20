#include "enemy.hpp"
using namespace std;

vector <Enemy*> enemies;

Enemy::Enemy(vector2f spawn_point, SDL_Rect new_sprite):
	Entity(spawn_point) // player's hitbox = {+8, +10, 15, 20}
{
	pos = spawn_point;
	sprite = new_sprite;
	last_update = 0;
	target.x = 8 + random() % 16;
	target.y = 10 + random() % 21;
}

Slime::Slime(vector2f spawn_point):
	Enemy(spawn_point, {0, 0, 32, 32})
{
	health_point = 3;
	speed = 15;
	state = 1;
	wait = 2;
	order = 0;
	texture = main_window.load_texture("res/slimeball.png");
}


void Slime::update(float current_time, vector2f new_target, float delta_time
	,SDL_Rect player_hitbox)
{
	hitbox = SDL_Rect{(int)pos.x + 11, (int)pos.y + 17, 10, 11};
	vector2f core(hitbox.x + hitbox.w / 2, hitbox.y + hitbox.h / 2);

	//if(SDL_HasIntersection)

	if(max_move.x <= 0.0f && max_move.y <= 0.0f && state == 2)
	{
		state = 1;
		order = 0;
		wait = 4 + random() % 4;
	} 

	if(wait == 0)
	{
		switch(state)
		{
			case 0:
				break;
			case 1:
				state = 2;
				order = 0;
				wait = 4 + random() % 4;

				new_target.x += target.x;
				new_target.y += target.y;	

				direction.x = (core.x <= new_target.x ? 1 : -1);
				direction.y = (core.y <= new_target.y ? 1 : -1);

				max_move.x = abs(core.x - new_target.x);
				max_move.y = abs(core.y - new_target.y);
				break;
			case 2:
				state = 1;
				order = 0;
				wait = 4 + random() % 8;
				break;
			case 3:
				state = 1;
				order = 0;
				wait = 4 + random() % 4;
				break;
		}
	}

	switch(state)
	{
		case 0:
			break;
		case 1:
			set_sprite(vector2f(0, 4 + order));
			break;
		case 2:
			set_sprite(vector2f(0, 8 + order));

			if(max_move.x > 0.0f) current_move.x = speed * delta_time;
			else current_move.x = 0;
			if(max_move.y > 0.0f) current_move.y = speed * delta_time;
			else current_move.y = 0;

			max_move.x -= current_move.x;
			max_move.y -= current_move.y;

			move_x(current_move.x * direction.x, hitbox);
			move_y(current_move.y * direction.y, hitbox);

			if(direction.x == 1) set_flip(SDL_FLIP_NONE);
			else set_flip(SDL_FLIP_HORIZONTAL);

			break;
		case 3:
			break;
	}

	if(current_time - last_update > 0.15f)
	{
		last_update = current_time;
		wait--;
		order++;
		switch(state)
		{
			case 0: // spawn
				break;
			case 1: // idle
				order %= 4;
				break;
			case 2: // move
				order %= 4;
				break;
			case 3: // attack
				order %= 8;
				break;
		}
	}
}

void spawn_enemies()
{
	enemies.push_back(new Slime(vector2f(231, 63)));
}
