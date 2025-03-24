#include "enemy.hpp"
#include "player.hpp"
#include "fantasy.hpp"
using namespace std;

vector <Enemy*> enemies;

Enemy::Enemy(vector2f spawn_point, SDL_Rect new_sprite):
	Entity(spawn_point) // player's hitbox = {+8, +10, 15, 20}
{
	spawned = death = false;
	pos = spawn_point;
	sprite = new_sprite;
	last_update = 0;
	target.x = 13 + random() % 4;
	target.y = 18 + random() % 4;
}

Slime::Slime(vector2f spawn_point):
	Enemy(spawn_point, {0, 0, 32, 32})
{
	health_point = 5;
	speed = 15;
	state = 1;
	wait = 2;
	order = 0;
	texture = main_window.load_texture("res/slimeball.png");// 15 -> 18
	attack_hitbox[0] = SDL_Rect{10, 18, 12, 10};
	attack_hitbox[1] = SDL_Rect{9, 20, 14, 8};
	attack_hitbox[2] = SDL_Rect{8, 21, 16, 7};
	attack_hitbox[3] = SDL_Rect{10, 20, 12, 8};
}

SDL_Rect Slime::get_attack_hitbox()
{
	SDL_Rect current_hitbox = SDL_Rect{11, 17, 10, 11};
	if(state == 3)
	{
		switch(order)
		{
			case 3:
				current_hitbox = attack_hitbox[0];
				break;
			case 4:
				current_hitbox = attack_hitbox[1];
				break;
			case 5: 
				current_hitbox = attack_hitbox[2];
				break;
			case 6:
				current_hitbox = attack_hitbox[3];
				break;
		}
	}
	current_hitbox.x += pos.x;
	current_hitbox.y += pos.y;
	return current_hitbox;
}

bool Enemy::is_death()
{
	return death;
}

void Slime::update(float current_time, float delta_time)
{
	if(wait == 0 && state == 5) 
	{
		death = true;
		return;
	}
	hitbox = get_attack_hitbox();
	vector2f core(hitbox.x + hitbox.w / 2, hitbox.y + hitbox.h / 2);
	SDL_Rect player_hitbox = main_player.get_hitbox();
	SDL_Rect weapon_hitbox = sword.get_attack_hitbox();

	if(!spawned)
	{
		if( hitbox.x >= camera.x &&
		hitbox.y >= camera.y &&
		hitbox.x + hitbox.w <= camera.x + camera.w &&
		hitbox.y + hitbox.h <= camera.y + camera.h)
		{
			spawned = true;
			state = order = 0;
			wait = 4;
		}
		else return;
	}

	if(sword.is_attacking() && SDL_HasIntersection(&weapon_hitbox, &hitbox) == SDL_TRUE
		&& ((state > 0 && state < 4) || (state == 4 && wait == 0)))
	{
		state = 4;
		order = 1;
		wait = 4;
		health_point--;
		if(main_player.get_flip() == SDL_FLIP_NONE)
			direction.x = 1;
		else direction.x = -1;
		direction.y = 1.0f / (1 + random() % 5);
	}

	if(health_point == 0)
	{
		health_point--;
		state = 5;
		order = 0;
		wait = 8;
	}

	if(state == 2)
	{
		if(max_move.x <= 0.0f && max_move.y <= 0.0f) wait = 0;
		if(SDL_HasIntersection(&hitbox, &player_hitbox) == SDL_TRUE) wait = 0;
	}


	if(wait == 0)
	{
		if(SDL_HasIntersection(&hitbox, &player_hitbox)) // in attack range
			{
				state = 3;
				order = 0;
				wait = 8;
			}
		else 
		{
			switch(state)
			{
				case 0:
					state = 1;
					order = 0;
					wait = random() % 5;
					break;
				case 1:
				{
					state = 2;
					order = 0;
					wait = 4 + random() % 4;

					vector2f new_target = main_player.get_pos();

					new_target.x += target.x;
					new_target.y += target.y;	

					direction.x = (core.x <= new_target.x ? 1 : -1);
					direction.y = (core.y <= new_target.y ? 1 : -1);

					max_move.x = abs(core.x - new_target.x);
					max_move.y = abs(core.y - new_target.y);
					break;
				}
				case 2:
					state = 1;
					order = 0;
					wait = 4 + random() % 4;
					break;
				case 3:
					state = 1;
					order = 0;
					wait = 4 + random() % 4;
					break;
				case 4:
					state = 1;
					order = 0;
					wait = 1 + random() % 4;
					break;
				case 5:
					break;
			}
		}
		
	}


	switch(state)
	{
		case 0:
			set_sprite(vector2f(0, order));
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

			//cout << current_move.x << " " << current_move.y
			//<< direction.x << " " << direction.y << endl;

			move_x(current_move.x * direction.x, hitbox);
			move_y(current_move.y * direction.y, hitbox);

			if(direction.x == 1) set_flip(SDL_FLIP_NONE);
			else set_flip(SDL_FLIP_HORIZONTAL);

			break;
		case 3:
			set_sprite(vector2f(0, 12 + order));
			break;
		case 4:
			set_sprite(vector2f(0, 20 + order));
			move_x(speed * 2.0f * delta_time * direction.x, hitbox);
			move_y(speed * 1.5f * delta_time * direction.y, hitbox);
			break;
		case 5:
			set_sprite(vector2f(0, 24 + order));
			break;
			
	}

	if(current_time - last_update > 0.15f)
	{
		last_update = current_time;
		wait--;
		if(order == 3 && state == 5)
			order--;
		order++;
		switch(state)
		{
			case 0: // spawn
				order %= 4;
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
			case 4: // hit
				order %= 4;
				break;
			case 5: // death
				order %= 4;
				break;
		}
	}
}

void spawn_enemies()
{
	enemies.push_back(new Slime(vector2f(231, 63)));
}
