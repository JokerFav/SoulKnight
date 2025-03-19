#include "player.hpp"
using namespace std;

Player::Player():
	Entity({CAMERA_WIDTH / 2, CAMERA_HEIGHT / 2})
{
	order = last_update = 0;
	texture = main_window.load_texture("res/lancelot_.png");
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



void Player::player_update(float current_time, bool is_attacking)
{
	const Uint8* key = SDL_GetKeyboardState(NULL);
	bool key_pressed = 0;
	if(key[SDL_SCANCODE_W])
	{
		move_y(-90, get_leg_rect());
		key_pressed = 1;
	}
	if(key[SDL_SCANCODE_S])
	{
		move_y(90, get_leg_rect());
		key_pressed = 1;
	}
	if(key[SDL_SCANCODE_A])
	{
		move_x(-90, get_leg_rect());
		key_pressed = 1;
		if(!is_attacking)
			set_flip(SDL_FLIP_HORIZONTAL);
	}
	if(key[SDL_SCANCODE_D])
	{
		move_x(90, get_leg_rect());
		key_pressed = 1;
		if(!is_attacking) 
			set_flip(SDL_FLIP_NONE);
	}
	if(current_time - last_update > 0.1f) 
	{
		order = (order + 1) % (key_pressed ? 20 : 4);
		last_update = current_time;
	}
	set_sprite(vector2f(order / 4, order % 4));
	camera_update();
}