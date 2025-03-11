#include "player.hpp"
using namespace std;

Player::Player(Window &main_window):
	Entity(main_window.load_texture("res/lancelot_.png"), 
		{CAMERA_WIDTH / 2, CAMERA_HEIGHT / 2}, {0, 0, 32, 32})
{
	order = last = 0;
}

void Player::player_render(Window &main_window)
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



void Player::player_update(float delta_time, float now)
{
	const Uint8* key = SDL_GetKeyboardState(NULL);
	bool key_pressed = 0;
	if(key[SDL_SCANCODE_W])
	{
		move_y(-90, delta_time);
		key_pressed = 1;
	}
	if(key[SDL_SCANCODE_S])
	{
		move_y(90, delta_time);
		key_pressed = 1;
	}
	if(key[SDL_SCANCODE_A])
	{
		move_x(-90, delta_time);
		key_pressed = 1;
		set_flip(SDL_FLIP_HORIZONTAL);
	}
	if(key[SDL_SCANCODE_D])
	{
		move_x(90, delta_time);
		key_pressed = 1;
		set_flip(SDL_FLIP_NONE);
	}
	if(now - last > 0.1f) 
	{
		order = (order + 1) % (key_pressed ? 20 : 4);
		last = now;
		//cout << "changed" << endl;
	}
	set_sprite(vector2f(order / 4, order % 4));
	camera_update();
	//SDL_Rect tmp = get_rect();
	//cout << tmp.x << " " << tmp.y << endl; // 54 162
}