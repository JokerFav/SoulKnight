#include "player.hpp"
using namespace std;

Player::Player():
	Entity({CAMERA_WIDTH / 2, CAMERA_HEIGHT / 2})
{
	texture = main_window.load_texture("res/player.png");
	order = 0;
	state = 0;
	last_update = 0;
	health_point = 12;
	speed = 60;
}

void Player::player_render()
{
	SDL_Rect player_sprite = get_sprite();
	SDL_Rect player_pos;
	player_pos.w = player_pos.h = 32;
	player_pos.x = pos.x - camera.x;
	player_pos.y = pos.y - camera.y;
	SDL_RenderCopyEx(main_window.renderer, get_tex(), &player_sprite, &player_pos, 0, NULL, 
		get_flip());
}

void Player::camera_update()
{
	camera.x = max(pos.x + 16 - CAMERA_WIDTH / 2, 0.0f);
	camera.x = min(camera.x, MAP_WIDTH - camera.w); 
	camera.y = max(pos.y + 16 - CAMERA_HEIGHT / 2, 0.0f);
	camera.y = min(camera.y, MAP_HEIGHT- camera.h);
}

SDL_Rect Player::get_leg_rect()
{
	SDL_Rect l_rect; // go chicken go uuuuuuuuuuuuu
	l_rect.x = pos.x + 9;
	l_rect.y = pos.y + 26;
	l_rect.w = 13;
	l_rect.h = 3;
	return l_rect;
}

SDL_Rect Player::get_hitbox()
{
	hitbox.x = pos.x + 8;
	hitbox.y = pos.y + 10;
	hitbox.w = 15;
	hitbox.h = 20;
	return hitbox;
}

void Player::update(float current_time, bool is_attacking, float delta_time)
{
	const Uint8* key = SDL_GetKeyboardState(NULL);
	state = 0;
	if(key[SDL_SCANCODE_W])
	{
		move_y(-speed * delta_time, get_leg_rect());
		state = 1;
	}
	if(key[SDL_SCANCODE_S])
	{
		move_y(speed * delta_time, get_leg_rect());
		state = 1;
	}
	if(key[SDL_SCANCODE_A])
	{
		move_x(-speed * delta_time, get_leg_rect());
		state = 1;
		if(!is_attacking)
			set_flip(SDL_FLIP_HORIZONTAL);
	}
	if(key[SDL_SCANCODE_D])
	{
		move_x(speed * delta_time, get_leg_rect());
		state = 1;
		if(!is_attacking) 
			set_flip(SDL_FLIP_NONE);
	}

	if(current_time - last_update > 0.1f)
	{
		last_update = current_time;
		switch(state)
		{
			case 0: // idle
				order = (order + 1) % 4;
				break;
			case 1: // run
				order = (order + 1) % 8;
				break;
		}
		set_sprite(vector2f(0, state * 4 + order));
	}
	camera_update();
}