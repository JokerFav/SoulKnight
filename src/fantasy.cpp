#include "fantasy.hpp"
#include "player.hpp"
using namespace std;

Sword sword;
vector <Heart*> health_bar;

Sword::Sword():
	Entity()
{
	last_update = 0;
	state = 0;
	order = 4;
	last_attack = 0;
	roll = 0;
	texture = main_window.load_texture("res/excalibur_.png");
}

void Sword::sword_render()
{
	SDL_Rect sword_sprite = get_sprite();
	SDL_Rect sword_pos;
	sword_pos.x = pos.x - camera.x;
	sword_pos.y = pos.y - camera.y;
	sword_pos.w = sword_pos.h = 32;
	//roll = 35;
	SDL_RenderCopyEx(main_window.renderer, get_tex(), &sword_sprite, &sword_pos, roll, 
		NULL, get_flip());
}

bool Sword::is_attack()
{
	return (state > 0);
}

SDL_Rect Sword::set_attack_hitbox()
{
	SDL_Rect attack_hitbox = SDL_Rect{0, 0, 0, 0};
	switch(state)
	{
		case 1:
			attack_hitbox = SDL_Rect{(int)pos.x + 7, (int)pos.y - 3, 20, 23};
			break;
		case 2:
			attack_hitbox = SDL_Rect{(int)pos.x, (int)pos.y - 3, 20, 23};
			break;
	}
	return attack_hitbox;
}

void Sword::attack(float now, vector2f player_pos, SDL_RendererFlip player_flip)
{
	if(main_player.is_death())
	{
		state = 0;
		set_sprite(vector2f(0, 1));
		return;
	}
	if(player_flip == SDL_FLIP_NONE)
	{
		if(order == 4)
		{
			pos.x = player_pos.x + 6;
			pos.y = player_pos.y - 3;
		}
		else
		{
			pos.x = player_pos.x + 11;
			pos.y = player_pos.y + 6;
		}
	}
	else 
	{
		if(order == 4)
		{
			pos.x = player_pos.x - 6;
			pos.y = player_pos.y - 3;
		}
		else
		{
			pos.x = player_pos.x - 11;
			pos.y = player_pos.y + 6;
		}
	}
	
	const Uint8* key = SDL_GetKeyboardState(NULL);
	if(order == 4)
	{
		
		if(key[SDL_SCANCODE_J] && now - last_attack > 1)
		{
			
			if(player_flip == SDL_FLIP_NONE) state = 1;
			else state = 2;
			order = 0;
			last_attack = now;
		}
		else 
		{
			state = 0;
			roll = 0;
		}
	}

	if(now - last_update > 0.1f)
	{
		last_update = now;
		switch(state)
		{
			case 0: // idle
				set_sprite(vector2f(0, 0));
				break;
			case 1: // attack right
				set_sprite(vector2f(state, order));
				order++;
				roll = 90;
				break;
			case 2: // attack left
				set_sprite(vector2f(state, order));
				order++;
				roll = 270;
				break;
		}
	}
	//set_sprite(vector2f(3, order));
}

Heart::Heart(vector2f new_pos):
	Entity(new_pos)
{
	state = new_pos.x;
	sprite = SDL_Rect{0, 0, 8, 7};
	texture = main_window.load_texture("res/heart.png");
	order = 0;
}

void Heart::update(int new_order)
{
	pos.x = camera.x + state * sprite.w;
	pos.y = camera.y + camera.h - sprite.h;
	set_sprite(vector2f(0, new_order));
}

void set_health_bar()
{
	for(int i = 0; i < main_player.get_health() / 2; ++i)
		health_bar.emplace_back(new Heart(vector2f(i, 0)));
}
